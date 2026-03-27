#include <iostream>
#include <vector>
#include <string>

#include "leitorArquivo.h"
#include "tokenHandler.h"

using namespace std;


int main() {
    leitorArquivo arquivo("txt.txt");

    std::vector<tabelaToken> tabela;
    char pivo;

    while (arquivo.lerChar(pivo)) {
        if (litarais(pivo, arquivo, tabela)) continue;
       
        if(comentarios(pivo, arquivo /*,tabela*/)) continue;

        if(operadoMatLog(pivo, arquivo, tabela)) continue;

        if(numerais(pivo, arquivo, tabela)) continue;

        // futuros tokens aqui
    }

    for (const auto &t : tabela) {
        cout << "Token: " << t.nome << "\t"
             << "Classe: " << toSString(t.classe) << "\t"
             << " Linha: " << t.linha << "\t"
             << " Coluna: " << t.coluna << std::endl;
    }

    return 0;
}