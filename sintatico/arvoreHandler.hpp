#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

enum class tipoStatement {
    EXPRESSAO,
    REPETICAO,
    CONDICAO,
    DECLARACAO,
    SENTENCA,
    BLOCO,
    TOKEN
};


struct NoArvore {
    int id;
    tipoStatement tipo;
    vector<NoArvore> filhos;

    NoArvore(int id, tipoStatement tipo)
        : id(id), tipo(tipo) {}

};


void contarNos(const NoArvore& no, int& total, int& folhas);