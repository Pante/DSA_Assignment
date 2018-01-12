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
 * Created on January 12, 2018, 12:11 AM
 */

#ifndef NODE_H
#define NODE_H

#include <memory>

using namespace std;

namespace assignment {
    
    template <class T = int>
    struct Node {
        
        T value;
        int amount;
        int balance;
        shared_ptr<Node<T>> parent;
        shared_ptr<Node<T>> left;
        shared_ptr<Node<T>> right;
              
        
        Node(T value, shared_ptr<Node<T>> parent = shared_ptr<Node<T>>(nullptr)) {
            this->value = value;
            amount = 1;
            balance = 0;
            this->parent = parent;
            left = shared_ptr<Node<T>>(nullptr);
            right = shared_ptr<Node<T>>(nullptr);
        }

        
        friend ostream& operator<<(const ostream& stream, const Node<T>& node) {
            for (int i = 0; i < node.amount; i++) {
                stream << node.value << endl;
            }
            return stream;
        }
            
    };

    
    template <class T>
    void swap(shared_ptr<Node<T>> a, shared_ptr<Node<T>> b) {
        set(a, b);
        set(b, a);
        
        a->parent.swap(b->parent);
        a->left.swap(b->left);
        a->right.swap(b->right);
    }
    
    template <class T>
    void set(shared_ptr<Node<T>> source, shared_ptr<Node<T>> target) {
        if (target->left) {
            target->left->parent = source;
        }
        if (target->right) {
            target->right->parent = source;
        }
        if (target->parent) {
            if (target->parent->left == source) {
                target->parent->left = source;

            } else {
                target->parent->right = source;
            }
        }
    }
    
}

#endif /* NODE_H */

