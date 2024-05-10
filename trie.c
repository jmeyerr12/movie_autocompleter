#include "trie.h"

void criaArv(ApNodo *raiz) {
    *raiz = NULL;  // Inicializa a raiz da Trie como NULL.
}

ApNodo criaNodo() {
    ApNodo n = (ApNodo)malloc(sizeof(Nodo));
    if (n) {
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            n->filhos[i] = NULL;
        }
    }
    return n;
}

void insere(ApNodo *raiz, const char *palavra) {
    if (*raiz == NULL) {
        *raiz = criaNodo();
    }

    ApNodo p = *raiz;
    while (*palavra) {
        int index = *palavra - 'a';
        if (!p->filhos[index]) {
            p->filhos[index] = criaNodo();
        }
        p = p->filhos[index];
        palavra++;
    }

    p->filhos[ALPHABET_SIZE - 1] = criaNodo(); 
} 

ApNodo busca(ApNodo raiz, const char *palavra) {
    if (raiz == NULL) return NULL;  

    ApNodo p = raiz;
    while (*palavra) {
        int index = *palavra - 'a';
        if (p->filhos[index] == NULL) return NULL;  
        p = p->filhos[index]; 
        palavra++;
    }

    if (p->filhos[ALPHABET_SIZE - 1] != NULL) return p->filhos[ALPHABET_SIZE - 1]; 
    return NULL;
}
