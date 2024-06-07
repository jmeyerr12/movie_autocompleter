#include "trie.h"

void listarPrefixo(ApNodo root, char *prefixo, FILE *saida) {
    ApNodo p = root;
    for (int i = 0; prefixo[i] != '\0' && p != NULL; i++) {
        int index = indC(prefixo[i]);
        if (index == -1) return; // Ignora se houver caractere não reconhecido
        p = p->filhos[index];
    }

    if (p != NULL) {
        imprimeTrieArquivo(p, prefixo, saida);
    }
}

void listarMaisLongoPrefixo(ApNodo root, char *consulta, FILE *saida) {
    ApNodo p = root;
    int lastValidIndex = -1;
    int i;
    for (i = 0; consulta[i] != '\0' && p != NULL; i++) {
        if (p->filhos[indC('\0')] != NULL) {
            lastValidIndex = i;
        }
        int index = indC(consulta[i]);
        if (index == -1) break;
        p = p->filhos[index];
    }

    if (lastValidIndex != -1) {
        consulta[lastValidIndex + 1] = '\0';
        fprintf(saida, "%s\n", consulta);
    }
}

void buscaCuringa(ApNodo node, const char *padrao, int pos, char *prefixo, FILE *saida) {
    if (node == NULL) return;

    if (padrao[pos] == '\0') {
        if (node->filhos[indC('\0')] != NULL) {
            fprintf(saida, "%s\n", prefixo);
        }
        return;
    }

    if (padrao[pos] == '.') {
        for (int i = 0; i <= ALPHABET_SIZE; i++) {
            if (node->filhos[i] != NULL) {
                char next[1000];
                sprintf(next, "%s%c", prefixo, indToChar(i));
                buscaCuringa(node->filhos[i], padrao, pos + 1, next, saida);
            }
        }
    } else if (padrao[pos] == '*') {
        buscaCuringa(node, padrao, pos + 1, prefixo, saida);
        for (int i = 0; i <= ALPHABET_SIZE; i++) {
            if (node->filhos[i] != NULL) {
                char next[1000];
                sprintf(next, "%s%c", prefixo, indToChar(i));
                buscaCuringa(node->filhos[i], padrao, pos, next, saida);
            }
        }
    } else {
        int ind = indC(padrao[pos]);
        if (ind != -1 && node->filhos[ind] != NULL) {
            char next[1000];
            sprintf(next, "%s%c", prefixo, padrao[pos]);
            buscaCuringa(node->filhos[ind], padrao, pos + 1, next, saida);
        }
    }
}

void listarComCuringa(ApNodo root, const char *padrao, FILE *saida) {
    char prefixo[1000] = "";
    buscaCuringa(root, padrao, 0, prefixo, saida);
}

char* padronizaString(char* entrada) {
    size_t tam = strlen(entrada);
    char* nova = (char*)malloc(tam + 1); // Alocando memória com base no tamanho da entrada.
    char* p = nova;

    while (*entrada != '\0') {
        if (*entrada >= 'A' && *entrada <= 'Z') {
            *p++ = *entrada + ('a' - 'A');
        } else if ((*entrada >= 'a' && *entrada <= 'z') || 
                   (*entrada >= '0' && *entrada <= '9') || 
                   (*entrada == ' ') || (*entrada == '.') || (*entrada == '*')) {
            *p++ = *entrada;
        } else if (*entrada != '\n') {
            *p++ = '?';
        }
        entrada++;
    }
    *p = '\0'; // Terminando a nova string.

    return nova;
}

int main(int argc, char *argv[]) {
    FILE *filmes;
    char *linha = NULL;
    char *result = NULL;
    int status;
    unsigned long tamLinha;
    ApNodo root;

    criaArv(&root);

    // abre arquivo de entrada
    if (argc != 2) {
        printf("Erro nos argumentos da chamada\n");
        printf("Chamada: ./qualFilme filmes.txt < consultas.txt > saida.txt\n");
        return 0;
    }
    
    filmes = fopen(argv[1], "r");

    if (filmes == NULL) {
        printf("Erro na abertura do arquivo de filmes\n");
        return 0;
    }

    // Processa o arquivo de filmes
    while ((status = getline(&linha, &tamLinha, filmes)) != -1) {
        result = padronizaString(linha); 
        insere(&root, result);
        free(result);
    }

    fclose(filmes);
    free(linha);
    linha = NULL;

    // Processa as consultas a partir da entrada padrão
    while ((status = getline(&linha, &tamLinha, stdin)) != -1) {
        result = padronizaString(linha);
        printf("%s", linha);
        char *argument = result + 2;
        if (result[0] == 'p') { // Prefixo
            listarPrefixo(root, argument, stdout);
        } else if (result[0] == 'l') { // Mais longo prefixo
            listarMaisLongoPrefixo(root, argument, stdout);
        } else if (result[0] == 'c') { // Curinga
            listarComCuringa(root, argument, stdout);
        }
        free(result);
    }
    
    free(linha);
    freeArv(root);

    return 0;
}