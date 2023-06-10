#ifndef Node_h
#define Node_h

struct Node{
    Node *right;
    Node *bottom;
    unsigned line;
    unsigned column;
    double value;


    //constructor of class node
    Node (Node *d, Node *b, unsigned l, unsigned c, double v){
        this->right = d;
        this->bottom = b;
        this->line = l;
        this->column = c;
        this->value = v;
    }
};

#endif
