/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Node.h
 * Author: Karus Labs
 *
 * Created on January 7, 2018, 3:06 PM
 */

#ifndef NODE_H
#define NODE_H

#include <iostream>

namespace Assignment {
    
    template <class T>
    struct Node {
        
        T item;
        unsigned int amount;
        unsigned int height;
        unsigned int balance;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;
        
        
        Node(T item, Node<T>* parent = nullptr) {
            this->item = item;
            amount = 1;
            height = 1;
            balance = 0;
            this->parent = parent;
            left = nullptr;
            right = nullptr;
        }
        
        
        Node<T>* add(T item) {
            if (this->item < item) {
                return add(&right, item);
                
            } else if (this-> item > item) {
                return add(&left, item);
                
            } else {
                amount++;
                return nullptr;
            }
        }
        
        Node<T>* add(Node<T>** node, T item) {
            if (*node == nullptr) {
                *node = new Node(item, this);
                return nullptr;
                
            } else {
                return *node;
            }
        }

        
        friend std::ostream& operator<<(std::ostream& stream, const Node<T>& node) {
            for (int i = 0; i < node->amount; i++) {
                stream << "value: " << node->item << std::endl;
            }
            return stream;
        }
        
    };
    
}

#endif /* NODE_H */

