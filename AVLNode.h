/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLNode.h
 * Author: Karus Labs
 *
 * Created on January 7, 2018, 12:56 PM
 */

#ifndef AVLNODE_H
#define AVLNODE_H

#include <iostream>


namespace Assignment {
    
    template <class T>
    struct Node {
        
        T item;
        unsigned int amount;
        Node<T>* parent;
        Node<T>* left;
        Node<T>* right;

        
        Node(T item) : item {item}, amount {0}, parent {nullptr}, left {nullptr}, right {nullptr} {}
        
        
        Node<T>** add(T item) {
            if (this->item == item) {
                amount++;
                return nullptr;
                
            } else if (this->item < item) {
                
                
            } else {
                
            }
        }
        
        
        friend std::ostream& operator<<(std::ostream& stream, const Node<T>& node) {
            stream << "value: " << node->item << " amount: " << node->amount << std::endl;
            return stream;
        }
        
        
        friend bool operator==(const Node<T>& left, const Node<T>& right) {
            return left->item == right->item;
        }
        
        friend bool operator!=(const Node<T>& left, const Node<T>& right) {
            return !(left == right);
        }
        
        friend bool operator<(const Node<T>& left, const Node<T>& right) {
            return left->item < right->item;
        }
        
        friend bool operator> (const Node<T>& left, const Node<T>& right){ 
            return right < left; 
        }
        
        friend bool operator<=(const Node<T>& left, const Node<T>& right){ 
            return !(left > right); 
        }
        
        friend bool operator>=(const Node<T>& left, const Node<T>& right){ 
            return !(left < right); 
        }
        
    };
    
}


#endif /* AVLNODE_H */

