#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 256

int str_to_long(const char * str, long long * num) {
    char *eptr;
    *num = strtoll(str, &eptr, 10);
    if (*eptr == '\0') {
        return 0;
    } else {
        fprintf(stdout, "Conversao para numero invalida.\n");
        return -1;
    }
}

int open_file(const char * filename, long long * key1, long long * key2) {
    FILE * fptr = fopen(filename, "r"); 
    
    if (fptr == NULL) { 
        fprintf(stdout, "Nao e possivel abrir o arquivo %s\n", filename); 
        return -1; 
    } 
    
    char buffer[MAX_LEN];
    long long keys[2];
    size_t i = 0;
    while (fgets(buffer, MAX_LEN - 1, fptr)) {
        buffer[strcspn(buffer, "\n")] = 0;
        if (str_to_long(buffer, &keys[i]) != 0) {
            return -1;
        }
        i++;
    }
    
    if (fptr) {
        fclose(fptr); 
    }

    *key1 = keys[0];
    *key2 = keys[1];

    return 0;       
}

long long power(long long x, unsigned long long y, long long p) {
    long long res = 1; 
    x = x % p; 
    if(x == 0) {
        return 0; 
    }

    while(y > 0) {  
        if (y & 1)  
            res = (res * x) % p;  
        y = y >> 1;
        x = (x*x) % p;  
    }
    
    return res;  
}

int read_from_input_and_encode(long long key1, long long key2) {
    char c;
    
    while(fscanf(stdin, "%c", &c) == 1) {
        // aritmetica modular
        int aux = power(c, key1, key2);
        fprintf(stdout, "%d ", aux);
    }

    return 0;
}

int read_from_input_and_decode(long long key1, long long key2) {
    long long d;
    
    while(fscanf(stdin, "%lld", &d) == 1) {
        // aritmetica modular
        int aux = power(d, key1, key2);
        fprintf(stdout, "%c", aux);
        
    }

    return 0;
}

int main(int argc, char ** argv) {
    
    if (argc < 2) {
        fprintf(stdout, "Entrada invalida. Para rodar: %s -c/-d < entrada > saida\n", argv[0]);
        return -1;
    }

    char cfilename[BUFSIZ];
    char choice;
    if (strcmp(argv[1], "-c") == 0) {
        strcpy(cfilename, "numcripto.txt");
        choice = 'c';
    } else if (strcmp(argv[1], "-d") == 0) {
        strcpy(cfilename, "numdescripto.txt");
        choice = 'd';
    } else {
        fprintf(stdout, "Opcao invalida. Para rodar: %s -c/-d < entrada > saida\n", argv[0]);
        return -1;
    }

    long long key1 = 0, key2 = 0;
    if (open_file(cfilename, &key1, &key2) != 0) {
        return -1;
    }

    if (choice == 'c')
        read_from_input_and_encode(key1, key2);

    if (choice == 'd')
        read_from_input_and_decode(key1, key2);

    return 0;
}