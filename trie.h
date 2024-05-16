#ifndef TRIE_H
#define TRIE_H

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#define ALPHABET_SIZE 27  // [a-z] e '\0' para final de palavra
#define DIGITONULO 26
#define indC(c) ((c) >= 'a' && (c) <= 'z' ? (c) - 'a' : ALPHABET_SIZE - 1) 


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
void printTrie(ApNodo raiz, int nivel);

#endif

