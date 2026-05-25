#include "gramatica.hpp"

bool Analisador::S1(NoArvore& pai){
    // cerr << "S1: pos=" << pos << "\n";
    if(pos >= (int)tabela.size())
        return true;

    if(tabela[pos].nome == "}" )
        return true;

    if(!sentenca(pai)) return false;
    return true;
}

bool Analisador::sentenca(NoArvore& pai){
    // cerr << "sentenca: pos=" << pos << "\n";

    if(pos >= (int)tabela.size()) return false;
    
    string nome = tabela[pos].nome;
    classeToken cls = tabela[pos].classe;

    if(!tipo(nome) &&
       nome != "if" && nome != "while" && nome != "for" &&
       nome != "!" && nome != "(" && nome != "true" && nome != "false" &&
       cls != classeToken::IDENTIFICADORES &&
       cls != classeToken::NUMERAIS &&
       cls != classeToken::LITERAIS)
        return false;

    NoArvore sentNo(-1, tipoStatement::SENTENCA);
    pai.filhos.push_back(sentNo);
    NoArvore& noAtual = pai.filhos.back();

    // FIRST(declaracao) = tipo
    if(tipo(tabela[pos].nome)){
        if(!declaracao(noAtual)) return false;
        if(tabela[pos].nome != ";") return false;
        NoArvore ptNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(ptNo);
        proxPos();

        if(!S1(noAtual)) return false;
        return true;
    }

    // FIRST(expressao) = !, (, identi, true, false, numeral, literal
    if(tabela[pos].nome == "!" || tabela[pos].nome == "(" ||
       tabela[pos].nome == "true" || tabela[pos].nome == "false" ||
       tabela[pos].classe == classeToken::IDENTIFICADORES ||
       tabela[pos].classe == classeToken::NUMERAIS ||
       tabela[pos].classe == classeToken::LITERAIS){
        if(!expressao(noAtual)) return false;
        if(tabela[pos].nome != ";") return false;
        NoArvore ptNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(ptNo);
        proxPos();

        if(!S1(noAtual)) return false;
        return true;
    }

    // FIRST(condicao) = if
    if(tabela[pos].nome == "if"){
        if(!condicao(noAtual)) return false;

        if(!S1(noAtual)) return false;
        return true;
    }

    // FIRST(repeticao) = while, for
    if(tabela[pos].nome == "while" || tabela[pos].nome == "for"){
        if(!repeticao(noAtual)) return false;

        if(!S1(noAtual)) return false;
        return true;
    }

    return false;
}