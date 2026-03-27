#include "literais.h"

int litarais(char pivo, leitorArquivo &arquivo,
             std::vector<tabelaToken> &tabela) {

    if (pivo == '"') {
        arquivo.setColunaPivo(arquivo.getColuna());

        std::string token = "";
        char batedor;

        while (arquivo.lerChar(batedor)) {
            if (batedor == '"') {
                salvarToken(classeToken::LITERAIS, token, arquivo, tabela);
                return 1;
            }
            token += batedor;
        }
    }
    return 0;
}