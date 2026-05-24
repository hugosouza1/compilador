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
    TOKEN
};


struct NoArvore {
    int id;
    tipoStatement tipo;
    vector<NoArvore> filhos;

    NoArvore(int id, tipoStatement tipo)
        : id(id), tipo(tipo) {}

};