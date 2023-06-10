/**************************************************************************
 Guilherme Lima Moretti 536179
 Vitória ashiley Lopes Ferreira 535667
**************************************************************************/

#include <filesystem>
#include <fstream>
#include <iostream>

#include "Matriz.h"

#ifdef _WIN32
const std::string clearCommand = "cls";
#else
const std::string clearCommand = "clear";
#endif

using namespace std;

// Lê uma matrix de um arquivo txt
SparseMatrix *readSparseMatrix(string archive) {
  // procura o arquivo
  ifstream file(archive);

  unsigned linhas, colunas;

  // lê a primeira linha do arquivo
  file >> linhas >> colunas;

  // cria uma matriz
  SparseMatrix *matrix = new SparseMatrix(linhas, colunas);

  unsigned linha, coluna;
  double value;

  // lê todas as linhas do arquivo até que não tenham mais linhas
  while (file >> linha >> coluna >> value) {
    matrix->insert(linha, coluna, value);
  }
  return matrix;
}

// faz a soma dos elementos de duas matrizes
// SparseMatrix* sum(SparseMatrix* M1, SparseMatrix* M2);

// faz a multiplicação dos elementos de duas matrizes
// SparseMatrix* multiply(SparseMatrix* M1, SparseMatrix* M2);

SparseMatrix *createMatrix() {
  int l, c;
  cout << "/-------------------------------------------------------------------"
          "----------------------------------\\"
       << endl;
  cout << "Digite a quantidade de linhas e colunas que deseja criar a matriz:"
       << endl;
  cout << "Linhas: ";
  cin >> l;
  cout << "Colunas: ";
  cin >> c;
  SparseMatrix *matrix = new SparseMatrix(l, c);
  return matrix;
}
SparseMatrix *createMatrix(string name) {
  // A biblioteca le o diretorio atual e armazena o no CurrentDir
  filesystem::path currentDir = filesystem::current_path();
  // Concatena a pasta matrizes no diretorio
  currentDir /= "matrizes";
  // Adiciona o nome do arquivo no path
  filesystem::path filePath = currentDir /= (name + ".txt");
  // Ele envia o nome do diretorio do arquivo para a funcao readSparseMatrix, a
  // funcao retorna com a matriz criada, criando um ponteiro da matriz, e
  // retorna a matriz.
  SparseMatrix *matrix = readSparseMatrix(filePath.string());
  return matrix;
}

SparseMatrix *MenuCreationMatrix() {
  char op;
  string name;
  cout << "\t\t\t\tMenu" << endl;
  cout << "Escolha uma opcao:" << endl;
  cout << "(a) criar matriz vazia" << endl;
  cout << "(c) criar matriz por meio do arquivo" << endl;
  cout << ">";
  cin >> op;
  switch (op) {
      // Criar vazia
    case 'a':
      return createMatrix();
      break;
      // Criar por meio de arquivo
    case 'c':
      cout << "/---------------------------------------------------------------"
              "--------------------------------------\\"
           << endl;
      cout << "Digite o nome do arquivo .txt que deseja adicionar: ";
      cin >> name;
      return createMatrix(name);
      break;
    default:
      system(clearCommand.c_str());
      cout << "Opcao invalida" << endl;
      return MenuCreationMatrix();
  }
  return nullptr;
}

SparseMatrix *menuMatrix(SparseMatrix *matrix) {
  cout << "Escolha as funcoes disponiveis para matriz: " << endl;
  cout << "(p) printar matriz" << endl;
  cout << "(e) printar elemento da matriz" << endl;
  cout << "(m) modificar elemento da matriz" << endl;
  cout << ">";
  char op;
  cin >> op;
  switch (op) {
    case 'p':
      cout << "/------------- Matriz ------------\\" << endl;
      matrix->print();
      cout << "\\---------------------------------/" << endl;
      break;
    case 'e':
  }
}

int main() {
  system(clearCommand.c_str());
  cout << "/-------------------------------------------------------------------"
          "----------------------------------\\"
       << endl;
  cout << "\t\tOla Professor, seja bem vindo ao Projeto de Matriz Esparsa!"
       << endl;
  cout << "\\------------------------------------------------------------------"
          "-----------------------------------/"
       << endl;
  cout << "Autores:\n\t0536179 - Guilherme Lima Moretti" << endl;
  cout << "\t0535667 - Vitoria Ashiley Lopes Ferreira " << endl;
  cout << "/-------------------------------------------------------------------"
          "----------------------------------\\"
       << endl;
  // Chama menu para criar matriz
  SparseMatrix *matrix = MenuCreationMatrix();
  // Limpa o Terminal
  system(clearCommand.c_str());

  menuMatrix(matrix);

  return 0;
}