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
 * File:   Queue.h
 * Author: Matthias Ngeo - S10172190F
 * Author: Francis Koh - S10172072G
 *
 * Created on January 18, 2018, 10:59 PM
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdexcept>

using namespace std;

namespace assignment {
    
    /**
     * Represents a node which is used in a queue and holds a reference to the previous element.
     */
    template <class T = int>
    struct QueueNode {
        
        T value;
        QueueNode<T>* previous;
        
        /**
         * Constructs a QueueNode with the specified value and no reference to the previous node.
         * 
         * @param value the value
         */
        QueueNode(T value) {
            this->value = value;
            this->previous = nullptr;
        }
        
    };
    
    /**
     * Represents a queue based on linked nodes. The tail of the queue is that element 
     * that has been on the queue the shortest time. New elements are inserted at the tail 
     * of the queue, and the retrieval operations obtain elements from the head of the queue. 
     */
    template <class T>
    class Queue {
        private:
            QueueNode<T>* head;
            QueueNode<T>* tail;
            int size;
            
        public:
            /**
             * Constructs an empty Queue.
             */
            Queue();
            
            /**
             * Adds the specified element at the tail of the queue.
             * 
             * @param element the item to add 
             */
            void push(T& element);
            
            /**
             * Removes the element at the head of the queue.
             */
            void pop();
            
            /**
             * Returns a reference to the element at the head of the queue but does not remove it.
             * 
             * @return the element
             */
            T& front();
            
            /**
             * Returns whether the queue is empty.
             * 
             * @return true if the queue is empty; else false
             */
            bool empty();
    };
    
    
    template <class T>
    Queue<T>::Queue() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }
    
    template <class T>
    void Queue<T>::push(T& element) {
        auto node = new QueueNode<T>(element);
        if (size == 0) {
            head = node;
            tail = node;
            
        } else if (head == tail) {
            head->previous = node;
            tail = node;
            
        } else {
            tail->previous = node;
            tail = node;   
        }
        
        size++;
    }
    
    template <class T>
    void Queue<T>::pop() {
        if (size == 0) {
            return;
            
        } else if (size == 1) {
            delete head;
            delete tail;
            head = nullptr;
            tail = nullptr;
            
        } else {
            auto old = head;
            head = head->previous;
            delete old;
        }
        
        size--;
    }
   
    template <class T>
    T& Queue<T>::front() {
        if (size == 0) {
            throw invalid_argument("Queue is empty");
        }
        
        return head->value;
    }
    
    template <class T>
    bool Queue<T>::empty() {
        return size == 0;
    }
    
}

#endif /* QUEUE_H */

