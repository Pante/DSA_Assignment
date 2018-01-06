/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.h
 * Author: Karus Labs
 *
 * Created on January 5, 2018, 12:04 PM
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include <string>

using namespace std;


template <class T, bool Recursive>
struct Node {
    
    T item;
    Node<T>* left;
    Node<T>* right;
    unsigned int height;
    
    
    Node(T item) : item {item}, left {nullptr}, right {nullptr}, height {1} {}
    
};


template <class T>
class AVLTree {
    
private:
    Node<T>* root;
    
public:
    AVLTree() : root {nullptr} {}
        
    
    void add(T item);
    
    bool contains(T& item) const;
    
    void remove(T item);
    
    
    void displayAscending(ostream& stream = cout);
    
    void display(int index, ostream& stream = cout);
    
};


template <class T>
void AVLTree::add(T item) {
    
}

template <class T>
bool AVLTree::contains(T& item) const {
    return contains(root, item, "message");
}

template <class T>
bool contains(Node<T>* node, T& item, string message) {
    cout << message << endl;
    
    if (node == nullptr) {
        return false;
    }
    
    if (node->item == item) {
        return true;
        
    } else {
        return contains(node->left, item, "Left") || contains(node->right, item, "right");
    }
}


template <class T>
void AVLTree::remove(T item) {
    
}


template <class T>
void AVLTree::displayAscending(ostream& stream = cout) {
    
}

template <class T>
void AVLTree::display(int index, ostream& stream = cout) {
    
}


#endif /* AVLTREE_H */

