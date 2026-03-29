#pragma once

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <cctype>
#include <unordered_set>

#include "leitorArquivo.h"

using namespace std;

class leitorArquivo;

enum class classeToken {
    LITERAIS, //feito
    IDENTIFICADORES,
    COMENTARIOS, // feito
    PALAVRA_RESERVADA,
    NUMERAIS, // feito
    OPERADOR_LOGICO_MATEMATICO, // feito
    SEPARADOR // feito
};

struct tabelaToken {
    classeToken classe;
    string nome;
    int linha;
    int coluna;
};

void salvarToken(classeToken token, const string &nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela);
int litarais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela);
int comentarios(char pivo, leitorArquivo &arquivo/*, std::vector<tabelaToken> &tabela*/);
int operadoMatLog(char pivo, leitorArquivo &arquivo, std::vector<tabelaToken> &tabela);
int numerais(char pivo, leitorArquivo &arquivo, std::vector<tabelaToken> &tabela);
int separador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela);
int identificador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela);

void tokenError(string tipo, leitorArquivo &arquivo, string tipoErro);

string toSString(classeToken c);