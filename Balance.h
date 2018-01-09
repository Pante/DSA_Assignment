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
        public:
            void add(Node<T>* node, int balance);
            
            void remove(Node<T>* node, int balance);
    };
    
    
    template <class T>
    void Balance::add(Node<T>* node, int balance) {
        while (node) {
            int balance = node->balance += balance;
            // Parameterize
            if (balance == 0) {
                return;
                
            } else if (balance == 2) {
                if (node->left->balance == 1) {
                    rotateRight(node);
                    
                } else {
                    rotateLeftRight(node);
                }
                
            } else if (balance == -2) {
                if (node->right->balance == -1) {
                    rotateLeft(node);
                    
                } else {
                    rotateLeftRight(node);
                }
            }
            //
            auto parent = node->parent;
            if (parent) {
                balance = parent->left == node ? 1 : -1;
            }
            node = node->parent;
        }
    }
    
    
    template <class T>
    void Balance::remove(Node<T>* node, int balance) {
        
    }
    
    
    template <class T>
    class Rotation {
        
        
    };
    
}

#endif /* BALANCE_H */

