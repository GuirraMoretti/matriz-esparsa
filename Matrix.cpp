#include "Matriz.h"
#include <iostream>
#include <stdexcept>

using namespace std;
   
    //construtor 
SparseMatrix::SparseMatrix(unsigned l, unsigned c){
    this->linhas = l;
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

    //destrutor TO-DO
/*
SparseMatrix::~SparseMatrix(){

}
*/

//Funcao serve para ver se a coordenada passada esta contida na matriz
bool SparseMatrix::verifyCoord(unsigned i, unsigned j){
    if(i > linhas || i < 0 || j > colunas || j < 0){
         throw range_error("index out of range");
    }else return true;
}

    //inserir ou substituir elementos na matrix TO-DO
void SparseMatrix::insert(unsigned i, unsigned j, double value) {
    // Verifica se as coordenadas passadas estão dentro da matriz criada
    verifyCoord(i, j);

    Node* current = m_head;

    // Procura a linha passada como referência
    while (current->line != i) {
        current = current->bottom;
    }

    // Procura a coluna passada como referência
    while (current->column != j && current->right != m_head) {
        current = current->right;
    }

    if (current->column == j && current->line == i) {
        current->value = value;
    }
}

    //retornar o value do elemento passado
double SparseMatrix::get(unsigned i, unsigned j){
    
    //Verifica se as coordenadas passadas estao dentro da matriz criada
    SparseMatrix::verifyCoord( i , j); //se nao existir aquela coodenada na matriz, a funcao lanca um erro de range_error e mata o processo.

    Node* aux = m_head;

    //procura a line passada como refereência
    while(aux->line != i){
        aux = aux->bottom;
    }
    //procura a column passada como referência
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
void SparseMatrix::print() {
    for (unsigned i = 1; i <= linhas; i++) {
        for (unsigned j = 1; j <= colunas; j++) {
            double value = get(i, j);
            cout << value << " ";
        }
        cout << endl;
    }
}
