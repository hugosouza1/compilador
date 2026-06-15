#include "gramatica.hpp"

bool Analisador::expressao(NoArvore& pai){
    if( ! (ATR(pai))) return false;      
    return true;
}

bool Analisador::ATR(NoArvore& pai){
    NoArvore atrNo(-1, tipoStatement::EXPRESSAO); 
    pai.filhos.push_back(atrNo);
    NoArvore& noAtual = pai.filhos.back();

    
    // cout << tabela[pos].nome << "\n";
    
    if(!EL(noAtual))   return false;      
    if(!ATR1(noAtual)) return false;

    propagarTipo(noAtual);

    return true; 
}

bool Analisador::ATR1(NoArvore& pai){

    if (pos >= (int)tabela.size())
        return true;

    string nome = tabela[pos].nome;

    if (nome == ")" || nome == ";" || nome == ",")
        return true;

    if (nome == "=" || nome == "+=" || nome == "-=") {

        NoArvore opNo(pos, tipoStatement::TOKEN);
        pai.filhos.push_back(opNo);
        proxPos();

        if (!ATR(pai)) return false;

        NoArvore& ident = pai.filhos[0];
        NoArvore& expr = pai.filhos[2]; 

        tipoVar esq = ident.tipoToken;
        tipoVar dir = expr.tipoToken;

        if (esq == tipoVar::NONE || dir == tipoVar::NONE)
            return false;

        if (regras.resultado(Operador::ATRIB, esq, dir) == tipoVar::NONE) {
            // cout << "Erro: atribuicao invalida\n";
            return false;
        }

        pai.tipoToken = esq;
        
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
    
    if(!calcularTipo(noAtual, Operador::AND_OR))
        return false;
    
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

    propagarTipo(noAtual);

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


    if(!calcularTipo(noAtual, Operador::IGUAL_DIFERENTE))
        return false;
    
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

    if (pos >= (int)tabela.size()) return false;

    if(tabela[pos].nome == "!"){
        NoArvore fNo(-1, tipoStatement::EXPRESSAO);
        pai.filhos.push_back(fNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore opNo(pos, tipoStatement::TOKEN, tipoVar::BOOLEAN);
        noAtual.filhos.push_back(opNo);
        proxPos();
        
        if(!F(noAtual)) return false;

        if(noAtual.filhos.back().tipoToken != tipoVar::BOOLEAN)
            return false;

        noAtual.tipoToken = tipoVar::BOOLEAN;
        pai.tipoToken = tipoVar::BOOLEAN;
        return true;
    }

    if(tabela[pos].nome == "("){
        NoArvore fNo(-1, tipoStatement::EXPRESSAO);
        pai.filhos.push_back(fNo);
        NoArvore& noAtual = pai.filhos.back();

        NoArvore abreNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(abreNo);
        proxPos();
        
        if(!expressao(noAtual))
            return false;

        tipoVar t = noAtual.filhos.back().tipoToken;

        noAtual.tipoToken = t;
        pai.tipoToken = t;

        if(pos >= (int)tabela.size() || tabela[pos].nome != ")") return false;
        NoArvore fechaNo(pos, tipoStatement::TOKEN);
        noAtual.filhos.push_back(fechaNo);
        proxPos();
        return true;
    }
    
    
    if(tabela[pos].classe == classeToken::BOOLEAN){
        NoArvore opNo(pos, tipoStatement::TOKEN, tipoVar::BOOLEAN);
        pai.filhos.push_back(opNo);

        pai.tipoToken = tipoVar::BOOLEAN;

        // cout << "tipo = \n\n\n\n\n" << (int)pai.tipoToken << "\n";
        
        proxPos();
        
        return true;
    }
    

    if(tabela[pos].classe == classeToken::NUMERAIS_INT){
        NoArvore opNo(pos, tipoStatement::TOKEN, tipoVar::INT);
        pai.filhos.push_back(opNo);

        pai.tipoToken = tipoVar::INT;

        proxPos();

        if(!P(pai)) return false;
        return true;
    }

    if(tabela[pos].classe == classeToken::NUMERAIS_FLOAT){
        NoArvore opNo(pos, tipoStatement::TOKEN, tipoVar::FLOAT);
        pai.filhos.push_back(opNo);

        pai.tipoToken = tipoVar::FLOAT;
        
        proxPos();
        
        if(!P(pai))  return false;
        return true;
    }
        
    if(tabela[pos].classe == classeToken::LITERAIS){
        NoArvore opNo(pos, tipoStatement::TOKEN, tipoVar::STRING);
        pai.filhos.push_back(opNo);
        pai.tipoToken = tipoVar::STRING;
        proxPos();

        
        return true;
    }
    
    if(tabela[pos].classe == classeToken::IDENTIFICADORES){
        tipoVar tipoAtual = regras.buscarIdentificador(tabela[pos].nome)->tipoToken;
        if(tipoAtual == tipoVar::NONE) return false;

        NoArvore opNo(pos, tipoStatement::TOKEN, tipoAtual);
        pai.filhos.push_back(opNo);

        pai.tipoToken = tipoAtual;
        proxPos();
        
        if(!P(pai))  return false;
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

    if(!calcularTipo(noAtual, Operador::MULT_DIV))
        return false;
    
    return true;
}


bool Analisador::T1(NoArvore& pai){
    if (pos >= (int)tabela.size()) return true;
    
    string nome = tabela[pos].nome;

    if (nome == "||" || nome == "&&" || nome == ";" || nome == ")" || 
        nome == "=" || nome == "-=" || nome == "+=" ||
        nome == ">=" || nome == "<=" || nome == ">" || nome == "<" || nome == "==" || nome == "!=" || nome == "," || 
        nome == "+" || nome == "-")
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

    if(!calcularTipo(noAtual, Operador::SOMA_SUB))
        return false;
    
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

