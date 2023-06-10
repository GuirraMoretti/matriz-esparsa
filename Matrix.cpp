#include "Matriz.h"
#include <iostream>
#include <stdexcept>

using namespace std;
   
    //construtor 
SparseMatrix::SparseMatrix(short unsigned l, short unsigned c)
    : linhas(l), colunas(c), m_head(new Node(nullptr, nullptr, 0, 0, 0))
{
    Node* ptr = m_head;

    // Laço para criar linhas
    for (int i = 1; i <= l; ++i) {
        ptr->bottom = new Node(nullptr, nullptr, i, 0, 0);
        ptr = ptr->bottom;
        ptr->right = ptr;
        ptr->bottom = m_head;
    }

    // Reseta o ponteiro auxiliar
    ptr = m_head;

    // Laço para criar colunas
    for (int j = 1; j <= c; ++j) {
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
bool SparseMatrix::verifyCoord(short unsigned i, short unsigned j){
    if(i > linhas || i < 0 || j > colunas || j < 0){
         throw range_error("index out of range");
    }else return true;
}

    //inserir ou substituir elementos na matrix TO-DO
void SparseMatrix::insert(short unsigned i, short unsigned j, double value) {
    // Verifica se as coordenadas passadas estão dentro da matriz criada
    verifyCoord(i, j);

    Node * currentColumn = m_head->right;
    Node * currentLine = m_head->bottom;

    //Chegar no cabecalho da linha
    while (currentLine->line != i)
    {
        currentLine = currentLine->bottom;
    }
    //Chegar no cabecalho da coluna
    while (currentColumn->column != j)
    {
        currentColumn = currentColumn->right;
    }

        
    // Node* headerColumn = new Node(currentColumn->right,currentColumn->bottom,0,currentColumn->column,0);
    // Node* headerLine = new Node(currentLine->right,currentLine->bottom,currentLine->line,0,0);
    Node* headerLine = currentLine;
    Node* headerColumn = currentColumn;


        cout << "(" << headerColumn->line << "(" << endl;
        cout << "(" << headerColumn->column << "(" << endl;
        cout << "(" << headerLine->line << "(" << endl;
        cout << "(" << headerLine->column << "(" << endl;


    //Caso matriz vazia
    if (currentLine->right == currentLine && currentColumn->bottom == currentColumn && value!=0)
    {
        currentColumn->bottom = new Node(headerLine,headerColumn,i,j,value);
        currentLine->right = currentColumn->bottom;
        cout << "(" << currentColumn->bottom->bottom->line << "(" << endl;
        cout << "(" <<currentColumn->bottom->bottom->column << "(" << endl;
        cout << "(" <<currentColumn->bottom->right->column << "(" << endl;
        cout << "(" <<currentColumn->bottom->right->line << "(" << endl;
        return;
    }
    

    //Sai do cabeçalho e procura o node anterior
    while (currentLine->right->column < j && currentLine->right->column != 0)
    {
        currentLine = currentLine->right;
    }
    while (currentColumn->bottom->line < i && currentColumn->bottom->line != 0)
    {
        currentColumn = currentColumn->bottom;
    }

    //Atribui a um nó existente
    if (currentColumn->bottom->line == i  && currentLine->right->column == j)
    {
        currentColumn->bottom->value = value;
        return;
    }



    //!Adicionar Nó
    if (currentLine->right == headerLine && currentColumn->bottom == headerColumn)
    {
        currentLine->right = new Node(headerLine,headerColumn,i,j,value);
        headerColumn->bottom = currentLine->right;
    }
    else if (currentLine->right != headerLine && currentColumn->bottom == headerColumn)
    {
        Node *aux = currentLine->right;
        currentLine->right = new Node(aux,headerColumn->bottom,i,j,value);
        headerColumn->bottom = currentLine->right;   
    }
   else if (currentLine->right == headerLine && currentColumn->bottom != headerColumn)
    {
      Node *aux = currentColumn->bottom;
      currentColumn->bottom = new Node(headerLine->right,aux,i,j,value);
      headerLine->right = currentColumn->bottom;
    }
    else if (currentLine->right != headerLine && currentColumn->bottom != headerColumn)
    {
       Node *auxR = currentLine->right;
       Node *auxB = currentColumn->bottom;
       currentColumn->bottom = new Node(auxR,auxB,i,j,value);
       currentLine->right = currentColumn->bottom;       
    }
   
}

    //retornar o value do elemento passado
double SparseMatrix::get(short unsigned i, short unsigned j){
    
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
    for (short unsigned i = 1; i <= linhas; i++) {
        for (short unsigned j = 1; j <= colunas; j++) {
            double value = get(i, j);
            cout << value << " ";
        }
        cout << endl;
    }
}
