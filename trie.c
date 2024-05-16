#include "trie.h"

void criaArv(ApNodo *raiz) {
    *raiz = NULL;  // Inicializa a raiz da Trie como NULL.
}

ApNodo criaNodo() {
    ApNodo n = (ApNodo)malloc(sizeof(Nodo));
    if (!n) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(EXIT_FAILURE);  // Ou qualquer outro tratamento de erro apropriado
    }
    for (int i = 0; i < ALPHABET_SIZE; i++) 
        n->filhos[i] = NULL;
    return n;
}

void insere(ApNodo *raiz, const char *palavra) {
    if (!*raiz) {
        *raiz = criaNodo();
    }

    ApNodo p = *raiz;
    while (*palavra) {
        int index = indC(*palavra);
        if (index < 0 || index >= ALPHABET_SIZE) {
            fprintf(stderr, "Caractere '%c' fora do intervalo permitido\n", *palavra);
            continue;  // Pula caracteres inválidos
        }
        if (!p->filhos[index]) {
            p->filhos[index] = criaNodo();
        }
        p = p->filhos[index];
        palavra++;
    }

    if (!p->filhos[ALPHABET_SIZE - 1]) {
        p->filhos[ALPHABET_SIZE - 1] = criaNodo();
    }
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

void freeArv(ApNodo raiz) {
    if (raiz == NULL) return;
    for (int i = 0; i < ALPHABET_SIZE; i++) freeArv(raiz->filhos[i]);
    free(raiz);
}

int ehFolha(ApNodo no) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (no->filhos[i] != NULL) {
            return 0; // Não é folha
        }
    }
    return 1; // É folha
}

void printTrie(ApNodo raiz, int nivel) {
    if (ehFolha(raiz)) {
        for (int i = 0; i < nivel; i++) printf("   ");
        printf("\\0\n");
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (raiz->filhos[i] != NULL) {
            for (int j = 0; j < nivel; j++) printf("   ");
            printf("%c\n", (i == 26) ? ' ' : 'a' + i);
            printTrie(raiz->filhos[i], nivel + 1);
        }
    }
}
