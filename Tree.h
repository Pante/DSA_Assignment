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
 * File:   Tree.h
 * Author: Matthias Ngeo - S10172190FF
 * Author: Francis Koh - S10172072G
 *
 * Created on January 13, 2018, 4:35 PM
 */

#ifndef TREE_H
#define TREE_H

#include <memory>
#include <stdexcept>

#include "Node.h"
#include "Iterator.h"


using namespace std;

namespace assignment {
    
    /**
     * Represents an AVL tree. The implementation is non-recursive and provides 
     * a guaranteed time complexity of O(log(n)) for the basic operations (add, remove and contains), 
     * and a guaranteed time complexity of O(n) for additional operations (operator<< and operator[]).
     */
    template <class T>
    class AVLTree {
        private:
            shared_ptr<Node<T>> root;
            int values;
            int total;
            
            
            /**
             * Creates and adds the child node with the specified value, balance and parent
             * before balancing the tree, if the child is null; else returns the child.
             * 
             * @param value the value to add
             * @param parent the parent of the child node
             * @param child the child node
             * @param the balance to add if the child is created
             * @return the child node if not null; else null
             */
            shared_ptr<Node<T>> add(T value, shared_ptr<Node<T>> parent, shared_ptr<Node<T>>& child, int balance);
            
            /**
             * Balances the tree after addition.
             * 
             * @implSpec
             * Iterates through the parents of the nodes, starting from the specified node 
             * and updates the balance each time before delegating rotation to appropriate
             * method which depends on the balance.
             * 
             * A balance of 0 indicates that the tree has been fully balanced and the loop terminates.
             * 
             * @param node the parent of the node which was added
             * @param the resultant balance after the addition
             */
            void balanceAddition(shared_ptr<Node<T>> node, int balance);
            
            
            /**
             * Removes the specified node and balances the tree.
             * 
             * @param node the node to remove
             */
            void remove(shared_ptr<Node<T>> node);
            
            /**
             * Removes the specified node which has both a left and right child, and balances the tree.
             * 
             * @implSpec
             * Iterates through the left children of the specified node's right child while it exists
             * before replacing the specified node with the left-most child if the right child has a 
             * left child; else replaces the specified node with its right child.
             * 
             * @param node the node to remove
             */
            void removeMiddle(shared_ptr<Node<T>> node);
            
            /**
             * Balances the tree after removal.
             * 
             * @implSpec
             * Iterates through the parents of the nodes, starting from the specified node 
             * and updates the balance each time before delegating rotation to appropriate
             * method which depends on the balance.
             * 
             * A balance of either 1 or -1 indicates that the tree has been balanced.
             * 
             * @param node the parent of the node which was removed
             * @param the resultant balance after the removal
             */
            void balanceRemoval(shared_ptr<Node<T>> node, int balance);
            
            
            /**
             * Sets the specified node as the left child of its right child, before
             * setting the parent of the specified node as the parent of its right child
             * and updating the balance of the right child.
             * 
             * @param node the node to rotate
             * @return the right child of the specified node
             */
            shared_ptr<Node<T>> rotateLeft(shared_ptr<Node<T>> node);
            
            /**
             * Sets the specified node as the right child of its left child, before
             * setting the parent of the specified node as the parent of its left child
             * and updating the balance of the left child.
             * 
             * @param node the node to rotate
             * @return the left child of the specified node
             */
            shared_ptr<Node<T>> rotateRight(shared_ptr<Node<T>> node);
            
            
            /**
             * Sets the specified node as the right child of the right node of its left child and
             * the left child as the child as the left child of its right node before
             * setting the left child of the right node as the right child of the left node and the
             * right child of the right node as the left child of the specified node.
             * 
             * Essentially:
             * [N] = the specified node
             * 
             *         [P]                     [P]
             *          |                       |
             *         [N]                     [LR]
             *        /   \                   /    \
             *     [L]     [?]     =>      [L]      [N]
             *    /   \                   /   \    /   \
             * [?]     [LR]            [?]  [LRL][LRR]  [?]
             *        /    \
             *   [LRL]      [LRR]
             * 
             * @param node the node to rotate
             * @return the right child of the left node
             */
            shared_ptr<Node<T>> rotateLeftRight(shared_ptr<Node<T>> node);
            
