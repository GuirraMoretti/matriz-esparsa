/**************************************************************************
 Guilherme Lima Moretti 536179
 Vitória ashiley Lopes Ferreira 535667
**************************************************************************/

#include "Matriz.h"
#include <iostream>
#include <fstream>

using namespace std;

//Lê uma matrix de um arquivo txt
SparseMatrix* readSparseMatrix(string archive){
   
    //procura o arquivo
    ifstream file(archive);

    unsigned linhas, colunas;

    //lê a primeira linha do arquivo 
    file >> linhas >> colunas;

    //cria uma matriz
    SparseMatrix* matrix = new SparseMatrix(linhas, colunas);

    unsigned linha, coluna;
    double value;

    //lê todas as linhas do arquivo até que não tenham mais linhas
    while(file >> linha >> coluna >> value){
        matrix->insert(linha, coluna, value);
    }
    return matrix;
}

//faz a soma dos elementos de duas matrizes
//SparseMatrix* sum(SparseMatrix* M1, SparseMatrix* M2);

//faz a multiplicação dos elementos de duas matrizes
//SparseMatrix* multiply(SparseMatrix* M1, SparseMatrix* M2);


int main(){
    SparseMatrix* teste = new SparseMatrix(3,3);
    teste->print();
    cout << endl;
    teste->insert(2,2,30);
    teste->print();
    cout << endl;
    teste->insert(1,3,300);
    teste->print();
    cout << endl;
    teste->insert(2,3,200);
    teste->print();
    cout << endl;
    teste->insert(2,2,32);
    teste->print();
    cout << endl;
    teste->insert(5,5,30);
    teste->~SparseMatrix();
    teste->print();
    return 0;
}