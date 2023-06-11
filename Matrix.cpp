#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <math.h>

#include "Matriz.h"




using namespace std;

// construtor
SparseMatrix::SparseMatrix(short unsigned l, short unsigned c)
    : lines(l), columns(c), m_head(new Node(nullptr, nullptr, 0, 0, 0))
{
    Node *ptr = m_head;

    // Laço para criar linhas
    for (int i = 1; i <= l; ++i)
    {
        ptr->bottom = new Node(nullptr, nullptr, i, 0, 0);
        ptr = ptr->bottom;
        ptr->right = ptr;
        ptr->bottom = m_head;
    }

    // Reseta o ponteiro auxiliar
    ptr = m_head;

    // Laço para criar colunas
    for (int j = 1; j <= c; ++j)
    {
        ptr->right = new Node(nullptr, nullptr, 0, j, 0);
        ptr = ptr->right;
        ptr->bottom = ptr;
        ptr->right = m_head;
    }
}

// destrutor
SparseMatrix::~SparseMatrix()
{
    // cria um ponteiro para a linha do nó
    Node *ActualLine = m_head->bottom;

    // apaga as linhas enquanto forem diferentes do nó cabeça
    while (ActualLine != m_head)
    {
        // cria um ponteiro para a coluna da linha atual
        Node *ActualColumn = ActualLine->right;

        // apaga as colunas da linha atual
        while (ActualColumn != m_head)
        {
            Node *nextcolumn = ActualColumn->right;

            // deleta as colunas
            delete ActualColumn;

            ActualColumn = nextcolumn;
        }

        Node *nextline = ActualLine->bottom;
        delete ActualLine;
        ActualLine = nextline;
    }

    Node *ColumnRest = m_head->right;

    while (ColumnRest != m_head)
    {
        Node *next = ColumnRest->right;

        // deleta as colunas que restam a direita do nó cabeça
        delete ColumnRest;

        ColumnRest = next;
    }

    delete m_head;
}


unsigned int SparseMatrix::getColumns() const {
  return columns;
}

unsigned int SparseMatrix::getLines() const {
  return lines;
}

// Funcao serve para ver se a coordenada passada esta contida na matriz
bool SparseMatrix::verifyCoord(short unsigned i, short unsigned j)
{
    if (i > lines || i < 0 || j > columns || j < 0)
    {
        throw range_error("coordenada fora da matriz");
    }
    else
        return true;
}

// inserir ou substituir elementos na matrix TO-DO
void SparseMatrix::insert(short unsigned i, short unsigned j, double value)
{
    // Verifica se as coordenadas passadas estão dentro da matriz criada
    verifyCoord(i, j);

    Node *currentColumn = m_head->right;
    Node *currentLine = m_head->bottom;

    // Chegar no cabeçalho da linha
    while (currentLine->line != i)
    {
        currentLine = currentLine->bottom;
    }
    // Chegar no cabeçalho da coluna
    while (currentColumn->column != j)
    {
        currentColumn = currentColumn->right;
    }

    Node *headerLine = currentLine;
    Node *headerColumn = currentColumn;

    // Caso matriz vazia
    if (currentLine->right == currentLine && currentColumn->bottom == currentColumn && value != 0)
    {
        currentColumn->bottom = new Node(headerLine, headerColumn, i, j, value);
        currentLine->right = currentColumn->bottom;
        return;
    }

    // Sai do cabeçalho e procura o node anterior
    while (currentLine->right->column < j && currentLine->right->column != 0)
    {
        currentLine = currentLine->right;
    }
    while (currentColumn->bottom->line < i && currentColumn->bottom->line != 0)
    {
        currentColumn = currentColumn->bottom;
    }

    // Atribui a um nó existente
    if (currentColumn->bottom->line == i && currentLine->right->column == j)
    {
        currentColumn->bottom->value = value;
        return;
    }

    // Adicionar Nó
    currentLine->right = (currentLine->right == headerLine)
                             ? new Node(headerLine, headerColumn, i, j, value)
                             : new Node(currentLine->right, headerColumn->bottom, i, j, value);

    currentColumn->bottom = (currentColumn->bottom == headerColumn)
                                ? new Node(headerLine->right, currentColumn->bottom, i, j, value)
                                : new Node(currentLine->right, currentColumn->bottom, i, j, value);
}

// retornar o value do elemento passado
double SparseMatrix::get(short unsigned i, short unsigned j)
{
    // Verifica se as coordenadas passadas estao dentro da matriz criada
    SparseMatrix::verifyCoord(i, j); // se nao existir aquela coodenada na matriz, a funcao lanca um
                                     // erro de range_error e mata o processo.

    Node *aux = m_head;

    // procura a line passada como refereência
    while (aux->line != i)
    {
        aux = aux->bottom;
    }
    // procura a column passada como referência
    while (aux->column != j)
    {
        aux = aux->right;
        // verifica se o laço voltou para o nó inicial
        if (aux->column == 0)
        {
            return 0;
        }
    }
    return aux->value;
}

// printa toda a matrix
void SparseMatrix::print()
{
    // Determinar a largura máxima dos valores na matriz
    int maxDigits = 0;
    int maxPrecision = 0;
    for (short unsigned i = 1; i <= lines; i++)
    {
        for (short unsigned j = 1; j <= columns; j++)
        {
            double value = get(i, j);
            std::stringstream ss;
            ss << std::fixed << value; // Definir o formato como decimal fixo
            std::string strValue = ss.str();

            // Verificar se o número tem parte decimal
            size_t dotPos = strValue.find(".");
            if (dotPos != std::string::npos)
            {
                int precision = strValue.length() - dotPos - 1;
                if (precision > maxPrecision)
                {
                    maxPrecision = std::min(precision, 4); // Limitar a 4 casas decimais
                }
            }

            int numDigits = strValue.length();
            if (numDigits > maxDigits)
            {
                maxDigits = numDigits;
            }
        }
    }

    // Imprimir a matriz com valores alinhados
    for (short unsigned i = 1; i <= lines; i++)
    {
        for (short unsigned j = 1; j <= columns; j++)
        {
            double value = get(i, j);
            std::stringstream ss;
            ss << std::fixed << std::setprecision(maxPrecision) << value;
            std::string strValue = ss.str();
            std::cout << std::setw(maxDigits + maxPrecision + 1) << std::setfill(' ') << std::left << strValue << " ";
        }
        std::cout << std::endl;
    }
}
