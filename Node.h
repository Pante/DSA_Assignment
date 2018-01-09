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
 * File:   Node.h
 * Author: Karus Labs
 *
 * Created on January 8, 2018, 3:12 PM
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>

namespace assignment {
    
    template <class T>
    struct Node {
        
        T value;
        unsigned int amount;
        int balance;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;
        
        
        Node(T value, Node<T>* parent = nullptr) {
            this->value = value;
            amount = 1;
            balance = 0;
            this->parent = parent;
            left = nullptr;
            right = nullptr;
        }
        
        
        std::ostream& operator<<(std::ostream& stream, const Node<T>& node) {
            for (int i = 0; i < amount; i++) {
                stream << value << std::endl;
            }
            return stream;
        }
        
    };
    
}

#endif /* NODE_H */

