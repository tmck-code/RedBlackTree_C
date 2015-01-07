/********************************************************
 * File: RBTree.cpp
 *
 * This is the program file for a Red-Black Tree
 *
 * @author Thomas McKeesick
 * @version 0.1 8/01/2015
 *
 ********************************************************/
#include <RBTree.h>
#include <RBNode.h>

#include <exception>

using std::string;

template<typename T> RBTree<T>::RBTree() {
}

/*********************************************************************
 *          COLOUR METHODS, CONTAINS AND DELETE
 * *******************************************************************/

template<typename T> bool RBTree<T>::isRed(RBNode<T>* node) {
    return node.getColour() == 'R';
}

template<typename T> void RBTree<T>::colourFlip(RBNode<T>* parent) {
    if( parent->rChild == NULL || parent.lChild == NULL ) {
        return;
    }
    if( !isRed(parent) && isRed(parent->rChild) && isRed(parent->lChild) ) {
        if( parent != root ) {
            parent.setColour( 'R' );
        }
        parent->rChild.setColour( 'B' );
        parent->lChild.setColour( 'B' );
    }
}

template<typename T> T& RBTree<T>::contains(T data) {
    RBNode<T>* current = root;
    while( current->getData() != data ) {
        if(data < current->getData()) {
            current = current->lChild;
        } else {
            current = current->rChild;
        }
        
        if( current == NULL || current->isDeleted() ) {
            return NULL;
        }
    }
    return current;
}

/**
 * @brief Removes the supplied data from the tree. 
 * @param data The data to remove.
 * @return True if remove was successful, else throw an
 *      invalid_argument exception which is caught further up.
 */
template<typename T> bool RBTree<T>::removeElement(T data) {
    RBNode<T> node = contains(&data);
    
    if( node != NULL ) {
        node.deleteNode();
        return true;
    } else {
        throw std::invalid_argument("Could not find data in tree");
    }
}

/*********************************************************************
 *          ROTATION METHODS
 * *******************************************************************/

template<typename T> RBNode<T> RBTree<T>::rightRotation(RBNode<T>* grandparent) {
    RBNode<T>* parent = grandparent->lChild;
    RBNode<T>* rightChildOfParent = parent->rChild;
    parent->rChild = grandparent;
    grandparent->lChild = rightChildOfParent;
    
    return parent;
}

template<typename T> RBNode<T> RBTree<T>::leftRotation(RBNode<T>* grandparent) {
    RBNode<T>* parent = grandparent->rChild;
    RBNode<T>* leftChildOfParent = parent->lChild;
    parent->lChild = grandparent;
    grandparent->rChild = leftChildOfParent;
    
    return parent;
}

/*********************************************************************
 *          DISPLAY & TRAVERSAL METHODS
 * *******************************************************************/

template<typename T> void RBTree<T>::displayElements(string out) {
    displaySubTreeInOrder(root, out);
}

template<typename T> void RBTree<T>::displaySubTreeInOrder(RBNode<T>* node, string out) {
    if(node != NULL) {
        dispaySubTreeInOrder(node->lChild, out);
        out << node;
        displaySubTreeInOrder(node->rChild, out);
    }
}

template<typename T> void RBTree<T>::printStructure() {
    if(root == NULL) {
        cout << "tree is null" << endl;
    } else {
        cout << "**************************************" << endl;
        root->display(0);
        cout << "**************************************" << endl;
    }
    cout << endl;
}

/*********************************************************************
 *          INSERTION METHODS
 * *******************************************************************/

template<typename T> void RBTree<T>::insert(T data) {
    root =  put(root, data);
    root->setColour('B');
}

template<typename T> RBNode<T>* put(RBNode<T>* node, T data) {
    if( node == NULL ) {
        RBNode<T> newNode = RBNode<T>(data);
        return newNode;
    }
    
    if( data < node.getData() ) {
        node->lChild = put(node->lChild, data);
    } else if( data > node.getData() ) {
        node->rChild = put(node->rChild, data);
    } else {
        throw std::invalid_argument("Data already exists in tree!");
    }
    
    //Red-red conflict with outside grandchild
    if( isRed(node->lChild) && isRed(node->lChild->lChild) ) {
        node.setColour( 'R' );
        node->lChild.setColour( 'B' );
        node = rightRotation(node);
    }
    
    //Red-red conflict with right-outside grandchild
    if( isRed(node->rChild) && isRed(node->rChild->rChild) ) {
        node.setColour('R');
        node->rChild.setColour('B');
        node = leftRotation(node);
    }

    //Red-red conflict with left-right inside grandchild
    if( isRed(node->lChild) && isRed(node->lChild->rChild) ) {  
        node.setColour('R');
        node->lChild->rChild.setColour('B');
        node->lChild = leftRotation(node->lChild);
        node = rightRotation(node);
    }
    
    //Red-red conflict with right-left inside grandchild
    if( isRed(node->rChild) && isRed(node->rChild->lChild) ) {
        node.setColour('R');
        node->rChild->lChild.setColour('B');
        node->rChild = rightRotation(node->rChild);
        node = leftRotation(node);
    }
    
    colourFlip(node);
    return node;
}