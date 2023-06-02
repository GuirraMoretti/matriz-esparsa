#ifndef Matriz_h
#define Matriz_h
#include "Node.h"

class SparseMatrix{
    private:

    int linhas;
    int colunas;
    Node *m_head;

    public:
    //construtor
    SparseMatrix(int l, int c);

    //destrutor
    ~SparseMatrix();

    //inserir ou substituir elementos na matrix
    void insert(int i, int j, double value);

    //retornar o valor do elemento passado
    double get(int i, int j);

    //printa toda a matrix
    void print();
};

#endif