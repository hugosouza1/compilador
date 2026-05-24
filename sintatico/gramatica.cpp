#include "gramatica.hpp"

void Analisador::imprimirErro() {
    
    auto imprimirLinha = [&](int i, bool destaque) {
        if(i < 0 || i >= (int)tabela.size()) return;
        const tabelaToken& t = tabela[i];
        cout << (destaque ? " >>> " : "     ");
        cout << "[" << setw(3) << i << "] "
             << setw(18) << left << toSString(t.classe)
             << " | " << setw(15) << left << t.nome
             << " | linha " << setw(3) << t.linha
             << " col " << setw(3) << t.coluna;
        if(destaque) cout << "  <== erro por aqui";
        cout << "\n";
    };

    cout << "\n==== ERRO SINTÁTICO ===================================================\n";
    imprimirLinha(pos - 3, false);
    imprimirLinha(pos - 2, false);
    imprimirLinha(pos - 1, false);
    cout << "      ---------------------------------------------------------------\n";
    imprimirLinha(pos,     true);
    cout << "      ---------------------------------------------------------------\n";
    imprimirLinha(pos + 1, false);
    imprimirLinha(pos + 2, false);
    imprimirLinha(pos + 3, false);
    cout << "=======================================================================\n\n";
}

void Analisador::proxPos() {
    // int total = 0, folhas = 0;
    // contarNos(raiz, total, folhas);
    // cout << "Total: " << total << " | Folhas: " << folhas << " | Intermediários: " << total - folhas << "\n";

    // cout << "poooooooooooooooooooooooooos:" << tabela[pos].nome << "\n";

    pos++;
}

bool Analisador::fimDaEntrada() { 
    return pos >= (int)tabela.size(); 
}

bool Analisador::tipo(string token){

    static const unordered_set<string> reservadas = {
        "int", "bool", "string", "float"
    };

    return reservadas.count(token) > 0;
}

void Analisador::sincronizarPanico(){
    while(!fimDaEntrada()){
        string nome = tabela[pos].nome;
        proxPos();
        
        if(nome == ";" || nome == "}"){
            break;
        }
        
    }
}