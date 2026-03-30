#include "tokenHandler.h"

using namespace std;

void salvarToken(classeToken token, const string &nome, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    tabela.emplace_back(tabelaToken{
        token,
        nome,
        arquivo.getLinhaPivo(),
        arquivo.getColunaPivo()
    });
}

string toSString(classeToken c){
    switch (c){
        case classeToken::LITERAIS: return "LITERAL";
        case classeToken::IDENTIFICADORES: return "IDENTIFICADOR";
        case classeToken::COMENTARIOS: return "COMENTARIO";
        case classeToken::PALAVRA_RESERVADA: return "PALAVRA_RESERVADA";
        case classeToken::NUMERAIS: return "NUMERAL";
        case classeToken::OPERADOR_LOGICO_MATEMATICO: return "OPERADOR";
        case classeToken::SEPARADOR: return "SEPARADOR";
        default: return "so pra tirar o warning";
    }
}


// tabelar erros identificados nas classes
void erroFormado(const string& tipo, leitorArquivo &arquivo, const string& token, vector<tabelaERRO> &tabelaInvalidos){
    tabelaInvalidos.emplace_back(tabelaERRO{
        token,
        tipo,
        arquivo.getLinhaPivo(),
        arquivo.getColunaPivo()
    });
}


// aglomerar invalidos soltos
int erroToken(char pivo, leitorArquivo &arquivo, vector<tabelaERRO> &tabelaInvalidos){

    arquivo.setColunaPivo(arquivo.getColuna());
    arquivo.setLinhaPivo(arquivo.getLinha());


    string token;
    token += pivo;

    char c;

    while (arquivo.peekChar(c)){

        // se ler letra, numero, espaços e separador, sai
        if (isspace(c) || 
            isalnum(c) || c == '_' ||
            c == '"' ||
            c == '/' ||
            c == '+' || c == '-' || c == '*' || c == '=' ||
            c == '<' || c == '>' || c == '!' ||
            c == '&' || c == '|' ||
            c == '{' || c == '}' || c == '(' || c == ')' ||
            c == ';' || c == ',' || c == ':'){
            break;
        }

        arquivo.lerChar(c);
        token += c;
    }

    erroFormado("CARACTER INVALIDO!", arquivo, token, tabelaInvalidos);
    return 1;
}

int litarais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela, vector<tabelaERRO> &tabelaInvalidos){

    if (pivo == '"'){
        arquivo.setColunaPivo(arquivo.getColuna());
        arquivo.setLinhaPivo(arquivo.getLinha());

        string token = "\"";
        char batedor;

        while (arquivo.lerChar(batedor)){
            if (batedor == '"'){
                token += "\"";
                salvarToken(classeToken::LITERAIS, token, arquivo, tabela);
                return 1;
            }
            token += batedor;
        }
        erroFormado("LITERAL MAL FORMATADO!", arquivo, token, tabelaInvalidos);
        return 1; // evitar que o caracter antes do EOF caia em outra classe
    }
    return 0;
}



int comentarios(char pivo, leitorArquivo &arquivo /*, vector<tabelaToken> &tabela*/, vector<tabelaERRO> &tabelaInvalidos){
    
    if (pivo == '/'){
        arquivo.setColunaPivo(arquivo.getColuna());
        arquivo.setLinhaPivo(arquivo.getLinha());

        char batedor;

        if (!arquivo.peekChar(batedor)) return 0; // EOF ou \n como final do "//"

        if (batedor == '/'){
            arquivo.lerChar(batedor); 

            string token = "/";

            while (arquivo.lerChar(batedor)){
                token += batedor;
                if (batedor == '\n'){
                    // salvarToken(classeToken::COMENTARIOS, token, arquivo, tabela);
                    return 1;
                }
            }
            return 1; // fazer com que consuma o EOF caso bata no fim
        }
        
        else if (batedor == '*'){
            arquivo.lerChar(batedor); 
            
            string token = "/*";
            
            while (arquivo.lerChar(batedor)){
                token += batedor;
                
                if (batedor == '*'){
                    char prox;
                    if (!arquivo.peekChar(prox)) break; // EOF
                    
                    if (prox == '/'){
                        arquivo.lerChar(prox); 
                        // salvarToken(classeToken::COMENTARIOS, token, arquivo, tabela);
                        return 1;
                    }
                }
                
                token += batedor;
            }
            erroFormado("COMENTARIO MAL FORMATADO!", arquivo, token, tabelaInvalidos);
return 1;
        }
    }
    return 0;
}


