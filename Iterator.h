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

#include <stdexcept>

#include "Queue.h"
#include "Node.h"

using namespace std;

namespace assignment {
    
    /**
     * Represents the traversal types of the iterator(s).
     */
    enum Traversal {
        ASCENDING, LEVEL
    };
    
    /**
     * Represents an iterator for an AVL tree.
     */
    template <class T>
    class Iterator {
        protected:
            shared_ptr<Node<T>> current;
        
        public:
            /**
             * Constructs an Iterator which the specified root.
             */
            Iterator(shared_ptr<Node<T>> root);
            
            /**
            * Iterate to the next element in the iteration.
            * 
            * @return true if the iteration has more elements; else false
            */
            virtual bool operator++(int);
            
            /**
            * Iterates to the next element in the iteration.
            * 
            * @return true if the iteration has more elements; else false
            */
            virtual bool operator++() =0;
            
            /**
             * Returns the current element in the iteration.
             */
            shared_ptr<Node<T>> get();
    };
    
    template <class T>
    Iterator<T>::Iterator(shared_ptr<Node<T>> root) {
        current = root;
    }
    
    template <class T>
    bool Iterator<T>::operator++(int) {
        return operator++();
    }
    
    template <class T>
    shared_ptr<Node<T>> Iterator<T>::get() {
        return current;
    }
    
    
    /**
     * A concrete subclass of Iterator which iterates through an AVL tree in an
     * ascending order.
     */
    template <class T>
    class AscendingIterator : public Iterator<T> {
        private:
            /**
             * Represents the direction of the next traversal.
             */
            enum Direction {
                RIGHT, PARENT, END
            };
            
            shared_ptr<Node<T>> right;
            Direction direction;
            
        public:
            using Iterator<T>::current;
            using Iterator<T>::operator++;
            
            /**
             * Constructs an AscendingIterator with the specified root and
             * set the direction RIGHT, or END if the specified root is null.
             */
            AscendingIterator(shared_ptr<Node<T>> root) : Iterator<T>(root) {
                current = root;
                right = root;
                direction = (current == nullptr) ? Direction::END : Direction::RIGHT;
            }
            
            /**
             * Iterates to the next element in the iteration in an ascending order.
             * 
             * @return true if the iteration has more elements; else false
             */
            bool operator++() override;
    };
    
    /**
     * If the direction is RIGHT, set the current node as its left-most child. 
     * After which, set the next node as the current node's right child, or set the direction
     * as PARENT if the current node has no right child.
     * 
     * If the direction is PARENT, set the current node as its parent while the current node has a parent,
     * and sets the direction to RIGHT if the current node has a right child and returns from the loop, otherwise
     * sets the direction as END.
     */
    template <class T>
    bool AscendingIterator<T>::operator++() {
        if (direction == Direction::RIGHT) {
            current = right;
            
            while (current->left) {
                current = current->left;
            }
 
            if (!current->right) {
                direction = Direction::PARENT;
            } else {
                right = current->right;
            }
            return true;
            
        } else if (direction == Direction::PARENT) {
            while (current->parent) {
                auto previous = current;
                current = current->parent;

                if (current->left == previous) {
                    right = current->right;
                    if (right) {
                        direction = Direction::RIGHT;
                    }
                    return true;
                }
            }
            direction = Direction::END;
            return false;
            
        }
        return false;
    }
    
    
    /**
     * A concrete subclass of Iterator which iterates through an AVL tree level-by-level.
     */
    template <class T>
    class LevelIterator : public Iterator<T> {
        private:
            week5::Queue<shared_ptr<Node<T>>> nodes;
        
        public:
            using Iterator<T>::current;
            using Iterator<T>::operator++;
            
            /**
             * Constructs a LevelIterator with the specified root and appends
             * the root to the queue if non-null.
             */
            LevelIterator(shared_ptr<Node<T>> root) : Iterator<T>(root) {
                nodes = week5::Queue<shared_ptr<Node<T>>>();
                if (current) {
                    nodes.enqueue(current);
                }
            }
            
            /**
             * Iterates through the iteration level-by-level.
             * 
             * @return true if the iteration has more elements; else false
             */
            bool operator++() override;  
    };
    
    /**
     * Sets the current node as the front and pops the queue before pushing the 
     * child nodes into the queue if the queue is not empty.
     */
    template <class T>
    bool LevelIterator<T>::operator++() {
        if (!nodes.empty()) {
            current = nodes.take();
            
            if (current->left) {
                nodes.enqueue(current->left);
            }
            if (current->right) {
                nodes.enqueue(current->right);
            }
            return true;
            
        } else {
            return false;
        }
    }
}

#endif /* ITERATOR_H */

