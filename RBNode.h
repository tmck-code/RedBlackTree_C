#ifndef RBNODE_H
#define RBNODE_H

/********************************************************
 * File: RBNode.h
 *
 * This is the header file for a Red-Black Node
 *
 * @author Thomas McKeesick
 * @version 0.1 8/01/2015
 *
 ********************************************************/
 
 #include <iostream>
 
 using std::cout;
 using std::endl;
 using std::istream;
 using std::ostream;
 
template<typename T>
class RBNode {
     
    public:
        RBNode(T data);
        RBNode* rChild;
        RBNode* lChild;
        
        void setData(T data);
        bool setColour(char c);
        //void setRightChild(RBNode node);
        //void setLeftChild(RBNode node);
        void deleteNode();
        
        T& getData();
        char getColour();
        //RBNode& getRightChild();
        //RBNode& getLeftChild();
        bool isDeleted();
        void display(int n);
        
        bool operator == (const T& rhs) { return data == rhs; }
        bool operator != (const T& rhs) { return !operator==(rhs); }
        bool operator < (const T& rhs) { return data < rhs; }
        bool operator > (const T& rhs) { return !operator<(rhs); }
        bool operator <= (const T& rhs) { return !operator>(rhs); }
        bool operator >= (const T& rhs) { return !operator<(rhs); }
        
        friend ostream& operator << (ostream& os, const RBNode<T>& node) {
            os << "Node colour: " << node.colour << endl;
            os << "Data: " << node.data << endl;
            return os;
        }
        friend istream& operator >> (istream& is, RBNode<T>& node) {
            is >> node.data;
            return is;
        }

     private:
        static const char RED = 'R';
        static const char BLUE = 'B';
        char colour;
        bool deleted;
        T data;
};

#endif