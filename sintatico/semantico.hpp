#pragma once

#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "../lexico/tokenHandler.hpp"

using namespace std;

struct NoArvore;

enum class tipoVar {
    INT,
    FLOAT,
    STRING,
    BOOL,
    NONE,
    COUNT
};

enum class Operador {
    SOMA_SUB,
    MULT_DIV,
    MAIOR_MENOR_IGUAL, // maior, menor, mair ou ihual, menor ou igual
    IGUAL_DIFERENTE,
    AND_OR,
    ATRIB,
    COUNT
};

struct Simbolo {
    tipoVar tipoToken;
    string token;
    int linhaDec;
    int colunaDec;
};

constexpr int M = static_cast<int>(Operador::COUNT);
constexpr int N = static_cast<int>(tipoVar::COUNT);

class Semantica {
    private: 
        tipoVar tabelaTipos[M][N][N];
        vector<Simbolo> variaveis;


    public:
        Semantica(){
            for(int op = 0; op < M; op++)
                for(int i = 0; i < N; i++)
                    for(int j = 0; j < N; j++)
                        tabelaTipos[op][i][j] = tipoVar::NONE;
            
            auto SOMA_SUB = (int)Operador::SOMA_SUB;
            tabelaTipos[SOMA_SUB][(int)tipoVar::INT][(int)tipoVar::INT] = tipoVar::INT;
            tabelaTipos[SOMA_SUB][(int)tipoVar::INT][(int)tipoVar::FLOAT] = tipoVar::FLOAT;
            tabelaTipos[SOMA_SUB][(int)tipoVar::FLOAT][(int)tipoVar::INT] = tipoVar::FLOAT;
            tabelaTipos[SOMA_SUB][(int)tipoVar::FLOAT][(int)tipoVar::FLOAT] = tipoVar::FLOAT;
            tabelaTipos[SOMA_SUB][(int)tipoVar::STRING][(int)tipoVar::STRING] = tipoVar::STRING;

            auto MAIOR = (int)Operador::MAIOR_MENOR_IGUAL;
            tabelaTipos[MAIOR][(int)tipoVar::INT][(int)tipoVar::INT] = tipoVar::BOOL;
            tabelaTipos[MAIOR][(int)tipoVar::INT][(int)tipoVar::FLOAT] = tipoVar::BOOL;
            tabelaTipos[MAIOR][(int)tipoVar::FLOAT][(int)tipoVar::INT] = tipoVar::BOOL;
            tabelaTipos[MAIOR][(int)tipoVar::FLOAT][(int)tipoVar::FLOAT] = tipoVar::BOOL;

            auto AND = (int)Operador::AND_OR;
            tabelaTipos[AND][(int)tipoVar::BOOL][(int)tipoVar::BOOL] = tipoVar::BOOL;

            auto ATRIB = (int)Operador::ATRIB;
            tabelaTipos[ATRIB][(int)tipoVar::INT][(int)tipoVar::INT] = tipoVar::INT;
            tabelaTipos[ATRIB][(int)tipoVar::FLOAT][(int)tipoVar::FLOAT] = tipoVar::FLOAT;
            tabelaTipos[ATRIB][(int)tipoVar::FLOAT][(int)tipoVar::INT] = tipoVar::FLOAT;     
            
            auto IGUAL = (int)Operador::IGUAL_DIFERENTE;
            tabelaTipos[IGUAL][(int)tipoVar::INT][(int)tipoVar::INT] = tipoVar::BOOL;
            tabelaTipos[IGUAL][(int)tipoVar::FLOAT][(int)tipoVar::FLOAT] = tipoVar::BOOL;
            tabelaTipos[IGUAL][(int)tipoVar::BOOL][(int)tipoVar::BOOL] = tipoVar::BOOL;
            tabelaTipos[IGUAL][(int)tipoVar::STRING][(int)tipoVar::STRING] = tipoVar::BOOL;
        }

    tipoVar resultado(Operador op, tipoVar esq, tipoVar dir);

    bool declararIdentificador(const tabelaToken& identi, tipoVar var);
    Simbolo* buscarIdentificador(const string& nome);
    tipoVar inferirTipoExpressao(const NoArvore& no, Operador op);

    void imprimirTabela();
};

tipoVar stringPraTipoVar(string x);