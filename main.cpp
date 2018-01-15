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
#include <memory>
#include <iostream>

#include "Node.h"
#include "Iterator.h"
#include "Tree.h"

using namespace assignment;
using namespace std;

int main(int argc, char** argv) {
    
    AVLTree<int> tree {};
    tree.add(2);
    tree.add(2);
    tree.add(3);
    
    try {
        cout << tree << endl;
        cout << "nodes: " << tree.nodes() << " size: " << tree.size() << endl;
        
        tree.remove(2);
        
        cout << tree << endl;
        cout << "nodes: " << tree.nodes() << " size: " << tree.size() << endl;
    } catch (invalid_argument) {
        cout << "Error" << endl;
    }
    
    
    return 0;
}

