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
    tree.add(14).add(33).add(50).add(72).add(99).add(76).add(78).add(82).add(39).add(45);
//    
//    cout << tree.remove(72) << endl;
//    
//    cout << tree << endl;
    
    auto iterator = tree.iterator(Traversal::ASCENDING);
    while ((*iterator)++) {
        auto value = iterator->get();
        cout << (*value);
    }
    
    return 0;
}

