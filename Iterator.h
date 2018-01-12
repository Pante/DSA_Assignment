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
 * Created on January 12, 2018, 1:41 AM
 */

#ifndef ITERATOR_H
#define ITERATOR_H

#include <queue>
#include <stdexcept>
#include "Node.h"

using namespace std;

namespace assignment {
    
    enum Traversal {
        ASCENDING, LEVEL
    };
    
    template <class T>
    class Iterator {
        protected:
            shared_ptr<Node<T>> current;
        
        public:
            Iterator(shared_ptr<Node<T>> root);
            
            virtual Iterator<T>& operator++(int increment);
            
            virtual Iterator<T>& operator++() =0;
            
            shared_ptr<Node<T>> operator->();
    };
    
    template <class T>
    Iterator<T>::Iterator(shared_ptr<Node<T>> root) {
        current = root;
    }
    
    template <class T>
    Iterator<T>& Iterator<T>::operator++(int increment) {
        if (increment < 0) {
            throw invalid_argument("argument must be equal to or more than 0");
        }
        
        for (int i = 0; i <= increment; i++) {
            this->operator++();
        }
        
        return *this;
    }
    
    template <class T>
    shared_ptr<Node<T>> Iterator<T>::operator->() {
        return current;
    }
    
    
    template <class T>
    class AscendingIterator : public Iterator<T> {
        private:
            enum Direction {
                RIGHT, PARENT, END
            };
            
            shared_ptr<Node<T>> right;
            Direction direction;
            
        public:
            using Iterator<T>::current;
            using Iterator<T>::operator++;

            AscendingIterator(shared_ptr<Node<T>> root) : Iterator<T>(root) {
                current = root;
                right = root;
                direction = (current == nullptr) ? Direction::END : Direction::RIGHT;
            }
            
            Iterator<T>& operator++() override;
    };
    
    template <class T>
    Iterator<T>& AscendingIterator<T>::operator++() {
        if (direction == Direction::RIGHT) {
            current = right;
            while (current->left) {
                current = current->left;
            }

            right = current->right;
            if (!right) {
                direction = Direction::PARENT;
            }
        } else if (direction == Direction::PARENT) {
            while (current->parent) {
                auto previous = current;
                current = current->parent;

                if (current->left == previous) {
                    right = current->right;
                    if (right) {
                        direction = Direction::RIGHT;
                    }
                    return *this;
                }
            }
            direction = Direction::END;
        }
        return *this;
    }
    
    
    template <class T>
    class LevelIterator : public Iterator<T> {
        private:
            std::queue<shared_ptr<Node<T>>> nodes;
        
        public:
            using Iterator<T>::current;
            using Iterator<T>::operator++;
            
            LevelIterator(shared_ptr<Node<T>> root) : Iterator<T>(root) {
                nodes = std::queue<shared_ptr<Node<T>>>();
                nodes.push(current);
            }
            
            LevelIterator<T>& operator++() override;  
    };
    
    template <class T>
    LevelIterator<T>& LevelIterator<T>::operator++() {
        if (!nodes.empty()) {           
            current = nodes.front();
            nodes.pop();
            
            if (current->left) {
                nodes.push(current->left);
            }
            if (current->right) {
                nodes.push(current->right);
            }
        }
        
        return *this;
    }
}

#endif /* ITERATOR_H */

