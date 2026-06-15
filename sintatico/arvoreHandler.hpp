#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

#include "../lexico/tokenHandler.hpp"
#include "semantico.hpp"

enum class tipoStatement {
    EXPRESSAO,
    REPETICAO,
    CONDICAO,
    DECLARACAO,
    ATRIBUICAO,
    SENTENCA,
    BLOCO,
    RAIZ,
    TOKEN
};


struct NoArvore {
    int id;
    tipoStatement tipo;
    tipoVar tipoToken;
    vector<NoArvore> filhos;

    NoArvore(int id, tipoStatement tipo, tipoVar tipoToken = tipoVar::NONE)
        : id(id), tipo(tipo), tipoToken(tipoToken) {}
    
    void podar();
};

string tipoToString(tipoStatement t);
void imprimirArvore(const NoArvore& no, const vector<tabelaToken>& tabela, string prefixo, bool ultimo);