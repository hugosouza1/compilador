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
    string nome;
    int linha;
    int coluna;
};

struct tabelaERRO {
    string tokenErro;
    string tipoErro;
    int linha;
    int coluna;
};

void salvarToken(classeToken token, const string &nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela);
int litarais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela, vector<tabelaERRO> &tabelaInvalidos);
int comentarios(char pivo, leitorArquivo &arquivo/*, std::vector<tabelaToken> &tabela*/, vector<tabelaERRO> &tabelaInvalidos);
int operadoMatLog(char pivo, leitorArquivo &arquivo, std::vector<tabelaToken> &tabela);
int numerais(char pivo, leitorArquivo &arquivo, std::vector<tabelaToken> &tabela, vector<tabelaERRO> &tabelaInvalidos);
int separador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela);
int identificador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela, vector<tabelaERRO> &tabelaInvalidos);

int erroToken(char pivo, leitorArquivo &arquivo, vector<tabelaERRO> &tabelaInvalidos);

string toSString(classeToken c);