            /**
             * Sets the specified node as the left child of the left node of its right child and
             * the right child as the child as the right child of its left node before
             * setting the right child of the left node as the left child of the right node and the
             * left child of the left node as the right child of the specified node.
             * 
             * Essentially:
             * [N] = the specified node
             * 
             *       [P]                     [P]
             *        |                       |
             *       [N]                     [RL]
             *      /   \                   /    \
             *   [?]     [R]      =>     [N]      [R]
             *          /   \           /   \    /   \
             *       [RL]    [?]     [?]  [RRL][RRR]  [?]
             *      /    \
             * [RRL]      [RRR]
             * 
             * @param node the node to rotate
             * @return the right child of the left node
             */
            shared_ptr<Node<T>> rotateRightLeft(shared_ptr<Node<T>> node);
            
            
        public:
            /**
             * Constructs an empty AVL tree.
             */
            AVLTree();
            
            /**
             * Adds the specified value.
             * 
             * @implSpec
             * Creates the root if the tree is empty; else iterates through the nodes 
             * in the tree starting from the root while the current node is not null. 
             * If the value is either larger than or smaller than the current node, delegate the addition 
             * to #add(T value, shared_ptr<Node<T>> parent, shared_ptr<Node<T>> child, int balance).
             * Otherwise increase the amount of the current node and return.
             * 
             * @param value the value to add
             * @return this
             */
            AVLTree<T>& add(T value);
            
            /**
             * Returns whether the tree contains the specified value.             * 
             * 
             * @param value the value which the tree contains
             * @param stream the ostream used to display the path taken, or cin if unspecified
             * @return true if the tree contains the specified value; else false
             */
            bool contains(T value, ostream& stream = cout);
            
            /**
             * Removes the specified value.
             * 
             * @implSpec
             * Iterates through the nodes in the tree starting from the root while the current node is not null.
             * If the node is smaller than or larger than the value set the respective child nodes as the next node.
             * Otherwise if the node is equal to the specified value and the node amount is 1, delegates removal 
             * to #remove(shared_ptr<Node<T>> node), else decrease the amount and return.
             * 
             * @param value the value to remove
             * @return true if the value was successfully removed; else false
             */
            bool remove(T value);
            
            /**
             * Returns an iterator with the specified traversal type for the elements in the tree.
             * 
             * @param traversal the traversal type, or level-by-level if unspecified
             * @throws invalid_argument if the traversal type is unsupported
             * @return the iterator
             */
            shared_ptr<Iterator<T>> iterator(Traversal traversal = Traversal::LEVEL);
            
            /**
             * Returns the value of the node at the specified index.
             * 
             * @implSpec
             * Creates a level-by-level iterator using #iterator() and iterates through the nodes
             * until the specified index has been reached and the value of the node is returned.
             * This implementation ignores duplicate values and treats duplicate values as a single
             * node/iteration.
             * 
             * @param index the index of the node
             * @throws invalid_argument if the specified inex if less than 0 or greater than the number of nodes
             * @return the value of the node at the specified index
             */
            T operator[](int index);
            
            /**
             * Displays the tree using the specified ostream.
             * 
             * @param stream the ostream used to display the tree
             * @param the tree to display
             * @return the ostream
             */
            template <class V>
            friend ostream& operator<<(ostream& stream, const AVLTree<V>& tree);
            
            /**
             * Returns the number of nodes in the tree.
             * 
             * @return the number of nodes in the tree, excluding duplicate values
             */
            int nodes();
            
            /**
             * Returns the number of values in the tree.
             * 
             * @return the number of values in the tree, including duplicate values
             */
            int size();
    };
    
