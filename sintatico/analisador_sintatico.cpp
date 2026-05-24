#include "analisador_sintatico.hpp"

int analisadorSintatico(vector<tabelaToken>& tabela){

    Analisador ParserArvore(tabela);

    if(ParserArvore.sentenca(ParserArvore.raiz) && ParserArvore.fimDaEntrada()){
        std::cout << "Sucesso" << "\n";
        return 1;
    } else {
        std::cout << "fracasso" << "\n";
        return 0;
    }
}