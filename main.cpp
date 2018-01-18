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
#include <functional>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>

#include "Node.h"
#include "Iterator.h"
#include "Tree.h"

using namespace assignment;
using namespace std;


using Predicate = bool (*)(int);


void menu(ostream& stream = cout) {
    stream << "-----------------------" << endl;
    stream << "1. Add a value" << endl;
    stream << "2. Remove a value" << endl;
    stream << "3. Search for a value" << endl;
    stream << "4. Get value at index" << endl;
    stream << "5. Display values" << endl;
    stream << "6. Exit" << endl;
    stream << "------------------------" << endl;
}

int input(string message, string error = "Value must be an integer", function<bool (int)> predicate = [](int value) {return true;}, istream& in = cin, ostream& out = cout) {
    string unparsed;
    stringstream stream;
    int value;
    char remainder;
    
    while (true) {
        out << message << endl;
        in >> unparsed;
        stream << unparsed;
        
        if (stream >> value && !(stream >> remainder) && predicate(value)) {
            return value;
        
        } else {
            in.clear();
            in.ignore(numeric_limits<streamsize>::max(), '\n');

            stream.str("");
            stream.clear();
                
            out << error << endl;
        }
    }
    
}

int main(int argc, char** argv) {
    AVLTree<int> tree {};
    while (true) {
        menu();
        switch (input("Please enter an option: ", "Option must be an integer between 1 and 6", [](int option){return 1 <= option && option <= 6;})) {
            case 1:
                tree.add(input("Please enter the value to add: "));
                cout << "Successfully added the value" << endl;
                break;
                
            case 2:
                if (tree.remove(input("Please enter the value to remove: "))) {
                    cout << "Successfully removed the value" << endl;
                    
                } else {
                    cout << "Failed to remove the value, as it was not present in the tree" << endl;
                }
                break;
                
            case 3:
                if (tree.contains(input("Please enter the value to search for: "))) {
                    cout << "Value is present in the tree" << endl;
                    
                } else {
                    cout << "Value was not present in the tree" << endl;
                }
                break;
            
            case 4: {
                auto index = input("Please enter the index of the node: ", "Index must be between 0 and " + tree.nodes(), [&tree](int value){return 0 <= value && value < tree.nodes();});
                cout << "The value at " << index << " is " << tree[index] << endl;
                break;
            }
                
            case 5:
                cout << tree << endl;
                break;
                
            case 6:
                cout << "Enter any key(s) to exit: " << endl;
                string wait;
                cin >> wait;
                return 0;
                
        }
    }
    
    return 0;
}

