#include "gramatica.hpp"

void Analisador::proxPos() {
    pos++;
}

bool Analisador::tipo(string token){

    static const unordered_set<string> reservadas = {
        "int", "bool", "string", "float"
    };

    return reservadas.count(token) > 0;
}

bool Analisador::D2(NoArvore& pai) {
    // FIRST(D2) = {=, +=, -=}  →  row D2, col =  → rule 4
    // FOLLOW(D2) = {",", ";"}  →  row D2, col , and ; → rule 5 (ε)

    classeToken cls = tabela[pos].classe;
    string nome     = tabela[pos].nome;

    // ε production: nothing to consume
    if (nome == "," || nome == ";" || pos >= (int)tabela.size())
        return true;

    // Rule 4: D2 → <OP> <D3>
    if (nome == "=" || nome == "+=" || nome == "-=") {

        NoArvore d2No(-1, tipoStatement::EXPRESSAO);
        pai.filhos.push_back(d2No);
        NoArvore& noAtual = pai.filhos.back();

        // OP node
        NoArvore opNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(opNo);
        proxPos();

        // D3
        if (!D3(noAtual))
            return false;

        return true;
    }

    return false; // unexpected token
}

bool Analisador::D3(NoArvore& pai) {
    // Rule 6: D3 → <identificador> | <numeral> | <literal> | <expressão>
    // FIRST(D3) = {a}  (identifiers, numerals, literals, expressions)

    classeToken cls = tabela[pos].classe;

    if (cls == classeToken::IDENTIFICADORES ||
        cls == classeToken::NUMERAIS        ||
        cls == classeToken::LITERAIS
        // cls == classeToken::EXPRESSAO
        //     AAAAAAAAAAAAAAAARRUMAR DEPOIS
    ) {

        NoArvore d3No(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(d3No);
        proxPos();
        return true;
    }

    return false;
}

bool Analisador::D1(NoArvore& pai) {

    if (tabela[pos].nome == ";")
        return true;

    if (tabela[pos].nome == ",") {

        NoArvore d1No(pos, tipoStatement::DECLARACAO);
        pai.filhos.push_back(d1No);
        NoArvore& noAtual = pai.filhos.back();

        // nó da vírgula como filho
        NoArvore virgulaNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(virgulaNo);
        proxPos();

        if (tabela[pos].classe != classeToken::IDENTIFICADORES)
            return false;

        NoArvore idNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(idNo);
        proxPos();

        if (!D2(noAtual)) return false;
        if (!D1(noAtual)) return false;

        return true;
    }

    return false;
}


bool Analisador::declaracao(NoArvore& pai) {

    if (!tipo(tabela[pos].nome))
        return false;

    NoArvore declaracaoNo(-1, tipoStatement::DECLARACAO);
    pai.filhos.push_back(declaracaoNo);
    NoArvore& noAtual = pai.filhos.back();

    // nó de tipo como filho
    NoArvore tipoNo(pos, tipoStatement::TOKEN);
    noAtual.filhos.push_back(tipoNo);
    proxPos();

    if (tabela[pos].classe != classeToken::IDENTIFICADORES)
        return false;

    NoArvore idNo(pos, tipoStatement::TOKEN);
    noAtual.filhos.push_back(idNo);
    proxPos();

    if (!D2(noAtual)) return false;
    if (!D1(noAtual)) return false;

    return true;
}