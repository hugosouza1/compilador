#include "semantico.hpp"
#include "arvoreHandler.hpp"

tipoVar Semantica::resultado(Operador op, tipoVar esq, tipoVar dir) {
    return tabelaTipos[(int)op][(int)esq][(int)dir];
}

tipoVar stringPraTipoVar(string x){
    if(x == "int")
        return tipoVar::INT;

    if(x == "float")
        return tipoVar::FLOAT;

    if(x == "string")
        return tipoVar::STRING;

    if(x == "bool")
        return tipoVar::BOOLEAN;

    return tipoVar::NONE;
}

bool Semantica::declararIdentificador(const tabelaToken& identi, tipoVar var) {
    for(const auto& var : variaveis) {
        if(var.token == identi.nome && var.escopo == escopoAtual) {
            return false; // já declarado
        }
    }

    Simbolo novo;
    novo.token = identi.nome;
    novo.tipoToken = var; 
    novo.linhaDec = identi.linha;
    novo.colunaDec = identi.coluna;
    novo.escopo = escopoAtual;

    variaveis.push_back(novo);
    return true;
}


Simbolo* Semantica::buscarIdentificador(const string& nome){
    for(int i = variaveis.size()-1; i >= 0; i--){
        if(variaveis[i].token == nome)
            return &variaveis[i];
    }

    return nullptr;
}

string tipoVarToString(tipoVar tipo) {
    switch(tipo) {
        case tipoVar::INT:    return "INT";
        case tipoVar::FLOAT:  return "FLOAT";
        case tipoVar::STRING: return "STRING";
        case tipoVar::BOOLEAN:   return "BOOLEAN";
        default:              return "NONE";
    }
}

void Semantica::imprimirTabela() {
    cout << "\n===== TABELA DE SIMBOLOS =====\n";

    cout << left
         << setw(20) << "Token"
         << setw(10) << "Tipo"
         << setw(10) << "Linha"
         << setw(10) << "Coluna"
         << '\n';

    cout << string(50, '-') << '\n';

    for(const auto& var : variaveis) {
        cout << left
             << setw(20) << var.token
             << setw(10) << tipoVarToString(var.tipoToken)
             << setw(10) << var.linhaDec
             << setw(10) << var.colunaDec
             << '\n';
    }

    cout << string(50, '=') << '\n';
}

tipoVar Semantica::inferirTipoExpressao(const NoArvore& no, Operador op){
    if(no.filhos.empty())
        return tipoVar::NONE;

    if(no.filhos.size() == 1)
        return no.filhos[0].tipoToken;

    tipoVar resultado = no.filhos[0].tipoToken;

    for(size_t i = 1; i + 1 < no.filhos.size(); i += 2){
        tipoVar dir = no.filhos[i + 1].tipoToken;

        resultado = this->resultado(op, resultado, dir);

        if(resultado == tipoVar::NONE)
            return tipoVar::NONE;
    }

    return resultado;
}


void Semantica::entrarEscopo() {
    escopoAtual++;
}

void Semantica::sairEscopo() {
    while(!variaveis.empty() && variaveis.back().escopo == escopoAtual) {
        variaveis.pop_back();
    }

    escopoAtual--;
}
