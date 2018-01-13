/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: Karus Labs
 *
 * Created on January 5, 2018, 12:03 PM
 */

#include <cstdlib>
#include <iostream>

#include "Node.h"
#include "Iterator.h"

using namespace assignment;
using namespace std;

int main(int argc, char** argv) {
    
    auto node = make_shared<Node<int>>(2);
    node->left = make_shared<Node<int>>(1);
    node->right = make_shared<Node<int>>(3);
    
    node->left->parent = node;
    node->right->parent = node;
    
    auto ascending = AscendingIterator<int>(node);
    auto level = LevelIterator<int>(node);
    
    while (ascending++) {
        cout << "ASCENDING: " << ascending->value << endl;

    }

    return 0;
}

