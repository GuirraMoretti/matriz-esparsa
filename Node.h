#ifndef Node_h
#define Node_h

struct Node{
    Node *right;
    Node *bottom;
    unsigned line;
    unsigned column;
    double value;


    //constructor of class node
    Node (Node *r, Node *b, unsigned l, unsigned c, double v){
        this->right = r;
        this->bottom = b;
        this->line = l;
        this->column = c;
        this->value = v;
    }
};

#endif
