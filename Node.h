#ifndef Node_h
#define Node_h

struct Node{
    Node *right;
    Node *bottom;
    unsigned line;
    unsigned column;
    double value;


    //constructor of class node
    Node (Node *d, Node *a, unsigned l, unsigned c, double v){
        this->right = d;
        this->bottom = a;
        this->line = l;
        this->column = c;
        this->value = v;
    }
};

#endif
