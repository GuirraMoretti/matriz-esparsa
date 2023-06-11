/**************************************************************************
 Guilherme Lima Moretti 536179
 Vitória ashiley Lopes Ferreira 535667
**************************************************************************/

#ifndef Node_h
#define Node_h

struct Node {
  Node *right;
  Node *bottom;
  unsigned line;
  unsigned column;
  double value;

  // construtor da classe Node
  Node(Node *d, Node *b, unsigned l, unsigned c, double v) {
    this->right = d;
    this->bottom = b;
    this->line = l;
    this->column = c;
    this->value = v;
  }
};

#endif
