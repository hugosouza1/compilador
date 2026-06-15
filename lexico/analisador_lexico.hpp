#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#include "leitorArquivo.hpp"
#include "tokenHandler.hpp"
#include "analisador_lexico.hpp"

using namespace std;

void imprimirTokens(vector<tabelaToken> tabela);

void imprimeErro(vector<tabelaERRO> tabelaInvalidos );

vector<tabelaToken> analisadorLexico(int argc, char *argv[]);

