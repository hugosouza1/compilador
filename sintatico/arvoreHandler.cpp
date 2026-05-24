#include "arvoreHandler.hpp"

void contarNos(const NoArvore& no, int& total, int& folhas) {
    total++;
    if (no.filhos.empty()) {
        folhas++;
    }
    for (const NoArvore& filho : no.filhos)
        contarNos(filho, total, folhas);
}
