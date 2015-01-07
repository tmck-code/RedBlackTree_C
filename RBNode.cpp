/********************************************************
 * File: RBNode.cpp
 *
 * This is the program file for a Red-Black Node
 *
 * @author Thomas McKeesick
 * @version 0.1 8/01/2015
 *
 ********************************************************/
 
 #include <RBNode.h>
 
 #include <iostream>
 #include <string>
 
 using std::cout;
 using std::endl;
 using std::string;
 
 /**
  * @brief Constructor for a node that inserts the given data. The colour is red by default
  *     and the deleted status is false.
  * @param data The data that will be contained by the node
  */
 template<typename T> RBNode<T>::RBNode(T data) {
     RBNode::data = data;
     colour = 'R';
     deleted = false;
 }

template<typename T> void RBNode<T>::deleteNode() {
    deleted = true;
}

template<typename T> void RBNode<T>::display(int n) {
    string indent = "- ";
	
	for(int i = 1; i <= n; i++) {
			cout << indent;
	}
	cout << "ROOT: " << data << ", colour: " << colour << endl;

	for(int i = 1; i <= n; i++) {
		cout << indent;
	}
	cout << "LEFT" << endl;
	if( lChild == NULL) { 
		for(int i = 1; i <= n+1; i++) {
				cout << indent;
		}
		cout << "null" << endl;
		} else {
			lChild->display(n+1);
		}

		for(int i = 1; i <= n; i++) {
			cout << indent;
		}
        
		cout << "RIGHT" << endl;
        
		if( rChild == NULL) {
			for(int i = 1; i <= n+1; i++) {
				cout << indent;
			}
			cout << "null" << endl; 
		} else {
			rChild->display(n+1);
		}
}

/**************************************************\
 *          GETTER METHODS                         |
 **************************************************/

template<typename T> char RBNode<T>::getColour() {
    return colour;
}

template<typename T> T& RBNode<T>::getData() {
    return data;
}

template<typename T> bool RBNode<T>::isDeleted() {
    return deleted;
}

/**************************************************\
 *          SETTER METHODS                         |
 **************************************************/

/**
 * @brief Sets the colour of the node to the supplied colour. Must be a char matching
 *      either BLACK or RED as defined in the header. Must also not be the same colour
 *      as the current node colour.
 * @param c The new colour of the node.
 * @return true if the colour change was successful, false otherwise
 */
template<typename T> bool RBNode<T>::setColour(char c) {
    
    if( (c == 'R' || c == 'B' ) && c != colour ) {
        colour = c;
        return true;
    }
    return false;
}

template<typename T> void RBNode<T>::setData(T data) {
    RBNode<T>::data = data;
}