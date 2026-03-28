#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

#include "leitorArquivo.h"
#include "tokenHandler.h"

using namespace std;


int main() {
    leitorArquivo arquivo("txt.txt");

    std::vector<tabelaToken> tabela;
    char pivo;

    while (arquivo.lerChar(pivo)) {

        if(separador(pivo, arquivo, tabela)) continue;

        if (litarais(pivo, arquivo, tabela)) continue;
       
        if(comentarios(pivo, arquivo /*,tabela*/)) continue;

        if(operadoMatLog(pivo, arquivo, tabela)) continue;

        if(numerais(pivo, arquivo, tabela)) continue;

        if(identificador(pivo, arquivo, tabela)) continue;

        // futuros tokens aqui
    }

std::cout << std::left
          << std::setw(20) << "CLASSE"
          << std::setw(15) << "NOME"
          << std::setw(10) << "LINHA"
          << std::setw(10) << "COLUNA"
          << std::endl;

std::cout << std::string(55, '-') << std::endl;

for (const auto &t : tabela) {
    std::cout << std::left
    << std::setw(20) << ("|" + toSString(t.classe))
    << std::setw(15) << ("|" + t.nome)
    << std::setw(10) << ("|" + std::to_string(t.linha))
    << std::setw(10) << ("|" + std::to_string(t.coluna))
    << "|" << std::endl;
}

std::cout << std::string(55, '-') << std::endl;
    return 0;
}