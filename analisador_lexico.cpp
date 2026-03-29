#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

#include "leitorArquivo.h"
#include "tokenHandler.h"

using namespace std;


int main() {
    leitorArquivo arquivo("txt.txt");

    vector<tabelaToken> tabela;
    char pivo;

    while (arquivo.lerChar(pivo)) {
        if(isspace(pivo)) continue;

        if(separador(pivo, arquivo, tabela)) continue;

        if (litarais(pivo, arquivo, tabela)) continue;
       
        if(comentarios(pivo, arquivo /*,tabela*/)) continue;

        if(operadoMatLog(pivo, arquivo, tabela)) continue;

        if(numerais(pivo, arquivo, tabela)) continue;

        if(identificador(pivo, arquivo, tabela)) continue;
        
        tokenError("CARACTER INVALIDO!", arquivo, string(1,pivo));
        
    }

    
    // sort(tabela.begin(), tabela.end(), [](const tabelaToken &a, const tabelaToken &b){
    //     return toSString(a.classe) < toSString(b.classe);
    // });


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
    return 0;
}