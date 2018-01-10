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
 * File:   Balance.h
 * Author: Karus Labs
 *
 * Created on January 9, 2018, 3:52 PM
 */

#ifndef BALANCE_H
#define BALANCE_H

#include "Node.h"


namespace assignment {
    
    template <class T>
    class Balance {
        private:            
            void rotateLeft(Node<T>* root, Node<T>* node);
            
            void rotateRight(Node<T>* root, Node<T>* node);
            
            void rotate(Node<T>* root, Node<T>* node, Node<T>*& inserted, Node<T>*& opposite, Node<T>*& oppositeChild, Node<T>*& parentOpposite, Node<T>*& parentInserted, int balance);
            
            
            void rotateLeftRight(Node<T>* root, Node<T>* node);
            
            void rotateRightLeft(Node<T>* root, Node<T>* node);
            
            void rotateTwice();
            
        public:

            virtual void add(Node<T>* root, Node<T>* node, int balance);
            
            virtual void remove(Node<T>* root, Node<T>* node, int balance);
            
    };
    
    
    template <class T>
    void Balance<T>::add(Node<T>* root, Node<T>* node, int balance) {
        while (node) {
            int balance = node->balance += balance;
            if (balance == 0) {
                return;
                
            } else if (balance == 2) {
                if (node->left->balance == 1) {
                    rotateRight(root, node);
                    
                } else {
                    rotateLeftRight(root, node);
                }
                
            } else if (balance == -2) {
                if (node->right->balance == -1) {
                    rotateLeft(root, node);
                    
                } else {
                    rotateLeftRight(root, node);
                }
            }

            auto parent = node->parent;
            if (parent) {
                balance = parent->left == node ? 1 : -1;
            }
            node = node->parent;
        }
    }
    
    
    template <class T>
    void Balance<T>::remove(Node<T>* root, Node<T>* node, int balance) {
        
    }

    
    template <class T>
    void Balance<T>::rotateLeft(Node<T>* root, Node<T>* node) {
        rotate(root, node, node->left, node->right, node->right->left, node->parent->left, node->parent->right, 1);
    }
    
    template <class T>
    void Balance<T>::rotateRight(Node<T>* root, Node<T>* node) {
        rotate(root, node, node->right, node->left, node->left->right, node->parent->right, node->parent->left, -1);
    }
    
    template <class T>
    void Balance<T>::rotate(Node<T>* root, Node<T>* node, Node<T>*& inserted, Node<T>*& opposite, Node<T>*& oppositeChild, Node<T>*& parentInserted, Node<T>*& parentOpposite, int balance) {
        opposite->parent = node->parent;
        opposite->left = node;
        node->right = oppositeChild;
        node->parent = opposite;
        
        if (oppositeChild) {
            oppositeChild->parent = node;
        }
        
        if (node == root) {
            root = opposite;
            
        } else if (parentOpposite == node) {
            parentOpposite = opposite;
            
        } else {
            parentInserted = opposite;
        }
        
        opposite->balance += balance;
        node->balance = -opposite->balance;
    }
    
    
    template <class T>
    void Balance<T>::rotateLeftRight(Node<T>* root, Node<T>* node) {
        
    }
    
    template <class T>
    void Balance<T>::rotateRightLeft(Node<T>* root, Node<T>* node) {
        
    }
    
    template <class T>
    void Balance<T>::rotateTwice() {
        
    }
    
}

#endif /* BALANCE_H */

