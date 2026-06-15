#include "analisador_sintatico.hpp"

int analisadorSintatico(vector<tabelaToken>& tabela){
    Analisador ParserArvore(tabela); 

    bool sucesso = true;

    while(!ParserArvore.fimDaEntrada()){
        NoArvore subArvore(-1, tipoStatement::RAIZ);
        
        if(ParserArvore.sentenca(subArvore)){
            // merge da subarvore na raiz
            for(auto& filho : subArvore.filhos)
                ParserArvore.raiz.filhos.push_back(std::move(filho));
        } else {
            sucesso = false;
            ParserArvore.imprimirErro();

            // avança até token de sincronização (modo panico) "," e ";"
            ParserArvore.sincronizarPanico();
        }
    }

    if(sucesso){
        // ParserArvore.raiz.podar();
        imprimirArvore(ParserArvore.raiz, tabela, "", true);
        cout << "Sucesso\n";

        ParserArvore.imprimirTabelaDec();
        


        return 1;
    } else {
        cout << "Fracasso — erros encontrados\n";
        return 0;
    }
}