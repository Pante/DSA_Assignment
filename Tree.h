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
 * Created on January 8, 2018, 3:27 PM
 */

#ifndef TREE_H
#define TREE_H

#include <stdexcept>

#include "Iterator.h"
#include "Node.h"
#include "Balance.h"

namespace assignment {
    
    template <class T = int>
    class AVLTree {
        
        private:            
            Node<T>* root;
            Balance<T> balance;
            unsigned int size;
            unsigned int nodes;
            
            bool add(Node<T>* node, Node<T>* child, T value, int balance);
            
            void rotateLeft(Node<T>* node);
            
            void rotateRight(Node<T>* node);
            
            void rotateLeftRight(Node<T>* node);
            
            void rotateRightLeft(Node<T>* node);
            
        public:
            AVLTree();
            
            
            void add(T value);
            
            void remove(T value);
            
            T get(unsigned int index);
            
            bool contains(T value);
            
            friend std::ostream& operator<<(std::ostream& stream, const AVLTree<T>& tree);
            
            Iterator<T> iterator(Traversal traversal);
            
            unsigned int size();
            
    };
    
    
    template <class T>
    AVLTree::AVLTree() {
        root = nullptr;
        balance = Balance();
        size = 0;
        nodes = 0;
    }
    
    
    template <class T>
    void AVLTree::add(T value) {
        Node<T>* node = root;
        while (node) {
            if (node->value < value) {
                node = add(node, node->right, value, 1);
                
            } else if (node->value > value) {
                node = add(node, node->right, value, -1);
                
            } else {
                node->amount++;
                break;
            }
        }
        size++;
    }
    
    
    template <class T>
    Node<T>* AVLTree::add(Node<T>* node, Node<T>* child, T value, int balance) {
        if (child) {
            return child;
            
        } else {
            child = new Node(value, node);
            this->balance->add(node, balance);
            nodes++;
            return nullptr;
        }
    }
    
    
    template <class T>
    void AVLTree::remove(T value) {
        
    }

    
    // Parameterize
    template <class T>
    void AVLTree::rotateLeft(Node<T>* node) {
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
            
        } else if (parent->right == node) {
            parent->right = right;
            
        } else {
            parent->left = right;
        }
        
        right->balance++;
        node->balance = -right->balance;
        
        return right;
    }
    
    template <class T>
    void AVLTree::rotateRight(Node<T>* node) {
        auto left = node->left;
        auto leftRight = left->right;
        auto parent = node->parent;
        
        left->parent = parent;
        left->right = node;
        node->right = leftRight;
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
        
        left->balance++;
        node->balance = -left->balance;
        
        return left;
    }
    //
    
    // Parameterize
    template <class T>
    void AVLTree::rotateLeftRight(Node<T>* node) {
        auto left = node->left;
        auto leftRight = left->right;
        auto parent = node->parent;
        auto leftRightRight = leftRight->right;
        auto leftRightLeft = leftRight->right;

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

        if (leftRight.Balance == -1) {
            node.Balance = 0;
            left.Balance = 1;
        } else if (leftRight.Balance == 0) {
            node.Balance = 0;
            left.Balance = 0;
        } else {
            node.Balance = -1;
            left.Balance = 0;
        }

        leftRight.Balance = 0;
    }
    
    template <class T>
    void AVLTree::rotateRightLeft(Node<T>* node) {
        
    }
    //
    
    
    template <class T>
    T AVLTree::get(unsigned int index) {
        if (index >= nodes) {
            throw std::out_of_range("Index is out of range: " + index);
        }
        
        Iterator iterator = iterator(Traversal::LEVEL);
        for (unsigned int i = 0; i < index; i++) {
            iterator.next();
        }
        
        return iterator.next()->value;
    }
    
    
    template <class T>
    bool AVLTree::contains(T value, std::ostream& stream = std::cout) {
        if (size == 1 && root->value == value) {
            stream << "root" << std::endl;
            return true;
        }
        
        Node<T>* node = root;
        while (node) {
            if (node->value < value) {
                node = node->right;
                stream << "Right" << std::endl;
                
            } else if (node->value > value) {
                node = node->left;
                stream << "Left" << std::endl;
                
            } else {
                return true;
            }
        }
        
        return false;
    }
    
    
    template <class T>
    friend std::ostream& operator<<(std::ostream& stream, const AVLTree<T>& tree) {
        Iterator iterator = iterator(Traversal::ASCENDING);
        Node<T>* node;
        while ((node = iterator.next())) {
            stream << node;
        }
        return stream;
    }
    
    
    template <class T>
    Iterator<T> AVLTree::iterator(Traversal traversal) {
        switch (traversal) {
            case Traversal::ASCENDING:
                return AscendingIterator(root);
                
            case Traversal::LEVEL:
                return LevelIterator(root);
                
            default:
                throw std::invalid_argument();
        }
    }
    
    
    template <class T>
    unsigned int AVLTree::size() {
        return size;
    }
    
}

#endif /* TREE_H */

