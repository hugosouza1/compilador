#include <iostream>
#include <fstream>
#include <regex>

using namespace std;



int main() {
    ifstream codigoFonte("txt.txt");
    char c;
    if( ! codigoFonte.is_open()) cout << "Erro ao abrir o codigoFonte." << endl;


    while (codigoFonte.get(c)) { 
        cout << c; 
    }
    

    codigoFonte.close(); // Fecha o codigoFonte
    return 0;
}
