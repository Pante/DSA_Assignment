/*
 * The MIT License
 *
 * Copyright 2018 PohSeng#1.
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
 * File:   main.cpp
 * Author: Matthias Ngeo - S10172190F
 * Author: Francis Koh - S10172072G
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


/**
 * Displays the menu using the specified ostream.
 * 
 * @param stream the ostream used to display the menu, or cout if unspecified
 */
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

/**
 * Prompts the user for input using the specified message while the input cannot be
 * parsed to an integer and does not satisfy the specified predicate, returning the parsed integer
 * if the predicate has been satisfied.
 * 
 * @param message the message which is used to prompt the user for input
 * @param error the message which is displayed when the input cannot be parsed to an integer, or does not satisfy the predicate, or "Value must be an integer" if unspecified
 * @param predicate an additional predicate which the integer must satisfy, or always returns true if unspecified
 * @param istream the istream which is used to retrieve the user input
 * @param ostream the ostream which is used to display the messages
 */
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

/**
 * Contains the main programme loop.
 */
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
                    cout << "Failed to remove the value as it was not present in the tree" << endl;
                }
                break;
                
            case 3:
                if (tree.contains(input("Please enter the value to search for: "))) {
                    cout << "Value is present in the tree" << endl;
                    
                } else {
                    cout << "Value is not present in the tree" << endl;
                }
                break;
            
            case 4: {
                if (tree.size() > 0) {
                    auto index = input("Please enter the index of the node: ", "Index must be between 0 and " + to_string(tree.nodes()), [&tree](int value){return 0 <= value && value < tree.nodes();});
                    cout << "The value at " << index << " is " << tree[index] << endl;
                    
                } else {
                    cout << "The tree is empty." << endl;
                }
                
                break;
            }
                
            case 5:
                cout << "Tree: " << endl << tree << endl;
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

