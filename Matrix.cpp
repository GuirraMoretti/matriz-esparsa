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

    //destrutor
SparseMatrix::~SparseMatrix() {
  // cria um ponteiro para a linha do nó
  Node* ActualLine = m_head->bottom;

  // apaga as linhas enquanto forem diferentes do nó cabeça
  while (ActualLine != m_head) {
    // cria um ponteiro para a coluna da linha atual
    Node* ActualColumn = ActualLine->right;

    // apaga as colunas da linha atual
    while (ActualColumn != m_head) {
      Node* nextcolumn = ActualColumn->right;

      // deleta as colunas
      delete ActualColumn;

      ActualColumn = nextcolumn;
    }

    Node* nextline = ActualLine->bottom;
    delete ActualLine;
    ActualLine = nextline;
  }

  Node* ColumnRest = m_head->right;

  while (ColumnRest != m_head) {
    Node* next = ColumnRest->right;

    // deleta as colunas que restam a direita do nó cabeça
    delete ColumnRest;

    ColumnRest = next;
  }

  delete m_head;
}


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

    Node* currentLine = m_head;
    Node* currentColumn = m_head;

    // Procura a linha passada como referência
    while (currentLine->line != i) {
        currentLine = currentLine->bottom;
    }

    // Procura a coluna passada como referência
    while (currentColumn->column != j) {
        currentColumn = currentColumn->right;
    }

    // Percorre a coluna até encontrar a posição correta para inserir o nó
    while (currentColumn->bottom != m_head && currentColumn->bottom->line < i) {
        currentColumn = currentColumn->bottom;
    }

    // Percorre a linha até encontrar a posição correta para inserir o nó
    while (currentLine->right != m_head && currentLine->right->column < j) {
        currentLine = currentLine->right;
    }
if (currentColumn->bottom->line == i && currentLine->right->column == j) {
        // Se já existe um nó com as mesmas coordenadas
        if (value == 0) {
            // Se o valor a ser inserido é zero, exclui o nó existente e realoca os ponteiros
            Node* nodeToDelete = currentColumn->bottom;
            currentColumn->bottom = currentColumn->bottom->bottom;
            currentLine->right = currentLine->right->right;
            delete nodeToDelete;
        } else {
            // Se o valor a ser inserido é diferente de zero, atualiza o valor do nó existente
            currentColumn->bottom->value = value;
        }
    } else {
        // Caso contrário, cria um novo nó e insere na posição correta se o valor for diferente de zero
        if (value != 0) {
            currentColumn->bottom = new Node(currentLine->right, currentColumn->bottom, i, j, value);
            currentLine->right = currentColumn->bottom;
        }
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