int operadoMatLog(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){
    if(pivo == '+' || pivo == '-' || pivo == '*' || pivo == '/' || pivo == '|' || 
       pivo == '&' || pivo == '=' || pivo == '!' || pivo == '<' || pivo == '>'){
        char batedor;
        arquivo.setColunaPivo(arquivo.getColuna());
        arquivo.setLinhaPivo(arquivo.getLinha());

        arquivo.peekChar(batedor);

        if((batedor == pivo) || (batedor == '=' && (pivo == '<' || pivo == '>'))){
            string token = "";
            token += pivo;
            token += batedor;

            arquivo.lerChar(batedor);
            salvarToken(classeToken::OPERADOR_LOGICO_MATEMATICO, token, arquivo, tabela);
            return 1;
        } else {
            string token = "";
            token += pivo;
            salvarToken(classeToken::OPERADOR_LOGICO_MATEMATICO, token, arquivo, tabela);
            return 1;
        }
    }
    return 0;
}


int numerais(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela, vector<tabelaERRO> &tabelaInvalidos){

    if (!isdigit(pivo)) return 0;

    arquivo.setColunaPivo(arquivo.getColuna());
    arquivo.setLinhaPivo(arquivo.getLinha());

    string token;
    token += pivo;

    char batedor;
    bool temPonto = false;
    bool temDigitoAposPonto = false;
    bool doisPonto = false;
    bool invalido = false;

    while(arquivo.peekChar(batedor)){

        if(isdigit(batedor)){
            arquivo.lerChar(batedor);
            token += batedor;

            if(temPonto) temDigitoAposPonto = true; // pelo menos um numero apos o ponto
        }
        
        else if(batedor == '.' && temPonto){ // erro: dois ou mais ponts
            arquivo.lerChar(batedor);
            doisPonto = true;
            token += batedor;
        }

        else if (batedor == '.' && !temPonto){ // um ponto
            arquivo.lerChar(batedor);
            token += batedor;
            temPonto = true;
        }

        else if (batedor == 'f'){ //f
            if (!temPonto || temDigitoAposPonto){
                arquivo.lerChar(batedor);
                token += batedor;
            }
            break;
        } 

        else if (isalpha(batedor)){
            arquivo.lerChar(batedor);
            token += batedor;
            invalido = true;
        }

        else {
            break;
        }
    }

    if((temPonto && !temDigitoAposPonto) || doisPonto || invalido){ // 12. ou 1.2.2.2 ou 12a2
        erroFormado("NUMERAL MAL FORMATADO!", arquivo, token, tabelaInvalidos);
        return 1;
    }

    salvarToken(classeToken::NUMERAIS, token, arquivo, tabela);
    return 1;
}


int separador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela){

    if (pivo == '{' || pivo == '}' ||
        pivo == '(' || pivo == ')' ||
        pivo == '[' || pivo == ']' ||
        pivo == ';' || pivo == ',' || pivo == ':'){

        arquivo.setColunaPivo(arquivo.getColuna());
        arquivo.setLinhaPivo(arquivo.getLinha());

        string token(1, pivo);

        salvarToken(classeToken::SEPARADOR, token, arquivo, tabela);
        return 1;
    }
    return 0;
}


bool ehPalavraReservada(const string& token){
    static const unordered_set<string> reservadas = {
        "if", "for", "int", "bool", "string", "float"
    };

    return reservadas.count(token) > 0; 
}


int identificador(char pivo, leitorArquivo &arquivo, vector<tabelaToken> &tabela, vector<tabelaERRO> &tabelaInvalidos){

    if (!(isalpha(pivo) || pivo == '_')) // a-z ou _
        return 0;

    arquivo.setColunaPivo(arquivo.getColuna());
    arquivo.setLinhaPivo(arquivo.getLinha());

    string token;
    token += pivo;

    char batedor;
    bool invalido = false;

    while (arquivo.peekChar(batedor)){

        // válido
        if (isalnum(batedor) || batedor == '_'){ // a-z,  0-9 ou  _
            arquivo.lerChar(batedor);
            token += batedor;
        }

        // caractere inavlidos
        else if (!isspace(batedor) &&
                 batedor != '"' && batedor != '/' &&
                 batedor != '+' && batedor != '-' && batedor != '*' &&
                 batedor != '=' && batedor != '<' && batedor != '>' &&
                 batedor != '!' && batedor != '&' && batedor != '|' &&
                 batedor != '[' && batedor != ']' &&
                 batedor != '{' && batedor != '}' && batedor != '(' && batedor != ')'
        ){
            arquivo.lerChar(batedor);
            token += batedor;
            invalido = true;
        }
        
        // caracter valido do if de cima
        else {
            break;
        }
    }

    if (invalido){
        erroFormado("IDENTIFICADOR MAL FORMATADO!", arquivo, token, tabelaInvalidos);
    }
    else if (ehPalavraReservada(token)){
        salvarToken(classeToken::PALAVRA_RESERVADA, token, arquivo, tabela);
    }
    else {
        salvarToken(classeToken::IDENTIFICADORES, token, arquivo, tabela);
    }

    return 1;
}