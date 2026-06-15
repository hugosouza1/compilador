#include "gramatica.hpp"

bool Analisador::D2(NoArvore& pai) {
    if (pos >= (int)tabela.size()) return true;

    string nome = tabela[pos].nome;

    if (nome == "," || nome == ";" || nome == ")")
        return true;

    if (nome == "=" || nome == "+=" || nome == "-=") {

        NoArvore d2No(-1, tipoStatement::ATRIBUICAO);
        pai.filhos.push_back(d2No);
        NoArvore& noAtual = pai.filhos.back();

        
        NoArvore opNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(opNo);
        proxPos();

        if (!D3(noAtual)) return false;

        return true;
    }

    return false; 
}

bool Analisador::D3(NoArvore& pai) {

    if (pos >= (int)tabela.size()) return false;
        
    classeToken cls = tabela[pos].classe;
    string nome = tabela[pos].nome;
        
    if (nome == ")") return true;

    if (cls == classeToken::IDENTIFICADORES ||
        cls == classeToken::NUMERAIS_INT        ||
        cls == classeToken::NUMERAIS_FLOAT        ||
        cls == classeToken::LITERAIS        ||
        nome == "!" || nome == "(" || nome == "false" || nome == "true") {
        
        // cout << "pos: " << pos << "  token: " << tabela[pos].nome << "\n";
        NoArvore d3No(-1, tipoStatement::EXPRESSAO);
        pai.filhos.push_back(d3No);
        NoArvore& noAtual = pai.filhos.back();

        if(!expressao(noAtual)) return false;
        return true;
    }

    return false;
}

bool Analisador::D1(NoArvore& pai) {

    if (pos >= (int)tabela.size()) return false;

    if (tabela[pos].nome == ";") return true;

    if (tabela[pos].nome == ",") {

        NoArvore d1No(-1, tipoStatement::DECLARACAO, pai.tipoToken);
        pai.filhos.push_back(d1No);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore virgulaNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(virgulaNo);
        proxPos();

        if ((pos >= (int)tabela.size()) || (tabela[pos].classe != classeToken::IDENTIFICADORES))
            return false;

        NoArvore idNo(pos, tipoStatement::TOKEN, noAtual.tipoToken);
        
        if( ! regras.declararIdentificador(tabela[pos], noAtual.tipoToken)) return false;

        noAtual.filhos.push_back(idNo);
        proxPos();

        if (!D2(noAtual)) return false;
        if (!D1(noAtual)) return false;

        return true;
    }

    return false;
}


bool Analisador::declaracao(NoArvore& pai) {

    if (pos >= (int)tabela.size() || !tipo(tabela[pos].nome))
        return false;

    NoArvore declaracaoNo(-1, tipoStatement::DECLARACAO, stringPraTipoVar(tabela[pos].nome));
    pai.filhos.push_back(declaracaoNo);
    NoArvore& noAtual = pai.filhos.back();

    NoArvore tipoNo(pos, tipoStatement::TOKEN);
    noAtual.filhos.push_back(tipoNo);
    proxPos();

    if (pos >= (int)tabela.size() || tabela[pos].classe != classeToken::IDENTIFICADORES)
        return false;

    NoArvore idNo(pos, tipoStatement::TOKEN, noAtual.tipoToken);
    
    if( ! regras.declararIdentificador(tabela[pos], noAtual.tipoToken)) return false;

    noAtual.filhos.push_back(idNo);
    proxPos();

    if (!D2(noAtual)) return false;
    if (!D1(noAtual)) return false;

    return true;
}