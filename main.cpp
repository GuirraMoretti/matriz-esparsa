/**************************************************************************
 Guilherme Lima Moretti 536179
 Vitória ashiley Lopes Ferreira 535667
**************************************************************************/

#include <filesystem>
#include <fstream>
#include <iostream>
#include <vector>

#include "Matriz.h"

#ifdef _WIN32
const std::string clearCommand = "cls";
#else
const std::string clearCommand = "clear";
#endif

using namespace std;

vector<SparseMatrix*> matrizes;

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

//faz a soma dos elementos de duas matrizes
SparseMatrix* sum(SparseMatrix* M1, SparseMatrix* M2) {
    if (M1->getLines() != M2->getLines() || M1->getColumns() != M2->getColumns()) {
        cout << "As matrizes devem ter a mesma dimensão para serem somadas." << endl;
        return nullptr;
    }

    SparseMatrix* result = new SparseMatrix(M1->getLines(), M1->getColumns());

    for (unsigned int i = 1; i <= M1->getLines(); i++) {
        for (unsigned int j = 1; j <= M1->getColumns(); j++) {
            double value = M1->get(i, j) + M2->get(i, j);
            result->insert(i, j, value);
        }
    }

    return result;
}


 //faz a multiplicação dos elementos de duas matrizes
  SparseMatrix * multiply(SparseMatrix* M1, SparseMatrix* M2){

        if (M1->getColumns() != M2->getLines()) {
            cout << "Matrizes nao podem multiplicar!" << endl;
            return nullptr;
        }

      short unsigned resultLines = M1->getLines();
      short unsigned resultColumns = M2->getColumns();   
      
      SparseMatrix * result = new SparseMatrix(resultLines, resultColumns);

      for (short unsigned i = 1; i <= resultLines; i++) {
          for (short unsigned j = 1; j <= resultColumns; j++) {
              double value = 0.0;
              for (short unsigned k = 1; k <= M1->getColumns(); k++) {
                  value += M1->get(i, k) * M2->get(k, j);
              }
              
              result->insert(i, j, value);
          }
      }

      return result;
  }

SparseMatrix *createMatrix() {
  system(clearCommand.c_str());
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
  system(clearCommand.c_str());
  SparseMatrix *matrix = new SparseMatrix(l, c);
  cout << "/-------------------------------------------------------------------"
          "----------------------------------\\"
       << endl;
  cout << "\t\tMatriz " << matrizes.size()+1 << " criada com sucesso!" << endl;
  cout << "\\------------------------------------------------------------------"
            "-----------------------------------/" << endl;
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

void showAllMatrizes() {
  system(clearCommand.c_str());
  if (matrizes.empty()) {
    cout << "Nenhuma matriz foi criada." << endl;
  } else {
    cout << "Matrizes criadas:" << endl;
    for (size_t i = 0; i < matrizes.size(); i++) {
      cout << "Matriz " << i + 1 << ":" << endl;
      matrizes[i]->print();
      cout << endl;
    }
  }
}

void menuMatrix(SparseMatrix *matrix) {
  char op;
  short unsigned l, c;

  while(true) {
    cout << "Escolha as funcoes disponiveis para matriz: " << endl;
    cout << "(p) exibir matriz" << endl;
    cout << "(e) exibir elemento da matriz" << endl;
    cout << "(m) modificar elemento da matriz" << endl;
    cout << "(s) voltar para menu principal" << endl;
    cout << "> ";
    cin >> op;
    bool firstTime = true;

    if (firstTime) {
      system(clearCommand.c_str());
    } else {
      firstTime = false;
    }

    switch (op) {
      case 'p':
        cout << "/------------- Matriz ------------\\" << endl;
        matrix->print();
        cout << "\\---------------------------------/" << endl;
        break;
      case 'e':
        cout << "Digite a coordenada do elemento que deseja exibir (linha "
                "coluna):"
             << endl;
        cout << "> ";
        cin >> l >> c;
        cout << "Valor: < " << matrix->get(l, c) << fixed << setprecision(4)
             << " >" << endl;
        break;
      case 'm':

        cout << "Digite a coordenada do elemento que deseja inserir (linha "
                "coluna):"
             << endl;
        cout << "> ";
        cin >> l >> c;
        cout << "Digite o valor que deseja inserir na coordenada:" << endl;
        cout << "> ";
        double value;
        cin >> value;
        matrix->insert(l, c, value);
        if (matrix->get(l, c) == value) {
          cout << "Valor inserido com sucesso!" << endl;
        } else
          cerr << "Erro desconhecido";
        break;

      case 's':
        return;
      case 'q':
        return;
      default:
        cout << "Opção inválida. Tente novamente." << endl;
        break;
    }
  }
}


SparseMatrix *menuPrincipal() {
  char op;
  string name;
  
  while(true) {

    cout << "\t\t\t\tMenu Principal" << endl;
    cout << "Escolha uma opcao:" << endl;
    cout << "(c) criar matriz vazia" << endl;
    cout << "(a) criar matriz por meio do arquivo" << endl;
    cout << "(l) lista matrizes existentes" << endl;
    cout << "(e) editar matriz existentes" << endl;
    cout << "(m) multiplicar matrizes existentes" << endl;
    cout << "(s) somar matrizes existentes" << endl; // fazer
    cout << "(q) sair do programa" << endl; //exit(0)
    cout << ">";
    int m1,m2;
    cin >> op;

    SparseMatrix * matrizResultante = nullptr;

    switch (op) {
        // Criar vazia
      case 'c':
        matrizes.push_back(createMatrix());
        return matrizes.back();
        break;

      
        // Criar por meio de arquivo
      case 'a':
        cout << "/-----------------------------------------------------------------------------------------------------\\" << endl;
        cout << "Digite o nome do arquivo .txt que deseja adicionar: ";
        cin >> name;
        matrizes.push_back(createMatrix(name));
        cout << matrizes.size();
        return matrizes.back();
        break;

    
      case 'l':
        showAllMatrizes();
        // menuPrincipal();
        break;


      case 'e':
        cout << "Digite a posicao da matriz que deseja modificar:";
        cout << "> " << endl;
        cin >> m1;
        menuMatrix(matrizes[m1-1]);
        break;

      case 'm':
        cout << "Digite a posicao da primeira matriz que deseja multiplicar:";
        cout << "> " << endl;
        cin >> m1;
        cout << "Digite a posicao da segunda matriz que deseja multiplicar:";
        cout << "> " << endl;
        cin >> m2;
        matrizResultante = multiply(matrizes[m1 - 1], matrizes[m2 - 1]);
        matrizResultante->print();
        // menuPrincipal();
        break;
      case 's':
        cout << "Digite a posicao da primeira matriz que deseja somar:";
        cout << "> " << endl;
        cin >> m1;
        cout << "Digite a posicao da segunda matriz que deseja somar:";
        cout << "> " << endl;
        cin >> m2;
        matrizResultante = sum(matrizes[m1 - 1], matrizes[m2 - 1]);
        matrizResultante->print();
        // menuPrincipal();
        break;
      case 'q':
        for(auto x: matrizes) delete x;
        exit(0);
        break;


      default:
        system(clearCommand.c_str());
        cout << "Opcao invalida" << endl;
          // return menuPrincipal();
    }
  }
  return nullptr;
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
  while(true) {
    // Chama menu para criar matriz
    SparseMatrix *matrix = menuPrincipal();
  }
  
  for(auto x: matrizes) delete x;

  return 0;
}