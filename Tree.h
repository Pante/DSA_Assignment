/*
 * The MIT License
 *
 * Copyright 2018 Karus Labs.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/* 
 * File:   Tree.h
 * Author: Karus Labs
 *
 * Created on January 13, 2018, 4:35 PM
 */

#ifndef TREE_H
#define TREE_H

#include <memory>
#include <stdexcept>

#include "Node.h"
#include "Balance.h"
#include "Iterator.h"


using namespace std;

namespace assignment {
    
    template <class T>
    class AVLTree {
        private:
            shared_ptr<Node<T>> root;
            unique_ptr<Balance<T>> balance;
            int values;
            int total;
            
            shared_ptr<Node<T>> add(T value, shared_ptr<Node<T>> parent, shared_ptr<Node<T>>& child, int balance);
            
            void remove(shared_ptr<Node<T>> node);
            
            void remove(shared_ptr<Node<T>> node, shared_ptr<Node<T>> left, shared_ptr<Node<T>> right);
            
        public:
            AVLTree();
            
            void add(T value);
            
            bool contains(T value, ostream& stream = cout);
            
            bool remove(T value);
            
            shared_ptr<Iterator<T>> iterator(Traversal traversal = Traversal::LEVEL);
            
            T operator[](int index);
            
            template <class V>
            friend ostream& operator<<(ostream& stream, const AVLTree<V>& tree);
            
            int nodes();
            
            int size();
    };
    
    template <class T>
    AVLTree<T>::AVLTree() {
        root = shared_ptr<Node<T>>(nullptr);
        balance = unique_ptr<Balance<T>>(new Balance<T>(root));
        values = 0;
        total = 0;
    }
    
    
    template <class T>
    void AVLTree<T>::add(T value) {
        if (!root) {
            root = make_shared<Node<T>>(value);
            values++;
            total++;
            return;
        }
        
        auto node = root;
        while (node) {
            if (node->value < value) {
                node = add(value, node, node->right, 1);
                
            } else if (node->value > value) {
                node = add(value, node, node->left, -1);
                
            } else {
                node->amount++;
                total++;
                return;
            }
        }
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::add(T value, shared_ptr<Node<T>> parent, shared_ptr<Node<T>>& child, int balance) {
        if (!child) {
            child = make_shared<Node<T>>(value, parent);
            this->balance->add(child, balance);
            values++;
            total++;
            return nullptr;
            
        } else {
            return child;
        }
    }
    
    
    template <class T>
    bool AVLTree<T>::contains(T value, ostream& stream) {
        if (root && root->value == value) {
            stream << "Root" << endl;
            return true;
        }
        
        auto node = root;
        while (node) {
            if (node->value < value) {
                stream << "Right" << endl;
                node = node->right;
                
            } else if (node->value > value) {
                stream << "Left" << endl;
                node = node->left;
                
            } else {
                return true;
            }
        }
        
        return false;
    }
    
    
    template <class T>
    bool AVLTree<T>::remove(T value) {
        auto node = root;
        while (node) {
            if (node->value < value) {
                node = node->right;
                
            } else if (node->value > value) {
                node = node->left;
                
            } else {
                if (node->amount == 1) {
                    remove(node);
                    return true;
                    
                } else {
                    node->amount--;
                    total--;
                    return true;
                }
            }
        }
        
        return false;
    }
    
    template <class T>
    void AVLTree<T>::remove(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto right = node->right;
        if (left && right) {
            remove(left, node, right);
            
        } else if (left) {
            replace(left, node);
            balance->remove(node, 0);
            
        } else if (right) {
            replace(right, node);
            balance->remove(node, 0);
            
        } else {
            auto parent = node->parent;
            if (parent->left == node) {
                parent->left = nullptr;
                balance->remove(parent, -1);
                
            } else {
                parent->right = nullptr;
                balance->remove(parent, 1);
            }
        }
        values--;
        total--;
    }
    
    template <class T>
    void AVLTree<T>::remove(shared_ptr<Node<T>> node, shared_ptr<Node<T>> left, shared_ptr<Node<T>> right) {
        auto sucessor = right;
        auto parent = node->parent;
        
        if (sucessor->left) {
            while (sucessor->left) {
                sucessor = sucessor->left;
            }
            
            auto sucessorParent = sucessor->parent;
            auto sucessorRight = sucessor->right;
            
            sucessorParent->left = sucessorRight;
            if (sucessorRight) {
                sucessorRight->parent = sucessorParent;
            }
            
            sucessor->parent = parent;
            sucessor->left = left;
            sucessor->balance = node->balance;
            sucessor->right = right;
            right->parent = sucessor;
            
            if (left) {
                left->parent = sucessor;
            }
            
            if (node == root) {
                root = sucessor;
                
            } else if (parent->left = sucessor) {
                parent->left = sucessor;
                
            } else {
                parent->right = sucessor;
            }
            
            balance->remove(sucessorParent, -1);
            
        } else {
            sucessor->parent = parent;
            sucessor->left = left;
            sucessor->balance = node->balance;
            
            if (left) {
                left->parent = sucessor;
            }
            
            if (node == root) {
                root = sucessor;
                
            } else if (parent->left == node) {
                parent->left = sucessor;
                
            } else {
                parent->right = sucessor;
            }
            
            balance->remove(sucessor, 1);
        }
    }
    
    
    template <class T>
    shared_ptr<Iterator<T>> AVLTree<T>::iterator(Traversal traversal) {
        switch (traversal) {
            case Traversal::ASCENDING:
                return shared_ptr<Iterator<T>>(new AscendingIterator<T>(root));
                
            case Traversal::LEVEL:
                return shared_ptr<Iterator<T>>(new LevelIterator<T>(root));
                
            default:
                throw invalid_argument("Unsupported iterator");
        }
    }
    
    
    template <class T>
    T AVLTree<T>::operator[](int index) {
        if (index < 0 || index >= values) {
            throw invalid_argument("index is invalid");
        }
        
        shared_ptr<Iterator<T>> iterator = this->iterator();
        for (int i = 0; i < index; i++) {
            (*iterator)++;
        }
        
        return iterator->get()->value;
    }
    
    template <class T>
    ostream& operator<<(ostream& stream, AVLTree<T>& tree) {
        auto iterator = tree.iterator(Traversal::ASCENDING);
        while ((*iterator)++) {
            auto value = iterator->get();
            stream << (*value);
        }
        return stream;
    }
    
    
    template <class T>
    int AVLTree<T>::nodes() {
        return values;
    }
    
    template <class T>
    int AVLTree<T>::size() {
        return total;
    }
    
}

#endif /* TREE_H */

