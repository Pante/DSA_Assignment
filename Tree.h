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
 * Created on January 13, 2018, 4:35 PM
 */

#ifndef TREE_H
#define TREE_H

#include "Node.h"


using namespace std;

namespace assignment {
    
    template <class T>
    class AVLTree {
        private:
            shared_ptr<Node<T>> root;
            unsigned int total;
            
            
            
        public:
            AVLTree();
            
            void add(T value);
            
            bool contains(T value);
            
            bool remove(T value);
            
            unique_ptr<Iterator<T>> iterator();
            
            T operator[](int index);
        
            friend ostream& operator<<(ostream& stream, const AVLTree<T>& tree);
            
            unsigned int size();
    };
    
    template <class T>
    AVLTree<T>::AVLTree() {
        root = shared_ptr<Node<T>>(nullptr);
        nodes = 0;
        total = 0;
    }
    
    template <class T>
    void AVLTree<T>::add(T value) {
        if (root) {
            auto node = root;
            while (node) {
                if (node->value < value) {
                    
                } else if (node->value > value) {
                    
                } else {
                    node->amount++;
                }
            }
            
        } else {
            root = make_shared<Node<T>>(value);
        }
        total++;
    }
    
}

#endif /* TREE_H */

