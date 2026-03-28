#include "tokenHandler.h"

using namespace std;

void salvarToken(classeToken token, const string &nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    tabela.emplace_back(tabelaToken{
        token,
        nome,
        arquivo.getLinha(),
        arquivo.getColunaPivo()
    });
}

string toSString(classeToken c) {
    switch (c) {
        case classeToken::LITERAIS: return "LITERAIS";
        case classeToken::IDENTIFICADORES: return "IDENTIFICADORES";
        case classeToken::COMENTARIOS: return "COMENTARIOS";
        case classeToken::PALAVRA_RESERVADA: return "PALAVRA_RESERVADA";
        case classeToken::NUMERAIS: return "NUMERAIS";
        case classeToken::OPERADOR_LOGICO_MATEMATICO: return "OPERADOR";
        case classeToken::SEPARADOR: return "SEPARADOR";
        default: return "nada";
    }
}

int litarais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela) {

    if (pivo == '"') {
        arquivo.setColunaPivo(arquivo.getColuna());

        string token = "";
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



int comentarios(char pivo, leitorArquivo &arquivo /*, vector<tabelaToken> &tabela*/) {
    
    // cout << pivo << "\n";
    if (pivo == '/') {
        arquivo.setColunaPivo(arquivo.getColuna());

        char batedor;

        if (!arquivo.peekChar(batedor)) return 0;

        // comentário de linha 
        if (batedor == '/') {
            arquivo.lerChar(batedor); 

            string token = "";

            while (arquivo.lerChar(batedor)) {
                if (batedor == '\n') {
                    // salvarToken(classeToken::COMENTARIOS, token, arquivo, tabela);
                    return 1;
                }
                token += batedor;
            }
        }

        // comentário de bloco 
        else if (batedor == '*') {
            arquivo.lerChar(batedor); 

            string token = "";

            while (arquivo.lerChar(batedor)) {

                if (batedor == '*') {
                    char prox;
                    if (!arquivo.peekChar(prox)) return 0;

                    if (prox == '/') {
                        arquivo.lerChar(prox); 
                        // salvarToken(classeToken::COMENTARIOS, token, arquivo, tabela);
                        return 1;
                    }
                }

                token += batedor;
            }
        }
    }
    return 0;
}


int operadoMatLog(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    if(pivo == '+' || pivo == '-' || pivo == '*' || pivo == '/' || pivo == '|' || 
       pivo == '&' || pivo == '=' || pivo == '!' || pivo == '<' || pivo == '>'){
        char batedor;
        if(!arquivo.peekChar(batedor)) return 0;

        if((batedor == pivo) || (batedor == '=' && (pivo == '<' || pivo == '>'))){
            string token = "";
            token += static_cast<char>(pivo);
            token += static_cast<char>(batedor);

            arquivo.lerChar(batedor);
            salvarToken(classeToken::OPERADOR_LOGICO_MATEMATICO, token, arquivo, tabela);
            return 1;
        } else {
            string token = "";
            token += static_cast<char>(pivo);
            salvarToken(classeToken::OPERADOR_LOGICO_MATEMATICO, token, arquivo, tabela);
            return 1;
        }
    }
    return 0;
}


int numerais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){

    if (!isdigit(pivo))
        return 0;

    arquivo.setColunaPivo(arquivo.getColuna());

    string token;
    token += pivo;

    char c;
    bool temPonto = false;
    bool temDigitoAposPonto = false;

    while(arquivo.peekChar(c)){

        if(isdigit(c)){
            arquivo.lerChar(c);
            token += c;

            if(temPonto)
                temDigitoAposPonto = true;
        }

        else if (c == '.' && !temPonto) {
            arquivo.lerChar(c);
            token += c;
            temPonto = true;
        }

        else if (c == 'f') {
            if (!temPonto || temDigitoAposPonto) {
                arquivo.lerChar(c);
                token += c;
            }
            break;
        }

        else {
            break;
        }
    }

    salvarToken(classeToken::NUMERAIS, token, arquivo, tabela);
    return 1;
}


int separador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){

    if (isspace(pivo)) {
        return 1; // igonra espaço vazio
    }

    if (pivo == '{' || pivo == '}' ||
        pivo == '(' || pivo == ')' ||
        pivo == '[' || pivo == ']' ||
        pivo == ';' || pivo == ',' ||
        pivo == ':') {

        arquivo.setColunaPivo(arquivo.getColuna());

        string token(1, pivo);

        salvarToken(classeToken::SEPARADOR, token, arquivo, tabela);
        return 1;
    }
    return 0;
}


bool ehPalavraReservada(const string& token) {
    static const unordered_set<string> reservadas = {
        "if", "for", "int", "bool", "string", "float"
    };

    return reservadas.count(token) > 0; 
}


int identificador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){

    if (!(isalpha(pivo) || pivo == '_')) // a-z e _
        return 0;

    arquivo.setColunaPivo(arquivo.getColuna());

    string token = "";
    token += pivo;

    char batedor;

    while (arquivo.peekChar(batedor)) {
        if (isalnum(batedor) || batedor == '_') { // a-z ou 0-9
            arquivo.lerChar(batedor);
            token += batedor;
        } else {
            break;
        }
    }

    if (ehPalavraReservada(token)) {
        salvarToken(classeToken::PALAVRA_RESERVADA, token, arquivo, tabela);
    } else {
        salvarToken(classeToken::IDENTIFICADORES, token, arquivo, tabela);
    }

    return 1;
}