/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Tree.h
 * Author: Karus Labs
 *
 * Created on January 7, 2018, 3:14 PM
 */

#ifndef TREE_H
#define TREE_H

#include <iostream>
#include "Node.h"


namespace Assignment {
    
    template <class T>
    class AVLTree {
        
        private:
            Node<T>* root;
            unsigned int size;
            
            void balance(Node<T>* node);
            
            
        public:
            Node();
            
            
            bool contains(T item);
            
            void add(T item);
            
            void remove(T item);
                        
            Node<T>* find(int index);
            
            void ascending(Node<T>* node = root, std::ostream& stream = std::cout);
            
            unsigned int size();
            
                        
            friend std::ostream& operator<<(std::ostream& stream, const AVLTree<T>& tree) {
                ascending(stream);
                return stream;
            }
            
    };
    
    
    template <class T>
    AVLTree::Node() {
        root = nullptr;
        size = 0;
    }
    
    
    template <class T>
    bool AVLTree::contains(T item, std::ostream& stream = std::cout) {
        if (root != nullptr && root->item == item) {
            stream << "root" << std::endl;
            return true;
        }
        
        Node<T>* node = root;
        while (node) {
            if (node->item < item) {
                node = node->right;
                stream << "Right" << std::endl;
                
            } else if (node->item > item) {
                node = node->left;
                stream << "Left" << std::endl;
                
            } else {
                return true;
            }
        }
        
        return false;
    }
    
    
    template <class T>
    void AVLTree::add(T item) {
        Node<T>* node = root;
        while (node) {
            node->add(item);
        }
        
        if (node->amount == 1) {
            balance(node);
        }
    }
    
    template <class T>
    void AVLTree::balance(Node<T>* node) {
        node->parent
    }
    
    
    template <class T>
    void AVLTree::remove(T item) {
        
    }
    
    
    template <class T>
    Node<T>* AVLTree::find(int index) {
        
    }
    
    
    template <class T>
    void AVLTree::ascending(Node<T>* node = root, std::ostream& stream = std::cout) {
        if (node != nullptr) {
            ascending(node->left, stream);
            stream << *node << std::endl;
            ascending(node->right, stream);
        }
    }
    
    
    template <class T>
    unsigned int AVLTree::size() {
        return size;
    }
    
}

#endif /* TREE_H */

