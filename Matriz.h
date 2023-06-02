#ifndef Matriz_h
#define Matriz_h
#include "Node.h"

class SparseMatrix{
    private:

    unsigned linhas;
    unsigned colunas;
    Node *m_head;

    public:
    //construtor
    SparseMatrix(unsigned l, unsigned c);

    //destrutor
    //~SparseMatrix();

    //inserir ou substituir elementos na matrix
    void insert(unsigned i, unsigned j, double value);

    //retornar o valor do elemento passado
    double get(unsigned i, unsigned j);

    //printa toda a matrix
    void print();

    bool verifyCoord(unsigned i, unsigned j);
};

#endif