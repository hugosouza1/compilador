#include "gramatica.hpp"

bool Analisador::expressao(NoArvore& pai){
    // cerr << "expressao pos: " << pos << "\n"; 
    if( ! (ATR(pai))) return false;      
    return true;
}

bool Analisador::ATR(NoArvore& pai){
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();
    
    if(!EL(noAtual))   return false;      
    if(!ATR1(noAtual)) return false;
    return true; 
}

bool Analisador::ATR1(NoArvore& pai){

    if (pos >= (int)tabela.size())
            return true;

    string nome = tabela[pos].nome;
    
    if (nome == ")" || nome == ";" || nome == ",")
        return true;

    if(nome == "=" || nome == "+=" || nome == "-="){
        NoArvore opNo(pos, tipoStatement::TOKEN); 
        pai.filhos.push_back(opNo);
        proxPos();

        if(!ATR(pai)) return false; 
        return true;
    }


    return false;

}


bool Analisador::EL(NoArvore& pai){
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();
    
    if( ! TL(noAtual)) return false; 
    if( ! EL1(noAtual)) return false; 
    return true;
}


bool Analisador::EL1(NoArvore& pai){
    if (pos >= (int)tabela.size())
            return true;

    string nome = tabela[pos].nome;

    if (nome == ")" || nome == ";" || nome == "=" || nome == "-=" || nome == "+=" || nome == ",")
    return true;

    if(nome == "||"){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        if(!TL(pai))  return false;
        if(!EL1(pai)) return false;
        return true;
    }
   
    return false; 
    
}


bool Analisador::TL(NoArvore& pai){
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();
            
    if( ! ER(noAtual)) return false; 
    if( ! TL1(noAtual)) return false; 

    return true;
}


bool Analisador::TL1(NoArvore& pai){
    if (pos >= (int)tabela.size())
            return true;
    string nome = tabela[pos].nome;
    if (nome == ")" || nome == ";" || nome == "=" || nome == "-=" || nome == "+=" || nome == "||" || nome == ",")
        return true;

    if(nome == "&&"){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        if(!ER(pai))  return false;
        if(!TL1(pai)) return false;
        return true;
    }

    return false;

}


bool Analisador::ER(NoArvore& pai){
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();
    
    if( ! EA(noAtual)) return false; 
    if( ! ER1(noAtual)) return false; 
    return true;

}


bool Analisador::ER1(NoArvore& pai){
    if (pos >= (int)tabela.size())
        return true;

    string nome = tabela[pos].nome;
    if (nome == "||" || nome == ")" || nome == "&&" || nome == ";" || nome == "=" || nome == "-=" || nome == "+=" || nome == ",")
    return true;

    if(nome == ">=" || nome == "<=" || nome == ">" || nome == "<" || nome == "==" || nome == "!="){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        if(!EA(pai))  return false;
        return true;
    }

    return false;

}


bool Analisador::F(NoArvore& pai){
    // std::cerr << "F: pos=" << pos << " token=" << tabela[pos].nome << "\n";

    if (pos >= (int)tabela.size())
            return false;

    if(tabela[pos].nome == "!"){
        NoArvore fNo(-1, tipoStatement::EXPRESSAO);
        pai.filhos.push_back(fNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore opNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(opNo);
        proxPos();
        
        if(!F(noAtual)) return false;
        return true;
    }

    if(tabela[pos].nome == "("){
        NoArvore fNo(-1, tipoStatement::EXPRESSAO);
        pai.filhos.push_back(fNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore abreNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(abreNo);
        proxPos();
        
        if(!expressao(noAtual)) return false;

        if(pos >= (int)tabela.size() || tabela[pos].nome != ")") return false;
        NoArvore fechaNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(fechaNo);
        proxPos();
        return true;
    }

    if(tabela[pos].nome == "true" || tabela[pos].nome == "false"){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();
        
        return true;
    }
    
    if(tabela[pos].classe == classeToken::NUMERAIS || tabela[pos].classe == classeToken::IDENTIFICADORES){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();
        
        if(!P(pai))  return false;
        return true;
    }
    
    if(tabela[pos].classe == classeToken::LITERAIS){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();
        
        return true;
    }


    return false;


}


bool Analisador::T(NoArvore& pai){
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();
    
    if(!F(noAtual))  return false;
    if(!T1(noAtual))  return false;

    return true; 
}


bool Analisador::T1(NoArvore& pai){
    if (pos >= (int)tabela.size()) return true;
    
    string nome = tabela[pos].nome;

    if (nome == "||" || nome == "&&" || nome == ";" || nome == ")" || 
        nome == "=" || nome == "-=" || nome == "+=" ||
        nome == ">=" || nome == "<=" || nome == ">" || nome == "<" || nome == "==" || nome == "!=" || nome == ",")
        return true;

    if(nome == "*" || nome == "/"){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        if(!F(pai))  return false;
        if(!T1(pai))  return false;
        return true;
    }

    return false;

}


bool Analisador::EA(NoArvore& pai){      
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();

    if(!T(noAtual))  return false;
    if(!EA1(noAtual))  return false;

    return true; 
}


bool Analisador::EA1(NoArvore& pai){
    if (pos >= (int)tabela.size())
            return true;

    string nome = tabela[pos].nome;
    if (nome == "||" || nome == "&&" || nome == ";" || nome == "=" || nome == "-=" || nome == "+=" || nome == "," ||
        nome == ">=" || nome == "<=" || nome == ">" || nome == "<" || nome == "==" || nome == "!=" || nome == ")")
        return true;

    if(nome == "+" || nome == "-"){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        if(!T(pai))  return false;
        if(!EA1(pai))  return false;
        return true;
    }

    return false;

}


bool Analisador::P(NoArvore& pai){
    if (pos >= (int)tabela.size())
        return false;

    string nome = tabela[pos].nome;
    
    if (nome == "*" || nome == "/" || nome == ")" || nome == ";" ||
        nome == ">=" || nome == "<=" || nome == ">" || nome == "<" || nome == "==" || nome == "!=" ||
        nome == "&&" || nome == "||" || nome == "+" || nome == "-" ||
        nome == "=" || nome == "+=" || nome == "-=" || nome == ",")
        return true;

    if(nome == "++" || nome == "--"){
        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        return true;
    }

    return false;

}

