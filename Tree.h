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

namespace Assignment {
    
    template <class T>
    class AVLTree {
        
        private:
            Node<T>* root;
            unsigned int size;
            unsigned int nodes;
            
        public:
            AVLTree();
            
            
            void add(T value);
            
            void remove(T value);
            
            T get(unsigned int index);
            
            bool contains(T value);
            
            friend std::ostream& operator<<(std::ostream& stream, const AVLTree<T>& tree);
            
            Iterator<T> iterator(Traversal traversal);
            
            unsigned int size();
            
            
        protected:
            void balanceAddition(Node<T>* node, int balance);
            
            void balanceRemoval(Node<T>* node, int balance);
            
            // TODO rotation methods
            
    };
    
    
    template <class T>
    AVLTree::AVLTree() {
        root = nullptr;
        size = 0;
        nodes = 0;
    }
    
    
    template <class T>
    void AVLTree::add(T value) {
        
    }
    
    template <class T>
    void AVLTree::balanceAddition(Node<T>* node, int balance) {
        
    }
    
    
    template <class T>
    void AVLTree::remove(T value) {
        
    }
    
    template <class T>
    void AVLTree::balanceRemoval(Node<T>* node, int balance) {
        
    }
    
    
    template <class T>
    T AVLTree::get(unsigned int index) {
        if (index >= nodes) {
            throw std::out_of_range("Index is out of range: " + index);
        }
        
        Iterator iterator = iterator(Traversal::LEVEL);
        for (unsigned int i = 0; i < index; i++) {
            iterator.next();
        }
        
        return iterator.next()->value;
    }
    
    
    template <class T>
    bool AVLTree::contains(T value, std::ostream& stream = std::cout) {
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
    friend std::ostream& operator<<(std::ostream& stream, const AVLTree<T>& tree) {
        Iterator iterator = iterator(Traversal::ASCENDING);
        Node<T>* node;
        while ((node = iterator.next())) {
            stream << node;
        }
        return stream;
    }
    
    
    template <class T>
    Iterator<T> AVLTree::iterator(Traversal traversal) {
        switch (traversal) {
            case Traversal::ASCENDING:
                return AscendingIterator(root);
                
            case Traversal::LEVEL:
                return LevelIterator(root);
                
            default:
                throw std::invalid_argument();
        }
    }
    
    
    template <class T>
    unsigned int AVLTree::size() {
        return size;
    }
    
}

#endif /* TREE_H */

