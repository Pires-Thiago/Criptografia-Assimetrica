#include <stdio.h>
#include <string.h>

int main(int argc, char ** argv) {
    
    if (argc < 2) {
        fprintf(stdout, "Entrada invalida. Para rodar: %s -c/-d < entrada > saida\n", argv[0]);
        return -1;
    }

    if (strcmp(argv[1], "-c") == 0) {
        printf("encripta\n");
    } else if (strcmp(argv[1], "-d") == 0) {
        printf("decripta\n");
    } else {
        fprintf(stdout, "Opcao invalida. Para rodar: %s -c/-d < entrada > saida\n", argv[0]);
        return -1;
    }

    return 0;
}