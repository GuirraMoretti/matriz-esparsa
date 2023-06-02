#include "Matriz.h"
#include <iostream>
#include <stdexcept>

using namespace std;
   
    //construtor 
SparseMatrix::SparseMatrix(int l, int c){
    this->lines = l;
    this->colunas = c;
    this->m_head = new Node(nullptr, nullptr, 0, 0, 0);
    Node *ptr = m_head;

    //laço para criar lines
    for(int i = 1; i <= l; i++){
        ptr->bottom = new Node(nullptr, nullptr, i, 0, 0);
        ptr = ptr->bottom;
        ptr->right = ptr;
        ptr->bottom = m_head;
    }

    //reseta o ponteiro auxiliar
    ptr = m_head;

    //laço para criar colunas
    for(int j = 1; j <= c; j++){
        ptr->right = new Node(nullptr, nullptr, 0, j, 0);
        ptr = ptr->right;
        ptr->bottom = ptr;
        ptr->right = m_head;
    }
}

    //destrutor
SparseMatrix::~SparseMatrix();

    //inserir ou substituir elementos na matrix
void SparseMatrix::insert(int i, int j, double value){

     //verifica se a coordenada existe dentro da matrix
     if(i > linhas || i < 0 || j > colunas || j < 0){
        throw range_error("index out of range");
    }
}

    //retornar o value do elemento passado
double SparseMatrix::get(int i, int j){
    
    //verifica se a coordenada existe dentro da matrix
    if(i > linhas || i < 0 || j > colunas || j < 0){
        throw range_error("index out of range");
    }

    Node* aux = m_head;

    //procura a line passada como refereência
    while(aux->line != i){
        aux = aux->bottom;
    }

    //procura a column passada como refereência
    while(aux->column != j){
        aux = aux->right;
        //verifica se o laço voltou para o nó inicial
        if(aux->column == 0){
            return 0;
        }
    }
    return aux->value;
}
    //printa toda a matrix
void SparseMatrix::print();