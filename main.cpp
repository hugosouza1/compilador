#include <iostream>
#include "lexico/analisador_lexico.hpp"
#include "sintatico/analisador_sintatico.hpp"

int main(int argc, char *argv[]){
    vector<tabelaToken> saidaLexico = analisadorLexico(argc, argv);
    
    analisadorSintatico(saidaLexico);
}