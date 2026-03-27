#pragma once

#include <fstream>
#include <string>

class leitorArquivo {
private:
    int linha;
    int coluna;
    int colunaPivo;
    std::ifstream arquivo;

public:
    leitorArquivo(const std::string& nomeArquivo);

    bool lerChar(char &c);

    int getLinha() const;
    int getColuna() const;
    int getColunaPivo() const;

    void setColunaPivo(int num);
};