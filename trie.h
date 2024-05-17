#ifndef TRIE_H
#define TRIE_H

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define ALPHABET_SIZE 38  // [0-9], [a-z], ' ', '\0'

#define indC(c) ((c) == '\0' ? 37 : \
                 (c) >= '0' && (c) <= '9' ? (c) - '0' : \
                 (c) >= 'a' && (c) <= 'z' ? 10 + (c) - 'a' : \
                 (c) == ' ' ? 36 : -1)


typedef struct Nodo {
    struct Nodo *filhos[ALPHABET_SIZE];  // Apontadores para os filhos
} Nodo;

typedef Nodo* ApNodo;


//protótipos das funções
ApNodo criaNodo();
void freeArv(ApNodo raiz);
void criaArv(ApNodo *raiz);
void insere(ApNodo *raiz, const char *palavra);
ApNodo busca(ApNodo raiz, const char *palavra);
void escreve(ApNodo raiz);
void imprimeTrie(ApNodo raiz, int nivel);
void imprimeTrieArquivo(ApNodo p, char *prefixo, FILE *saida);

#endif

