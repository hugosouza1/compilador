#include "leitorArquivo.h"

leitorArquivo::leitorArquivo(const std::string& nomeArquivo): linha(1), coluna(0), colunaPivo(0), arquivo(nomeArquivo) {}

bool leitorArquivo::lerChar(char &c) {
    if (arquivo.get(c)) {
        if (c == '\n') {
            coluna = 0;
            linha++;
        } else {
            coluna++;
        }
        return true;
    }
    return false; // EOF
}

bool leitorArquivo::peekChar(char &c) {
    int val = arquivo.peek();
    if (val == EOF) return false;
    c = val;
    return true;
}

int leitorArquivo::getLinha() const { return linha; }
int leitorArquivo::getColuna() const { return coluna; }
int leitorArquivo::getColunaPivo() const { return colunaPivo; }

void leitorArquivo::setColunaPivo(int num) { colunaPivo = num; }
