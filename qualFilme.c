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

void listarPadrao(ApNodo root, char *consulta, FILE *saida) {
    ApNodo p = root;
    
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
        }
        entrada++;
    }
    *p = '\0'; // Terminando a nova string.

    return nova;
}

int main(int argc, char *argv[])
{
    FILE *filmes, *consultas, *saida;
    char *linha = NULL;
    char* result = NULL;
    int status;
    unsigned long tamLinha;
    ApNodo root;
    
    criaArv(&root);

    // abre arquivo de entrada
    if( argc != 4 ){
        printf( "Erro nos argumentos da chamada\n" );
        printf( "Chamada: ./qualFilme filmes.txt < consultas.txt > saida.txt\n" );
        return 0;
    }
    
    filmes = fopen( argv[1], "r" );
    consultas = fopen( argv[2], "r" );
    saida = fopen( argv[3], "w" );
    
    if( filmes == NULL || consultas == NULL || saida == NULL){
        printf( "Erro na abertura do arquivo\n" );
        return 0;
    }

    while ((status = getline(&linha, &tamLinha, filmes)) != -1) {
        result = padronizaString(linha); 
        insere(&root, result);
        free(result);
    }
 
    //char c[100];// = "Rocky I";
    //sprintf(c, "%c", indC('I'));
    //printf("%s\n", padronizaString(c));
    
    while ((status = getline(&linha, &tamLinha, consultas)) != -1) {
        result = padronizaString(linha); 
        fprintf(saida, "%s", linha);
        char *argument = result + 2;
        if (result[0] == 'p') { // Prefixo
            listarPrefixo(root, argument, saida);
        } else if (result[0] == 'l') { // Mais longo prefixo
            listarMaisLongoPrefixo(root, argument, saida);
        }/* else if (linha[0] == 'c') { // Curinga
            listarComCuringa(root, argument);
        }*/
        free(result);
    }
    
    
    free(linha);
    freeArv(root);
    fclose(filmes);
    fclose(consultas);
    fclose(saida);
    return 0;
}
