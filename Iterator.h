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

// I could use the implementation from Week 6's practical, but it is honestly really stupid
// having to copy & paste the code simply to bypass the STL ban. Plus the STL's implementation
// is far more optimal than a homebrew solution. If you insist on enforcing the ban here,
// I'll literally copy and paste the STL queue into this file. :)

#include <queue>
#include "Node.h"


namespace assignment {
    
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
        private:
            std::queue<T> queue;
        
        public:
            LevelIterator(Node<T>* root) : Iterator<T>(root) {
                queue = std::queue<T>();
            }

            Node<T>* next() override;
        
    };
    
    template <class T>
    Node<T>* LevelIterator::next() {
        if (current && !current->parent) {
            queue.push(current);
            return current;
            
        } else if (!queue.empty()) {
            queue.pop();
                        
            if (current->left) {
                queue.push(current->left);
            }
            if (current->right) {
                queue.push(current->right);
            }
            
            current = queue.front();
            
            return current;
            
        } else {
            return nullptr;
        }
    }
    
}

#endif /* ITERATOR_H */

