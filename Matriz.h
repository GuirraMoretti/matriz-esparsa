#ifndef Matriz_h
#define Matriz_h
#include "Node.h"

class SparseMatrix {
 private:
  short unsigned linhas;
  short unsigned colunas;
  Node *m_head;

 public:
  // construtor
  SparseMatrix(short unsigned l, short unsigned c);

  // destrutor
  ~SparseMatrix();

  bool verifyCoord(short unsigned i, short unsigned j);

  // inserir ou substituir elementos na matrix
  void insert(short unsigned i, short unsigned j, double value);

  // retornar o valor do elemento passado
  double get(short unsigned i, short unsigned j);

  // printa toda a matrix
  void print();
};

#endif