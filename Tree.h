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
#include "Iterator.h"


using namespace std;

namespace assignment {
    
    template <class T>
    class AVLTree {
        private:
            shared_ptr<Node<T>> root;
            int values;
            int total;
            
            
            shared_ptr<Node<T>> add(T value, shared_ptr<Node<T>> parent, shared_ptr<Node<T>>& child, int balance);
                        
            void balanceAddition(shared_ptr<Node<T>> node, int balance);
            
            void remove(shared_ptr<Node<T>> node);
            
            void removeMiddle(shared_ptr<Node<T>> node, shared_ptr<Node<T>> left, shared_ptr<Node<T>> right);
            
            void balanceRemoval(shared_ptr<Node<T>> node, int balance);
            
            
            shared_ptr<Node<T>> rotateLeft(shared_ptr<Node<T>> node);
            
            shared_ptr<Node<T>> rotateRight(shared_ptr<Node<T>> node);
            
            
            shared_ptr<Node<T>> rotateLeftRight(shared_ptr<Node<T>> node);
            
            shared_ptr<Node<T>> rotateRightLeft(shared_ptr<Node<T>> node);
            
            
        public:
            AVLTree();
            
            AVLTree<T>& add(T value);
            
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
        values = 0;
        total = 0;
    }
    
    
    template <class T>
    AVLTree<T>& AVLTree<T>::add(T value) {
        cout << "Value: " << value << endl;
        if (!root) {
            root = make_shared<Node<T>>(value);
            values++;
            total++;
            return *this;
        }
        
        auto node = root;
        while (node) {
            if (node->value < value) {
                node = add(value, node, node->right, -1);
                
            } else if (node->value > value) {
                node = add(value, node, node->left, 1);
                
            } else {
                node->amount++;
                total++;
                return *this;
            }
        }
        
        return *this;
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::add(T value, shared_ptr<Node<T>> node, shared_ptr<Node<T>>& child, int balance) {
        if (!child) {
            child = make_shared<Node<T>>(value, node);
            balanceAddition(node, balance);
            values++;
            total++;
            return nullptr;
            
        } else {
            return child;
        }
    }
    
    template <class T>
    void AVLTree<T>::balanceAddition(shared_ptr<Node<T>> node, int balance) {
        while (node) {
            balance = (node->balance += balance);

            if (balance == 0) {
                return;
                
            } else if (balance == 2) {
                if (node->left->balance == 1) {
                    rotateRight(node);

                } else {
                    rotateLeftRight(node);
                }
                return;
                
            } else if (balance == -2) {
                if (node->right->balance == -1) {
                    rotateLeft(node);
                    
                } else {
                    rotateRightLeft(node);
                }
                return;
            }
            
            auto parent = node->parent;
            if (parent) {
                if (parent->left == node) {
                    balance = 1;
                    
                } else {
                    balance = -1;
                }
            }
            node = parent;
        }
    }
    
    
    template <class T>
    bool AVLTree<T>::contains(T value, ostream& stream) {
        if (root && root->value == value) {
            return true;
        }
        
        auto node = root;
        while (node) {
            if (node->value < value) {
                node = node->right;
                
            } else if (node->value > value) {
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
            removeMiddle(node, left, right);
            
        } else if (left) {
            replace(left, node);
            balanceRemoval(node, 0);
            
        } else if (right) {
            replace(right, node);
            balanceRemoval(node, 0);
            
        } else {
            auto parent = node->parent;
            if (parent->left == node) {
                parent->left = nullptr;
                balanceRemoval(parent, -1);
                
            } else {
                parent->right = nullptr;
                balanceRemoval(parent, 1);
            }
        }
        values--;
        total--;
    }
    
    template <class T>
    void AVLTree<T>::removeMiddle(shared_ptr<Node<T>> node, shared_ptr<Node<T>> left, shared_ptr<Node<T>> right) {
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
            left->parent = sucessor;
            
            if (node == root) {
                root = sucessor;
                
            } else if (parent->left == node) {
                parent->left = sucessor;
                
            } else {
                parent->right = sucessor;
            }
            
            balanceRemoval(sucessorParent, -1);
            
        } else {
            sucessor->parent = parent;
            sucessor->left = left;
            sucessor->balance = node->balance;
            left->parent = sucessor;
            
            if (node == root) {
                root = sucessor;
                
            } else if (parent->left == node) {
                parent->left = sucessor;
                
            } else {
                parent->right = sucessor;
            }
            
            balanceRemoval(sucessor, 1);
        }
    }
    
    template <class T>
    void AVLTree<T>::balanceRemoval(shared_ptr<Node<T>> node, int balance) {
        while (node) {
            balance = (node->balance += balance);
            if (balance == 2) {
                if (node->left->balance >= 0) {
                    node = rotateRight(node);
                    if (node->balance == -1) {
                        return;
                    }
                    
                } else {
                    node = rotateLeftRight(node);
                }
                
            } else if (balance == -2) {
                if (node->right->balance <= 0) {
                    node = rotateLeft(node);
                    if (node->balance == 1) {
                        return;
                    }
                    
                } else {
                    node = rotateRightLeft(node);
                }
            } else if (balance != 0) {
                return;
            }
            
            if (node->parent) {
                balance = node->parent->left ? -1 : 1;
            }
            
            node = node->parent;
        }
    }
    
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateLeft(shared_ptr<Node<T>> node) {
        auto right = node->right;
        auto rightLeft = right->left;
        auto parent = node->parent;
        
        right->parent = parent;
        right->left = node;
        node->right = rightLeft;
        node->parent = right;
        
        if (rightLeft) {
            rightLeft->parent = node;
        }
        
        if (node == root) {
            root = right;
            
        } else if (parent->left == node) {
            parent->left = right;
            
        } else {
            parent->right = right;
        }
        
        right->balance++;
        node->balance = -right->balance;
        
        return right;
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateRight(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto leftRight = left->right;
        auto parent = node->parent;
        
        left->parent = parent;
        left->right = node;
        node->left = leftRight;
        node->parent = left;
        
        if (leftRight) {
            leftRight->parent = node;
        }
        
        if (node == root) {
            root = left;
            
        } else if (parent->left == node) {
            parent->left = left;
            
        } else {
            parent->right = left;
        }
        
        left->balance--;
        node->balance = -left->balance;
        
        return left;
    }
    
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateLeftRight(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto leftRight = left->right;
        auto parent = node->parent;
        
        auto leftRightRight = leftRight->right;
        auto leftRightLeft = leftRight->left;
        
        leftRight->parent = parent;
        node->left = leftRightRight;
        left->right = leftRightLeft;
        leftRight->left = left;
        leftRight->right = node;
        left->parent = leftRight;
        node->parent = leftRight;
        
        if (leftRightRight) {
            leftRightRight->parent = node;
        }
        
        if (leftRightLeft) {
            leftRightLeft->parent = left;
        }
        
        if (node == root) {
            root = leftRight;
            
        } else if (parent->left == node) {
            parent->left = leftRight;
            
        } else {
            parent->right = leftRight;
        }
        
        if (leftRight->balance == -1) {
            node->balance = 0;
            left->balance = 1;
            
        } else if (leftRight->balance == 1) {
            node->balance = -1;
            left->balance = 0;
            
        } else {
            node->balance = 0;
            left->balance = 0;
        }
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateRightLeft(shared_ptr<Node<T>> node) {
        auto right = node->right;
        auto rightLeft = right->left;
        auto parent = node->parent;
        auto rightLeftLeft = rightLeft->left;
        auto rightLeftRight = rightLeft->right;
        
        rightLeft->parent = parent;
        node->right = rightLeftLeft;
        right->left = rightLeftRight;
        rightLeft->right = right;
        rightLeft->left = node;
        right->parent = rightLeft;
        node->parent = rightLeft;
        
        if (rightLeftLeft) {
            rightLeftLeft->parent = node;
        }
        
        if (rightLeftRight) {
            rightLeftRight->parent = right;
        }
        
        if (node == root) {
            root = rightLeft;
            
        } else if (parent->left == node) {
            parent->left = rightLeft;
            
        } else {
            parent->right= rightLeft;
        }
        
        if (rightLeft->balance == 1) {
            node->balance = 0;
            right->balance = -1;
            
        } else if (rightLeft->balance == 0) {
            node->balance = 0;
            right->balance = 0;
            
        } else {
            node->balance = -1;
            right->balance = 0;
        }
        
        rightLeft->balance = 0;
        return rightLeft;
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

