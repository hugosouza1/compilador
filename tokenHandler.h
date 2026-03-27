#pragma once

#include <string>
#include <vector>
#include "leitorArquivo.h"

enum class classeToken {
    LITERAIS,
    IDENTIFICADORES,
    COMENTARIOS,
    PALAVRA_RESERVADA,
    NUMERAIS,
    OPERADOR_LOGICO_MATEMATICO,
    SEPARADOR
};

struct tabelaToken {
    classeToken classe;
    std::string nome;
    int linha;
    int coluna;
};

// funções
void salvarToken(classeToken token, const std::string &nome,
                 leitorArquivo &arquivo,
                 std::vector<tabelaToken> &tabela);

int litarais(char pivo, leitorArquivo &arquivo,
             std::vector<tabelaToken> &tabela);