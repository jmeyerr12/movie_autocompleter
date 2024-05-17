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

void imprimeTrie(ApNodo raiz, int nivel) {
    if (raiz == NULL) {
        return; // Adiciona segurança contra chamadas com nó nulo
    }

    if (ehFolha(raiz)) {
        for (int i = 0; i < nivel; i++) printf("   ");
        printf("\\0\n");  // Indica o final de uma palavra na Trie
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (raiz->filhos[i] != NULL) {
            for (int j = 0; j < nivel; j++) printf("   ");
            if (i < 10) {
                printf("%c\n", '0' + i); // Números primeiro
            } else if (i >= 10 && i < 36) {
                printf("%c\n", 'a' + (i - 10)); // Letras em seguida
            } else if (i == 36) {
                printf(" \n"); // Espaço no final
            }
            imprimeTrie(raiz->filhos[i], nivel + 1);
        }
    }
}

char indToChar(int index) {
    if (index >= 0 && index <= 9) return '0' + index;       // Números de 0 a 9
    if (index >= 10 && index <= 35) return 'a' + (index - 10); // Letras de a a z
    if (index == 36) return ' ';                          // Espaço
    if (index == 37) return '\0';                         // Fim de palavra
    return '?';                                           // Caso índice inválido
}


void imprimeTrieArquivo(ApNodo p, char *prefixo, FILE *saida) {
    if (p == NULL) return;
    if (p->filhos[indC('\0')] != NULL) {
        fprintf(saida, "%s\n", prefixo);
    }

    char next[1000]; // Supondo limitação razoável para títulos de filmes
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (p->filhos[i] != NULL) {
            sprintf(next, "%s%c", prefixo, indToChar(i)); // Convertendo índice para caractere
            imprimeTrieArquivo(p->filhos[i], next, saida);
        }
    }
}

