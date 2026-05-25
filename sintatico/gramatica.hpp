#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <string.h>
#include <unordered_set>

#include "arvoreHandler.hpp"
#include "../lexico/tokenHandler.hpp"

using namespace std;

class Analisador {
    private:
        vector<tabelaToken> tabela;
        int pos;

    public:
        NoArvore raiz;

        Analisador(vector<tabelaToken> token)
            : tabela(token),
              pos(0),
              raiz(-1, tipoStatement::RAIZ) {}

    void imprimirErro();

    void proxPos();
    void sincronizarPanico();
    bool tipo(string token);
    bool fimDaEntrada();
          
    // declaracao
    bool declaracao(NoArvore& pai);
    bool D1(NoArvore& pai);
    bool D2(NoArvore& pai);
    bool D3(NoArvore& pai);

    // expressao / atribuicao
    bool expressao(NoArvore& pai);
    bool ATR(NoArvore& pai);
    bool ATR1(NoArvore& pai);
    bool EA(NoArvore& pai);
    bool EL(NoArvore& pai);
    bool EL1(NoArvore& pai);
    bool TL(NoArvore& pai);
    bool TL1(NoArvore& pai);
    bool ER(NoArvore& pai);
    bool ER1(NoArvore& pai);
    bool F(NoArvore& pai);
    bool T(NoArvore& pai);
    bool T1(NoArvore& pai);
    bool EA1(NoArvore& pai);
    bool P(NoArvore& pai);

    // bloco - condicao e repeticao
    bool bloco(NoArvore& pai);

    // condicao
    bool condicao(NoArvore& pai);
    bool C1(NoArvore& pai);
    bool C2(NoArvore& pai);

    // repeticao
    bool repeticao(NoArvore& pai);
    
    bool sentenca(NoArvore& pai);
    bool S1(NoArvore& pai);    
};