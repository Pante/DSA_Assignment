#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <stdexcept>

using namespace std;

namespace week5 {

    template <class T>
    struct Node {

        Node<T>* previous;
        Node<T>* next;
        T item;


        Node(T item) : previous {nullptr}, next {nullptr}, item {item} {

        }

    };


    template <class T>
    class Queue {

    public:
        Queue();
        ~Queue();

        bool enqueue(T& newItem);

        bool dequeue();

        T take();

        T& peek(); 

        void print();

        bool empty(); 


    private:
        Node<T>* head;
        Node<T>* tail;
        int size;
    };

    template <class T> Queue<T>::Queue() : head {nullptr}, tail {nullptr}, size {0} {}

    template <class T> Queue<T>::~Queue() {
        if (tail != nullptr) {
            Node<T>* current = tail;
            while (current) {
                Node<T>* next = current->next;
                delete current;
                current = next;
            }
        }
    }

    template <class T> bool Queue<T>::enqueue(T& item) {
        Node<T>* node = new Node<T>(item);
        if (size == 0) {
            tail = node;
            head = node;

        } else if (size == 1) {
            tail->previous = node;
            tail = node;
            tail->next = head;

        } else {
            Node<T>* old = tail->previous;
            old->previous = node;
            tail = node;
            tail->next = old;
        }

        size++;
        return true;
    }

    template <class T> bool Queue<T>::dequeue() {
        if (size == 0) {
            return false;
        }

        if (size == 1) {
            delete head;
            head == nullptr;
            head == nullptr;

        } else if (size == 2) {
            delete head;
            head = tail;
            head->previous = nullptr;
            head->next == nullptr;

        } else {
            Node<T>* node = head->previous;
            delete head;
            head = node;
            head->next = nullptr;
        }

        size--;
        return true;
    }

    template <class T> T Queue<T>::take() {
        if (size == 0) {
            throw out_of_range("Stack is empty");
        }

        T item = head->item;
        if (size == 1) {
            delete head;
            head == nullptr;
            head == nullptr;

        } else if (size == 2) {
            delete head;
            head = tail;
            head->previous = nullptr;
            head->next == nullptr;

        } else {
            Node<T>* node = head->previous;
            delete head;
            head = node;
            head->next = nullptr;
        }

        size--;
        return item;
    }

    template <class T> T& Queue<T>::peek() {
        if (size > 0) {
            return head->item;

        } else {
            throw out_of_range("stack is empty");
        }
    }

    template <class T> void Queue<T>::print() {
        Node<T>* node = head;
        while (node) {
            cout << node->item << endl;
            node = node->previous;
        }
    }

    template <class T> bool Queue<T>::empty() {
        return size == 0;
    }
}

#endif /* QUEUE_H */

