#include "arvoreHandler.hpp"

void NoArvore::podar() {
    for(auto& filho : filhos)
        filho.podar();

    vector<NoArvore> novosFi;
    for(auto& filho : filhos) {
        if(filho.id == -1 && filho.filhos.size() == 1) {
            novosFi.push_back(filho.filhos[0]);
        } else {
            novosFi.push_back(filho);
        }
    }
    filhos = novosFi;
}

string tipoToString(tipoStatement t) {
    switch(t) {
        case tipoStatement::EXPRESSAO:       return "EXPRESSAO";
        case tipoStatement::REPETICAO:       return "REPETICAO";
        case tipoStatement::CONDICAO:        return "CONDICAO";
        case tipoStatement::DECLARACAO:      return "DECLARACAO";
        case tipoStatement::SENTENCA:        return "SENTENCA";
        case tipoStatement::BLOCO:           return "BLOCO";
        case tipoStatement::TOKEN:           return "TOKEN";
        case tipoStatement::RAIZ:            return "RAIZ";
        case tipoStatement::ATRIBUICAO:      return "ATRIBUICAO";
        default: return "?";
    }
}

void imprimirArvore(const NoArvore& no, const vector<tabelaToken>& tabela, string prefixo, bool ultimo) {
    cout << prefixo;
    cout << (ultimo ? "└── " : "├── ");

    if(no.id == -1) {
        cout << "[" << tipoToString(no.tipo) << "]" << "\n";
    } else {
        cout << tabela[no.id].nome << "\n";
    }

    string novoPrefixo = prefixo + (ultimo ? "    " : "│   ");
    for(int i = 0; i < (int)no.filhos.size(); i++) {
        bool ehUltimo = (i == (int)no.filhos.size() - 1);
        imprimirArvore(no.filhos[i], tabela, novoPrefixo, ehUltimo);
    }
}