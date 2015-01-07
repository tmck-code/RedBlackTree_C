#ifndef RBTREE_H
#define RBTREE_H

/********************************************************
 * File: RBTree.h
 *
 * This is the header file for a Red-Black Tree
 *
 * @author Thomas McKeesick
 * @version 0.1 8/01/2015
 *
 ********************************************************/
 
#include <RBNode.h>
 
#include <stdexcept>
#include <string>
 
template<typename T>
class RBTree {
    public:
        RBTree();
        void insert(T data);
        T& contains(T data);
        bool removeElement(T data);
        void printStructure();
        void displayElements(std::string out);
        
    private:
        static const char RED = 'R';
        static const char BLUE = 'B';
        RBNode<T>* root;
        RBNode<T>* put(RBNode<T>* node, T data);
        bool isRed(RBNode<T>* node);
        void colourFlip(RBNode<T>* parent);
        
        RBNode<T> rightRotation(RBNode<T>* grandparent);
        RBNode<T> leftRotation(RBNode<T>* grandparent);
        

        void displaySubTreeInOrder(RBNode<T>* node, std::string out);
        

};
 
#endif