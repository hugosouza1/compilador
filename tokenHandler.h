#pragma once

#include <string>
#include <vector>
#include <fstream>

class leitorArquivo {
    private:
        int linha;
        int coluna;
        int colunaPivo;
        std::ifstream arquivo;

    public:
        // construtor
        leitorArquivo(const std::string& nomeArquivo);

        // leitura
        bool lerChar(char &c);

        // getters
        int getLinha() const;
        int getColuna() const;
        int getColunaPivo() const;

        // setter
        void setColunaPivo(int num);
};

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

// funções do analisador léxico
void salvarToken(classeToken token, const std::string &nome,
                 const leitorArquivo &arquivo,
                 std::vector<tabelaToken> &tabela);

int litarais(char pivo, leitorArquivo &arquivo,
             std::vector<tabelaToken> &tabela);