    template <class T>
    AVLTree<T>::AVLTree() {
        root = shared_ptr<Node<T>>(nullptr);
        values = 0;
        total = 0;
    }
    
    
    template <class T>
    AVLTree<T>& AVLTree<T>::add(T value) {
        if (!root) {
            root = make_shared<Node<T>>(value);
            values++;
            total++;
            return *this;
        }
        
        auto node = root;
        while (node) {
            if (node->value < value) {
                node = add(value, node, node->right, 1);
                
            } else if (node->value > value) {
                node = add(value, node, node->left, -1);
                
            } else {
                node->amount++;
                total++;
                return *this;
            }
        }
        
        return *this;
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::add(T value, shared_ptr<Node<T>> node, shared_ptr<Node<T>>& child, int balance) {
        if (!child) {
            child = make_shared<Node<T>>(value, node);
            balanceAddition(node, balance);
            values++;
            total++;
            return nullptr;
            
        } else {
            return child;
        }
    }
    
    template <class T>
    void AVLTree<T>::balanceAddition(shared_ptr<Node<T>> node, int balance) {
        while (node) {
            balance = (node->balance += balance);

            if (balance == 0) {
                return;
                
            } else if (balance == -2) {
                if (node->left->balance == -1) {
                    rotateRight(node);

                } else {
                    rotateLeftRight(node);
                }
                return;
                
            } else if (balance == 2) {
                if (node->right->balance == 1) {
                    rotateLeft(node);
                    
                } else {
                    rotateRightLeft(node);
                }
                return;
            }
            
            auto parent = node->parent;
            if (parent) {
                if (parent->left == node) {
                    balance = -1;
                    
                } else {
                    balance = 1;
                }
            }
            node = parent;
        }
    }
    
    
    template <class T>
    bool AVLTree<T>::contains(T value, ostream& stream) {
        auto node = root;
        if (root && root->value) {
            cout << "Root" << endl;
        }
        
        while (node) {
            if (node->value < value) {
                node = node->right;
                stream << "Right" << endl;
                
            } else if (node->value > value) {
                node = node->left;
                stream << "Left" << endl;
                
            } else {
                return true;
            }
        }
        
        return false;
    }
    
    
    template <class T>
    bool AVLTree<T>::remove(T value) {
        if (total == 1 && root->value == value) {
            root = nullptr;
            values--;
            total--;
            return true;
        }
        
        auto node = root;
        while (node) {
            if (node->value < value) {
                node = node->right;
                
            } else if (node->value > value) {
                node = node->left;
                
            } else {
                if (node->amount == 1) {
                    remove(node);
                    return true;
                    
                } else {
                    node->amount--;
                    total--;
                    return true;
                }
            }
        }
        
        return false;
    }
    
    template <class T>
    void AVLTree<T>::remove(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto right = node->right;
        if (left && right) {
            removeMiddle(node);
            
        } else if (left) {
            replace(left, node);
            balanceRemoval(node, 0);
            
        } else if (right) {
            replace(right, node);
            balanceRemoval(node, 0);
            
        } else {
            auto parent = node->parent;
            if (parent->left == node) {
                parent->left = nullptr;
                balanceRemoval(parent, 1);
                
            } else {
                parent->right = nullptr;
                balanceRemoval(parent, -1);
            }
        }
        values--;
        total--;
    }
    
    template <class T>
    void AVLTree<T>::removeMiddle(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto right = node->right;
        auto sucessor = right;
        auto parent = node->parent;
        
        if (sucessor->left) {
            while (sucessor->left) {
                sucessor = sucessor->left;
            }
            
            auto sucessorParent = sucessor->parent;
            auto sucessorRight = sucessor->right;
            
            sucessorParent->left = sucessorRight;
            if (sucessorRight) {
                sucessorRight->parent = sucessorParent;
            }
            
            sucessor->parent = parent;
            sucessor->left = left;
            sucessor->balance = node->balance;
            sucessor->right = right;
            
            right->parent = sucessor;
            left->parent = sucessor;
            
            if (node == root) {
                root = sucessor;
                
            } else if (parent->left == node) {
                parent->left = sucessor;
                
            } else {
                parent->right = sucessor;
            }
            
            balanceRemoval(sucessorParent, 1);
            
        } else {
            sucessor->parent = parent;
            sucessor->left = left;
            sucessor->balance = node->balance;
            left->parent = sucessor;
            
            if (node == root) {
                root = sucessor;
                
            } else if (parent->left == node) {
                parent->left = sucessor;
                
            } else {
                parent->right = sucessor;
            }
            
            balanceRemoval(sucessor, -1);
        }
    }
    
    template <class T>
    void AVLTree<T>::balanceRemoval(shared_ptr<Node<T>> node, int balance) {
        while (node) {
            balance = (node->balance += balance);
            if (balance == -2) {
                if (node->left->balance <= 0) {
                    node = rotateRight(node);
                    if (node->balance == 1) {
                        return;
                    }
                    
                } else {
                    node = rotateLeftRight(node);
                }
                
            } else if (balance == 2) {
                if (node->right->balance >= 0) {
                    node = rotateLeft(node);
                    if (node->balance == -1) {
                        return;
                    }
                    
                } else {
                    node = rotateRightLeft(node);
                }
            } else if (balance != 0) {
                return;
            }
            
            if (node->parent) {
                balance = node->parent->left ? 1 : -1;
            }
            
            node = node->parent;
        }
    }
    
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateLeft(shared_ptr<Node<T>> node) {
        auto right = node->right;
        auto rightLeft = right->left;
        auto parent = node->parent;
        
        right->parent = parent;
        right->left = node;
        node->right = rightLeft;
        node->parent = right;
        
        if (rightLeft) {
            rightLeft->parent = node;
        }
        
        if (node == root) {
            root = right;
            
        } else if (parent->left == node) {
            parent->left = right;
            
        } else {
            parent->right = right;
        }
        
        right->balance--;
        node->balance = right->balance;
        
        return right;
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateRight(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto leftRight = left->right;
        auto parent = node->parent;
        
        left->parent = parent;
        left->right = node;
        node->left = leftRight;
        node->parent = left;
        
        if (leftRight) {
            leftRight->parent = node;
        }
        
        if (node == root) {
            root = left;
            
        } else if (parent->left == node) {
            parent->left = left;
            
        } else {
            parent->right = left;
        }
        
        left->balance++;
        node->balance = left->balance;
        
        return left;
    }
    

    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateLeftRight(shared_ptr<Node<T>> node) {
        auto left = node->left;
        auto leftRight = left->right;
        auto parent = node->parent;
        
        auto leftRightRight = leftRight->right;
        auto leftRightLeft = leftRight->left;
        
        leftRight->parent = parent;
        node->left = leftRightRight;
        left->right = leftRightLeft;
        leftRight->left = left;
        leftRight->right = node;
        left->parent = leftRight;
        node->parent = leftRight;
        
        if (leftRightRight) {
            leftRightRight->parent = node;
        }
        
        if (leftRightLeft) {
            leftRightLeft->parent = left;
        }
        
        if (node == root) {
            root = leftRight;
            
        } else if (parent->left == node) {
            parent->left = leftRight;
            
        } else {
            parent->right = leftRight;
        }
        
        if (leftRight->balance == 1) {
            node->balance = 0;
            left->balance = -1;
            
        } else if (leftRight->balance == -1) {
            node->balance = 1;
            left->balance = 0;
            
        } else {
            node->balance = 0;
            left->balance = 0;
        }
        
        return leftRight;
    }
    
    template <class T>
    shared_ptr<Node<T>> AVLTree<T>::rotateRightLeft(shared_ptr<Node<T>> node) {
        auto right = node->right;
        auto rightLeft = right->left;
        auto parent = node->parent;
        auto rightLeftLeft = rightLeft->left;
        auto rightLeftRight = rightLeft->right;
        
        rightLeft->parent = parent;
        node->right = rightLeftLeft;
        right->left = rightLeftRight;
        rightLeft->right = right;
        rightLeft->left = node;
        right->parent = rightLeft;
        node->parent = rightLeft;
        
        if (rightLeftLeft) {
            rightLeftLeft->parent = node;
        }
        
        if (rightLeftRight) {
            rightLeftRight->parent = right;
        }
        
        if (node == root) {
            root = rightLeft;
            
        } else if (parent->left == node) {
            parent->left = rightLeft;
            
        } else {
            parent->right= rightLeft;
        }
        
        if (rightLeft->balance == -1) {
            node->balance = 0;
            right->balance = 1;
            
        } else if (rightLeft->balance == 1) {
            node->balance = -1;
            right->balance = 0;
            
        } else {
            node->balance = 0;
            right->balance = 0;
        }
        
        rightLeft->balance = 0;
        return rightLeft;
    }
    
    
    template <class T>
    shared_ptr<Iterator<T>> AVLTree<T>::iterator(Traversal traversal) {
        switch (traversal) {
            case Traversal::ASCENDING:
                return shared_ptr<Iterator<T>>(new AscendingIterator<T>(root));
                
            case Traversal::LEVEL:
                return shared_ptr<Iterator<T>>(new LevelIterator<T>(root));
                
            default:
                throw invalid_argument("Unsupported iterator");
        }
    }
    
    
    template <class T>
    T AVLTree<T>::operator[](int index) {
        if (index < 0 || index >= values) {
            throw invalid_argument("index is invalid");
        }
        
        shared_ptr<Iterator<T>> iterator = this->iterator();
        for (int i = 0; i <= index; i++) {
            (*iterator)++;
        }
        
        return iterator->get()->value;
    }
    
    template <class T>
    ostream& operator<<(ostream& stream, AVLTree<T>& tree) {
        auto iterator = tree.iterator(Traversal::ASCENDING);
        while ((*iterator)++) {
            auto value = iterator->get();
            stream << (*value);
        }
        return stream;
    }
    

    template <class T>
    int AVLTree<T>::nodes() {
        return values;
    }

    template <class T>
    int AVLTree<T>::size() {
        return total;
    }
    
}

#endif /* TREE_H */

