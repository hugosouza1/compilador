#include <iostream>
#include <vector>

#include "leitorArquivo.h"
#include "tokenHandler.h"

int main() {
    leitorArquivo arquivo("txt.txt");

    std::vector<tabelaToken> tabela;
    char c;

    while (arquivo.lerChar(c)) {
        if (litarais(c, arquivo, tabela)) continue;

        // futuros tokens aqui
    }

    for (const auto &t : tabela) {
        std::cout << "Token: " << t.nome
                  << " Linha: " << t.linha
                  << " Coluna: " << t.coluna << std::endl;
    }

    return 0;
}