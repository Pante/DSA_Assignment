/*
 * The MIT License
 *
 * Copyright 2018 PohSeng#1.
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
 * Author: Matthias Ngeo - S10172190F
 * Author: Francis Koh - S10172072G
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
     * Represents the traversal type of an iterator.
     */
    enum Traversal {
        ASCENDING, LEVEL
    };
    
    /**
     * Represents an iterator over the elements in an AVL tree.
     */
    template <class T>
    class Iterator {
        protected:
            shared_ptr<Node<T>> current;
        
        public:
            /**
             * Constructs an Iterator with the specified root node.
             * 
             * @param the root node of the AVL tree
             */
            Iterator(shared_ptr<Node<T>> root);
            
            /**
            * Iterates to the next element in the iteration.
            * 
            * @return true if the iteration has more elements; else false
            */
            virtual bool operator++(int);
            
            /**
            * Iterates to the next element in the iteration.
            * 
            * Subclasses should override this method to implement the traversal of elements.
            * 
            * @return true if the iteration has more elements; else false
            */
            virtual bool operator++() =0;
            
            /**
             * Returns the current element in the iteration
             * 
             * @return the current element
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
     * A concrete subclass of Iterator over the elements in an AVL tree.
     * The elements will be returned in ascending order, starting from the element with the smallest
     * value to the element with the largest value.
     */
    template <class T>
    class AscendingIterator : public Iterator<T> {
        private:
            /**
             * Represents the direction of the traversal.
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
             * set the direction to RIGHT, or END if the specified root is null.
             */
            AscendingIterator(shared_ptr<Node<T>> root) : Iterator<T>(root) {
                current = root;
                right = root;
                direction = (current == nullptr) ? Direction::END : Direction::RIGHT;
            }
            
            /**
            * Iterates to the next element in the iteration in an ascending order.
            * 
             * @implSpec
             * The method first determines the direction of the traversal.
             * 
             * If the direction is RIGHT, it sets the right child of the previous element as the current element.
             * After which, it sets the it sets the left-most leaf element of the current element as the next node,
             * and sets the direction to PARENT if the current element has no right child; else sets the right element
             * as the right child of the current element.
             * Always returns true.
             * 
             * If the direction is PARENT, it iterates through the parents of the elements starting from the current
             * element while the element has a parent. If the left child of element is equal to the current element,
             * set the right child of the current element as the next right element and sets the direction to RIGHT 
             * if the next right element exists and returns true. Otherwise if the element has no parent, set the direction
             * as END and return false.
             * 
             * Otherwise returns false if the direction is END.
             * 
            * @return true if the iteration has more elements; else false
            */
            bool operator++() override;
    };
    
    
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
     * A concrete subclass of Iterator over the elements in an AVL tree.
     * The elements will be returned level-by-level, starting from the root element to the leaf
     * elements, in left to right order.
     */
    template <class T>
    class LevelIterator : public Iterator<T> {
        private:
            Queue<shared_ptr<Node<T>>> nodes;
        
        public:
            using Iterator<T>::current;
            using Iterator<T>::operator++;
            
            /**
             * Constructs a LevelIterator with the specified root and pushes the root to the queue if non-null.
             */
            LevelIterator(shared_ptr<Node<T>> root) : Iterator<T>(root) {
                nodes = Queue<shared_ptr<Node<T>>>();
                if (current) {
                    nodes.push(current);
                }
            }
            
            /**
            * Iterates to the next element in the iteration, level-by-level.
            * 
             * @implSpec
             * If the queue is not empty, set the element at the head of the queue as the 
             * current element and pop the queue before adding the left and right child
             * of the current element to the queue if they exist respectively.
             * 
             * Otherwise returns false if the queue is empty.
             * 
            * @return true if the iteration has more elements; else false
            */
            bool operator++() override;  
    };
    
    
    template <class T>
    bool LevelIterator<T>::operator++() {
        if (!nodes.empty()) {
            current = nodes.front();
            nodes.pop();
            
            if (current->left) {
                nodes.push(current->left);
            }
            if (current->right) {
                nodes.push(current->right);
            }
            return true;
            
        } else {
            return false;
        }
    }
}

#endif /* ITERATOR_H */

