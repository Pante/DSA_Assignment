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
 * File:   Tree.h
 * Author: Karus Labs
 *
 * Created on January 8, 2018, 3:27 PM
 */

#ifndef TREE_H
#define TREE_H

#include <stdexcept>

#include "Iterator.h"
#include "Node.h"
#include "Balance.h"

namespace assignment {
    
    template <class T>
    class AVLTree {
        
        private:            
            Node<T>* root;
            Balance<T> balance;
            unsigned int total;
            unsigned int nodes;
            
            Node<T>* add(Node<T>* node, Node<T>*& child, T value, int balance);
            
            void rotateLeft(Node<T>* node);
            
            void rotateRight(Node<T>* node);
            
            void rotateLeftRight(Node<T>* node);
            
            void rotateRightLeft(Node<T>* node);
            
        public:
            AVLTree();
            
            
            void add(T value);
            
            void remove(T value);
            
            T get(unsigned int index, Traversal traversal = Traversal::LEVEL);
            
            bool contains(T value, std::ostream& stream = std::cout);
            
            template <class U>
            friend std::ostream& operator<<(std::ostream& stream, const AVLTree<U>& tree);
            
            Iterator<T> iterator(Traversal traversal);
            
            unsigned int size();
            
    };
    
    
    template <class T>
    AVLTree<T>::AVLTree() {
        root = nullptr;
        balance = Balance<T>();
        total = 0;
        nodes = 0;
    }
    
    
    template <class T>
    void AVLTree<T>::add(T value) {
        Node<T>* node = root;
        while (node) {
            if (node->value < value) {
                node = add(node, node->right, value, 1);
                
            } else if (node->value > value) {
                node = add(node, node->right, value, -1);
                
            } else {
                node->amount++;
                break;
            }
        }
        size++;
    }
    
    
    template <class T>
    Node<T>* AVLTree<T>::add(Node<T>* node, Node<T>*& child, T value, int balance) {
        if (child) {
            return child;
            
        } else {
            child = new Node<T>(value, node);
            this->balance->add(root, node, balance);
            nodes++;
            return nullptr;
        }
    }
    
    
    template <class T>
    void AVLTree<T>::remove(T value) {
        
    }
    
    
    template <class T>
    T AVLTree<T>::get(unsigned int index, Traversal traversal) {
        if (index >= nodes) {
            throw std::out_of_range("Index is out of range: " + index);
        }
        
        Iterator<T> iterator = iterator(traversal);
        for (unsigned int i = 0; i < index; i++) {
            iterator.next();
        }
        
        return iterator.next()->value;
    }
    
    
    template <class T>
    bool AVLTree<T>::contains(T value, std::ostream& stream) {
        if (size == 1 && root->value == value) {
            stream << "root" << std::endl;
            return true;
        }
        
        Node<T>* node = root;
        while (node) {
            if (node->value < value) {
                node = node->right;
                stream << "Right" << std::endl;
                
            } else if (node->value > value) {
                node = node->left;
                stream << "Left" << std::endl;
                
            } else {
                return true;
            }
        }
        
        return false;
    }
    
    
    template <class T>
    std::ostream& operator<<(std::ostream& stream, const AVLTree<T>& tree) {
        Iterator<T> iterator = tree->iterator(Traversal::ASCENDING);
        Node<T>* node;
        while ((node = iterator.next())) {
            stream << node;
        }
        return stream;
    }
    
    
    template <class T>
    Iterator<T> AVLTree<T>::iterator(Traversal traversal) {
        switch (traversal) {
            case Traversal::ASCENDING:
                return AscendingIterator<T>(root);
                
            case Traversal::LEVEL:
                return LevelIterator<T>(root);
                
            default:
                throw std::invalid_argument();
        }
    }
    
    
    template <class T>
    unsigned int AVLTree<T>::size() {
        return total;
    }
    
}

#endif /* TREE_H */

