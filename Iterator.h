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
 * File:   Iterator.h
 * Author: Karus Labs
 *
 * Created on January 8, 2018, 3:19 PM
 */

#ifndef ITERATOR_H
#define ITERATOR_H

#include "Node.h"


namespace Assignment {
    
    enum Traversal {
        ASCENDING, LEVEL
    };
    
    
    template <class T>
    class Iterator {
        protected:
            Node<T> current;
            
        public:
            Iterator(Node<T>* root);
            
            virtual Node<T>* next() =0;
        
    };
    
    
    template <class T>
    Iterator::Iterator(Node<T>* root) : current {root} {}

    
    
    template <class T>
    class AscendingIterator : Iterator {
        private:
            enum direction {
                start, right, parent, end
            };
            
            Node<T>* right;
            direction direction;
            
        public:
            AscendingIterator(Node<T>* root) : Iterator<T>(root) {
                right = root;
                direction = root ? direction::start : direction::end;
            }
        
            Node<T>* next() override;
        
    };
    
    template <class T>
    Node<T>* AscendingIterator::next() {
        switch (direction) {
            case direction::start:
                direction = direction::right;
                return current;
            
            case direction::right:
                current = right;
                while (!current->left) {
                    current = current->left;
                }
                
                right = current->right;
                if (!right) {
                    direction = direction::parent;
                } 
                
                return current;
                
            case direction::parent:
                while (current->parent) {
                    auto previous = current;
                    current = current->parent;
                    
                    if (current.left == previous) {
                        right = current->right;
                        
                        if (right) {
                            direction = direction::right;
                        }
                        
                        return current;
                    }
                }
                direction = direction::end;
                        
                return nullptr;
                
            default:
                return nullptr;
        }
    }
    
    
    template <class T>
    class LevelIterator : Iterator {

        LevelIterator(Node<T>* root) : Iterator<T>(root) {}
        
        Node<T>* next() override;
        
    };
    
    template <class T>
    Node<T>* LevelIterator::next() {
        
    }
    
}

#endif /* ITERATOR_H */

