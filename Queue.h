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
 * File:   Queue.h
 * Author: Karus Labs
 *
 * Created on January 18, 2018, 10:59 PM
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <memory>
#include <stdexcept>

using namespace std;

namespace assignment {
    
    /**
     * Represents a node which is used in the queue.
     */
    template <class T = int>
    struct QueueNode {
        
        T value;
        shared_ptr<QueueNode<T>> previous;
        
        QueueNode(T value, shared_ptr<QueueNode<T>> previous = shared_ptr<QueueNode<T>>(nullptr)) {
            this->value = value;
            this->previous = previous;
        }
        
    };
    
    /**
     * Represents a queue with a linked list implementation.
     */
    template <class T>
    class Queue {
        private:
            shared_ptr<QueueNode<T>> head;
            shared_ptr<QueueNode<T>> tail;
            int size;
            
        public:
            Queue();
            
            void push(T& item);
            
            void pop();
            
            T& front();
            
            bool empty();
    };
    
    /**
     * Constructs a Queue.
     */
    template <class T>
    Queue<T>::Queue() {
        head = shared_ptr<QueueNode<T>>(nullptr);
        tail = shared_ptr<QueueNode<T>>(nullptr);
        size = 0;
    }
    
    /**
     * Adds the specified item to the tail of the queue.
     */
    template <class T>
    void Queue<T>::push(T& item) {
        auto node = make_shared<QueueNode<T>>(item);
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
    
    /**
     * Removes the item at the head of the queue.
     */
    template <class T>
    void Queue<T>::pop() {
        if (size == 0) {
            return;
            
        } else if (size == 1) {
            head = nullptr;
            tail = nullptr;
            
        } else {
            head = head->previous;
        }
        
        size--;
    }
    
    /**
     * Returns the element at the head of the queue.
     * 
     * @return
     * @throws invalid_argument if the queue is empty
     */
    template <class T>
    T& Queue<T>::front() {
        if (size == 0) {
            throw invalid_argument("Queue is empty");
        }
        
        return head->value;
    }
    
    /**
     * Returns whether the queue is empty.
     * 
     * @return true if empty; else false
     */
    template <class T>
    bool Queue<T>::empty() {
        return size == 0;
    }
    
}

#endif /* QUEUE_H */

