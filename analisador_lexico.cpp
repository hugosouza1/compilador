#include <iostream>
#include <fstream>
#include <regex>
#include <vector>

using namespace std;


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


void salvarToken(classeToken token, string nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    tabelaToken t;
    t.classe = token;
    t.nome = nome;
    t.linha = arquivo.getLinha();
    t.coluna = arquivo.getColunaPivo();
    tabela.emplace_back(t);
}


int litarais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    if(pivo == '"'){
        arquivo.setColunaPivo(arquivo.getColuna());

        string token = "";
        char batedor;
        while(arquivo.lerChar(batedor)){
            
            if(batedor == '"'){
                salvarToken(classeToken::LITERAIS, token, arquivo, tabela);            
                return 1;
            } 
            token += batedor;   
        }
    } 
    return 0;
}


int main() {
    leitorArquivo arquivo;

    vector<tabelaToken> tabela;
    char c;

    while (arquivo.lerChar(c)) {
        if (litarais(c, arquivo, tabela)) continue;

        // outros reconhecedores aqui (identificador, número, etc)
    }

    // Exemplo de saída
    for (const auto &t : tabela) {
        cout << "Token: " << t.nome 
             << " Linha: " << t.linha 
             << " Coluna: " << t.coluna << endl;
    }

    return 0;
}