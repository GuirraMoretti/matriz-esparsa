#include <iostream>
#include "Matriz.h"

int main() {
    // Cria uma matriz esparsa 3x3
    SparseMatrix matriz(3, 3);

    // Insere alguns valores na matriz
    matriz.insert(1, 1, 1.0);
    matriz.insert(2, 2, 2.0);
    matriz.insert(3, 3, 3.0);

    // Tenta inserir um valor em uma posição inválida
    try {
        matriz.insert(4, 4, 4.0);
    } catch (const std::out_of_range& e) {
        std::cout << "Erro: " << e.what() << std::endl;
    }

    // Imprime a matriz
    matriz.print();
    return 0;
}
