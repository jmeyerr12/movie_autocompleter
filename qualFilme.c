#include "trie.h"

char* padronizaString(char* entrada)
{
    const char idx[256] =    // mapeia [A-Z,0-9,tab] para [a-z,0-9,' ']
                           // e outros caracteres para '?' ('\0') 
    {
      0,   1,   2,   3,   4,   5,   6,   7,   8,  32,  10,  11,  12,  13,  14,  15,  // 000-015
     16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  // 016-031
     32,  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  42,  '\0',  '\0',  '\0',  46,  '\0',  // 032-047
     48,  49,  50,  51,  52,  53,  54,  55,  56,  57,  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  // 048-0'\0'
     '\0',  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 064-079
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  '\0',  '\0',  '\0',  '\0',  '\0',  // 080-095
     '\0',  97,  98,  99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,  // 096-111
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122,  '\0',  '\0',  '\0',  '\0', 127,  // 112-127
     '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  // 128-143
     '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  // 144-159
     '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  // 160-175
     '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  // 176-191
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 192-207
    100, 110, 111, 111, 111, 111, 111, 120,  48, 117, 117, 117, 117, 121,  '\0',  '\0',  // 208-223
     97,  97,  97,  97,  97,  97,  97,  99, 101, 101, 101, 101, 105, 105, 105, 105,  // 224-239
    111, 110, 111, 111, 111, 111, 111,  '\0',  48, 117, 117, 117, 117, 121, 112, 121   // 240-255
    }; 

    size_t tam = strlen(entrada);
    char* nova = (char*)malloc(tam + 1);  
    char* p = nova;

    while (*entrada != '\0') {
        if (*entrada == '\n') {
            entrada++;
            continue;
        }

        if (*entrada >= 0 && *entrada <= 255) {
            char converted = idx[(unsigned char)*entrada];
            if (converted != '\0') *p++ = converted;
        }
        entrada++;
    }
    *p = '\0'; 

    if (p != nova && *(p-1) == ' ') {
        *(p-1) = '\0';
    }

    return nova;
}

int main(int argc, char *argv[])
{
    FILE *arq;
    char *linha = NULL;
    char* result = NULL;
    int status;
    unsigned long tamLinha;
    ApNodo root;
    
    criaArv(&root);
    
    char espaco = '0';
    printf("O número ASCII para o espaço é: %d\n", (int)espaco);

    //muda o locale para mostrar os simbolos "certos"
    printf("locale original: %s\n", setlocale(LC_ALL, NULL));
    char* local = setlocale(LC_ALL, "pt_BR.UTF-8");
    if (local == NULL) return -1;
    printf("locale alterado para \"%s\"\n", local);

    // abre arquivo de entrada
    if( argc != 4 ){
        printf( "Erro nos argumentos da chamada\n" );
        printf( "Chamada: ./qualFilme filmes.txt < consultas.txt > saida.txt\n" );
        return 0;
    }
    arq= fopen( argv[1], "r" );
    if( arq == NULL ){
        printf( "Erro na abertura do arquivo\n" );
        return 0;
    }

    while ((status = getline(&linha, &tamLinha, arq)) != -1) {
        result = padronizaString(linha); 
        insere(&root, result);
        printf("%s\n", result);
        free(result);
    }
    
    printTrie(root,0);
    
    free(linha);
    freeArv(root);
    fclose(arq);
    return 0;
}
