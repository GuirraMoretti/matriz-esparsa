/**************************************************************************
 Guilherme Lima Moretti 536179
 Vitória ashiley Lopes Ferreira 535667
**************************************************************************/

#ifndef Matrix_h
#define Matrix_h
#include "Node.h"

class SparseMatrix {
 private:
  short unsigned lines;
  short unsigned columns;
  Node *m_head;

 public:
  // construtor
  SparseMatrix(short unsigned l, short unsigned c);

  // destrutor
  ~SparseMatrix();

  // retorna quantidade de linhas
  unsigned int getLines() const;

  // retorna a quantidade de colunas
  unsigned int getColumns() const;

  //verifica se a coordenada passada esta dentro da matriz
  bool verifyCoord(short unsigned i, short unsigned j);

  // inserir ou substituir elementos na matrix
  void insert(short unsigned i, short unsigned j, double value);

  // retornar o valor do elemento
  double get(short unsigned i, short unsigned j);

  // printa toda a matrix
  void print();
};

#endif