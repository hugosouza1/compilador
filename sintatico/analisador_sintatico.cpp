#include "analisador_sintatico.hpp"

string tipoToString(tipoStatement t) {
    switch(t) {
        case tipoStatement::EXPRESSAO:  return "EXPRESSAO";
        case tipoStatement::REPETICAO:  return "REPETICAO";
        case tipoStatement::CONDICAO:   return "CONDICAO";
        case tipoStatement::DECLARACAO: return "DECLARACAO";
        case tipoStatement::SENTENCA:   return "SENTENCA";
        case tipoStatement::BLOCO:      return "BLOCO";
        case tipoStatement::TOKEN:      return "TOKEN";
        case tipoStatement::RAIZ:      return "RAIZ";
        default: return "?";
    }
}

void imprimirArvore(const NoArvore& no, const vector<tabelaToken>& tabela, string prefixo = "", bool ultimo = true) {
    cout << prefixo;
    cout << (ultimo ? "└── " : "├── ");

    if(no.id == -1) {
        cout << "[" << tipoToString(no.tipo) << "]" << "\n";
    } else {
        cout << tabela[no.id].nome /* << " (" << tipoToString(no.tipo) << ")"*/ << "\n";
    }

    string novoPrefixo = prefixo + (ultimo ? "    " : "│   ");
    for(int i = 0; i < (int)no.filhos.size(); i++) {
        bool ehUltimo = (i == (int)no.filhos.size() - 1);
        imprimirArvore(no.filhos[i], tabela, novoPrefixo, ehUltimo);
    }
}


int analisadorSintatico(vector<tabelaToken>& tabela){
    Analisador ParserArvore(tabela); 
    bool sucesso = true;

    while(!ParserArvore.fimDaEntrada()){
        NoArvore subArvore(-1, tipoStatement::SENTENCA);
        
        if(ParserArvore.sentenca(subArvore)){
            // merge da subarvore na raiz
            for(auto& filho : subArvore.filhos)
                ParserArvore.raiz.filhos.push_back(filho);
        } else {
            sucesso = false;
            ParserArvore.imprimirErro();

            // avança até token de sincronização
            ParserArvore.sincronizarPanico();
        }
    }

    if(sucesso){
        cout << "Sucesso\n";
        ParserArvore.raiz.podar();
        imprimirArvore(ParserArvore.raiz, tabela);
        return 1;
    } else {
        cout << "Fracasso — erros encontrados\n";
        return 0;
    }
}