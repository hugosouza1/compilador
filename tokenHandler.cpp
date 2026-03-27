#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <vector>


enum class classeToken{
    LITERAIS,
    IDENTIFICADORES,
    COMENTARIOS,
    PALAVRA_RESERVADA,
    NUMERAIS,
    OPERADOR_LOGICO_MATEMATICO,
    SEPARADOR
};

struct tabelaToken{
    classeToken classe;
    string nome;
    int linha;
    int coluna;
};

void salvarToken(classeToken token, string nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    tabelaToken t;
    t.classe = token;
    t.nome = nome;
    t.linha = arquivo.getLinha();
    t.coluna = arquivo.getColunaPivo();
    tabela.emplace_back(t);
}