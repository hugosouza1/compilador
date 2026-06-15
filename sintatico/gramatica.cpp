#include "gramatica.hpp"

void Analisador::imprimirErro() {
    
    auto imprimirLinha = [&](int i, bool destaque) {

        if(i < 0 || i >= (int)tabela.size())
            return;

        const tabelaToken& t = tabela[i];

        cout << (destaque ? " >>> " : "     ");

        cout << "[" << setw(3) << right << i << "] "
             << setw(22) << left  << toSString(t.classe)
             << " | "
             << setw(15) << left  << t.nome
             << " | linha "
             << setw(3) << right << t.linha
             << " col "
             << setw(3) << right << t.coluna;

        if(destaque)
            cout << "   <== erro";

        cout << "\n";
    };

    cout << "\n";
    cout << "==== ERRO SINTÁTICO ==========================================\n";

    if(fimDaEntrada()) {

        cout << "\n";
        cout << "Final de arquivo inesperado.\n";
        cout << "Pode estar faltando ';', '}' ou ')'.\n\n";

    } else {

        tabelaToken &tk = tabela[pos];

        cout << "\n";
        cout << "Linha " << tk.linha
             << ", coluna " << tk.coluna << "\n\n";

        cout << "Contexto:\n";
        cout << "--------------------------------------------------------------\n";

        imprimirLinha(pos - 2, false);
        imprimirLinha(pos - 1, false);
        imprimirLinha(pos,     true);
        imprimirLinha(pos + 1, false);
        imprimirLinha(pos + 2, false);

        cout << "--------------------------------------------------------------\n\n";

        cout << "Token inesperado: '" 
             << tk.nome
             << "'\n";

        cout << "Classe do token: "
             << toSString(tk.classe)
             << "\n\n";

        cout << "Sugestão: verifique a sintaxe próxima dessa posição.\n";
    }

    cout << "==============================================================\n\n";
}

void Analisador::proxPos() {
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



bool Analisador::calcularTipo(NoArvore& no, Operador op){
    no.tipoToken = regras.inferirTipoExpressao(no, op);

    return no.tipoToken != tipoVar::NONE;
}


void Analisador::propagarTipo(NoArvore& no){
    if(no.filhos.size() == 1)
        no.tipoToken = no.filhos[0].tipoToken;
}