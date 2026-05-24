#include "gramatica.hpp"


bool Analisador::bloco(NoArvore& pai){
    if(tabela[pos].nome == "{"){
        NoArvore blocoNo(-1, tipoStatement::CONDICAO); // nó intermediário
        pai.filhos.push_back(blocoNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore abreNo(pos, tipoStatement::TOKEN); // { como filho
        noAtual.filhos.push_back(abreNo);
        proxPos();

        if(!sentenca(noAtual)) return false;

        if(tabela[pos].nome != "}") return false;
        NoArvore fechaNo(pos, tipoStatement::TOKEN); // } como filho
        noAtual.filhos.push_back(fechaNo);
        proxPos();

        return true;
    }
    return false;
}



bool Analisador::condicao(NoArvore& pai){
    if(tabela[pos].nome == "if"){
        NoArvore condNo(-1, tipoStatement::CONDICAO); // nó intermediário
        pai.filhos.push_back(condNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore ifNo(pos, tipoStatement::TOKEN); // if
        noAtual.filhos.push_back(ifNo);
        proxPos();

        if(tabela[pos].nome != "(") return false;
        NoArvore abreNo(pos, tipoStatement::TOKEN); // (
        noAtual.filhos.push_back(abreNo);
        proxPos();

        if(!expressao(noAtual)) return false;

        if(tabela[pos].nome != ")") return false; // )
        NoArvore fechaNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(fechaNo);
        proxPos();

        if(!bloco(noAtual)) return false; // noAtual, não pai
        if(!C1(noAtual))    return false; // noAtual, não pai
        return true;
    }
    return false;
}


bool Analisador::C1(NoArvore& pai){

    string nome = tabela[pos].nome;
    if (nome == "}" || pos >= (int)tabela.size())
        return true;

    if(nome == "else"){
        NoArvore c1No(-1, tipoStatement::CONDICAO); // nó intermediário
        pai.filhos.push_back(c1No);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore elseNo(pos, tipoStatement::TOKEN); // else como folha
        noAtual.filhos.push_back(elseNo);
        proxPos();

        if(!C2(noAtual)) return false;
        return true;
    }
   
    return false; 

}


bool Analisador::C2(NoArvore& pai){
    string nome = tabela[pos].nome;

    if(nome == "if")
        return condicao(pai);

    if(nome == "{")
        return bloco(pai);

    return false;
}


bool Analisador::repeticao(NoArvore& pai){
    string nome = tabela[pos].nome;

    if(nome == "while"){
        NoArvore condNo(-1, tipoStatement::REPETICAO); // nó intermediário
        pai.filhos.push_back(condNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore ifNo(pos, tipoStatement::TOKEN); // while
        noAtual.filhos.push_back(ifNo);
        proxPos();

        if(tabela[pos].nome != "(") return false;
        NoArvore abreNo(pos, tipoStatement::TOKEN); // (
        noAtual.filhos.push_back(abreNo);
        proxPos();

        if(!expressao(noAtual)) return false;

        if(tabela[pos].nome != ")") return false; // )
        NoArvore fechaNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(fechaNo);
        proxPos();

        if(!bloco(noAtual)) return false;
        return true;
    }

    if(nome == "for"){
        NoArvore condNo(-1, tipoStatement::REPETICAO); // nó intermediário
        pai.filhos.push_back(condNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore forNo(pos, tipoStatement::TOKEN); // for
        noAtual.filhos.push_back(forNo);
        proxPos();

        // (
        if(tabela[pos].nome != "(") return false;
        NoArvore abreNo(pos, tipoStatement::TOKEN);   
        noAtual.filhos.push_back(abreNo);
        proxPos();

        // declaração, expressão, ou vazio
        if(tipo(tabela[pos].nome)){
            if(!declaracao(noAtual)) return false;
        } else if(tabela[pos].nome != ";"){
            if(!expressao(noAtual)) return false;
        }
        
        // consome ;
        if(tabela[pos].nome != ";") return false;
        noAtual.filhos.push_back(NoArvore(pos, tipoStatement::TOKEN));
        proxPos();

        // condição: expressão ou vazio
        if(tabela[pos].nome != ";"){
            if(!expressao(noAtual)) return false;
        }

        // consome ;
        if(tabela[pos].nome != ";") return false;
        noAtual.filhos.push_back(NoArvore(pos, tipoStatement::TOKEN));
        proxPos();

        // incremento: expressão ou vazio
        if(tabela[pos].nome != ")"){
            if(!expressao(noAtual)) return false;
        }

        // consome )
        if(tabela[pos].nome != ")") return false;
        noAtual.filhos.push_back(NoArvore(pos, tipoStatement::TOKEN));
        proxPos();         


        if(!bloco(noAtual)) return false;
        return true;
    }

    return false;

}