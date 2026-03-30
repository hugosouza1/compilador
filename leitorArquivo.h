#pragma once

#include <fstream>
#include <string>
#include <string>
#include "tokenHandler.h"

class leitorArquivo {
private:
    int linha;
    int coluna;
    int colunaPivo;
    int linhaPivo;
    std::ifstream arquivo;

public:
    leitorArquivo(const std::string& nomeArquivo);

    bool lerChar(char &c);

    int getLinha() const;
    int getColuna() const;
    int getColunaPivo() const;
    int getLinhaPivo() const;

    void setColunaPivo(int num);
    void setLinhaPivo(int num);
    bool peekChar(char &c);
};