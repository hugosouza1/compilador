#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>

#include "tokenHandler.h"

using namespace std;

void salvarToken(classeToken token, string nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    tabelaToken t;
    t.classe = token;
    t.nome = nome;
    t.linha = arquivo.getLinha();
    t.coluna = arquivo.getColunaPivo();
    tabela.emplace_back(t);
}

class leitorArquivo {
    private:
        int linha;
        int coluna;
        int linhaPivo;
        int colunaPivo;
        ifstream arquivo;

    public:
        leitorArquivo() : linha(0), coluna(0), arquivo("txt.txt") {}

        bool lerChar(char &c) {
            if (arquivo.get(c)) {
                if (c == '\n') {
                    coluna = 0;
                    linha++;
                } else {
                    coluna++;
                }
                return true;
            }
            return false;
        }

        int getLinha() const { return linha; }
        int getColuna() const { return coluna; }
        int getColunaPivo() const { return colunaPivo; }

        void setColunaPivo(int num){colunaPivo = num;}
};