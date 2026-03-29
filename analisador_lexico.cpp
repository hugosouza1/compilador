#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#include "leitorArquivo.h"
#include "tokenHandler.h"

using namespace std;

void imprimirTokens(vector<tabelaToken> tabela){
    cout << left
         << setw(5) << "POS"
         << setw(20) << "CLASSE"
         << setw(30) << "TOKEN"
         << setw(10) << "LINHA"
         << setw(10) << "COLUNA"
         << endl;

    cout << string(76, '-') << endl;

    int i = 1;
    for (const auto &t : tabela) {
        cout << left
        << setw(5) << ("|" + to_string(i))
        << setw(20) << ("|" + toSString(t.classe))
        << setw(30) << ("|" + t.nome)
        << setw(10) << ("|" + to_string(t.linha))
        << setw(10) << ("|" + to_string(t.coluna))
        << "|" << endl;
        i++;
    }
    
    cout << string(76, '-') << endl;

}

void imprimeErro(vector<tabelaERRO> tabelaInvalidos ){
        for (const auto &t : tabelaInvalidos) {
    cout <<
        "-------------ERRO--------------"     << "\n" <<
        "TIPO: "  << t.tipoErro   << "\n" <<
            "LINHA: "  << t.linha      << "\n" <<
        "COLUNA: " << t.coluna << "\n" <<
        "TOKEN ERRADO:{\n" << t.tokenErro << "\n}\n" <<
        "-------------------------------\n\n";
    }
}


int main(int argc, char *argv[]) {
    if(argc > 2){cout << "erro\n"; return 1;}
    leitorArquivo arquivo(argv[1]);

    vector<tabelaToken> tabela;
    vector<tabelaERRO> tabelaInvalidos;

    char pivo;

    while (arquivo.lerChar(pivo)) {

        if(isspace(pivo)) continue;

        if(separador(pivo, arquivo, tabela)) continue;

        if (litarais(pivo, arquivo, tabela, tabelaInvalidos)) continue;
       
        if(comentarios(pivo, arquivo /*,tabela*/, tabelaInvalidos)) continue;

        if(operadoMatLog(pivo, arquivo, tabela)) continue;

        if(numerais(pivo, arquivo, tabela, tabelaInvalidos)) continue;

        if(identificador(pivo, arquivo, tabela, tabelaInvalidos)) continue;
        
        erroToken(pivo, arquivo, tabelaInvalidos);
    }

    imprimirTokens(tabela);
    imprimeErro(tabelaInvalidos);

    return 0;
}

