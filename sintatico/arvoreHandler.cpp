#include "arvoreHandler.hpp"

void contarNos(const NoArvore& no, int& total, int& folhas) {
    total++;
    if (no.filhos.empty()) {
        folhas++;
    }
    for (const NoArvore& filho : no.filhos)
        contarNos(filho, total, folhas);
}

void NoArvore::podar() {
    // poda filhos primeiro (bottom-up)
    for(auto& filho : filhos)
        filho.podar();

    // para cada filho intermediário com um único filho, substitui pelo neto
    vector<NoArvore> novosFi;
    for(auto& filho : filhos) {
        if(filho.id == -1 && filho.filhos.size() == 1) {
            // promove o neto no lugar do filho
            novosFi.push_back(filho.filhos[0]);
        } else {
            novosFi.push_back(filho);
        }
    }
    filhos = novosFi;
}
