#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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

void sieve_of_eratosthenes(long long n, int * primes) {   
    for (long long p = 2; p * p <= n; p++) { 
        if (primes[p]) { 
            for (long long i = p * p; i <= n; i += p) 
                primes[i] = 0; 
        } 
    } 
}

int is_prime(int num, int * primes) {
    return primes[num] ? 1 : 0;
}

int common_prime(long long n, int * primes) {
    for (long long p = 2; p * p <= n; p++) { 
        if (primes[p]) { 
            if (n % p != 0) {
                return p;
            }
        } 
    } 

}

int main(int argc, char ** argv) {

    if (argc < 3) {
        fprintf(stdout, "Entrada invalida. Para rodar: %s <primo_1> <primo_2>\n", argv[0]);
        return -1;
    }

    // verifica se sao numeros e converte
    long long num1, num2;
    if (str_to_long(argv[1], &num1) != 0) {
        return -1;
    }

    if (str_to_long(argv[2], &num2) != 0) {
        return -1;
    }

    int primes[num1 * num2 + 1]; //usar tamanho como sqrt
    memset(primes, 1, sizeof(primes));
    sieve_of_eratosthenes(num1 * num2, primes);

    // verifica se os numeros sao primos
    if (!is_prime(num1, primes)) {
        fprintf(stdout, "Entrada <primo_1> nao e primo\n");
        return -1;
    }
    
    if (!is_prime(num2, primes)) {
        fprintf(stdout, "Entrada <primo_2> nao e primo\n");
        return -1;
    }

    // gera chaves publicas
    long long chave_publica_1, chave_publica_2, y;
    chave_publica_1 = num1 * num2;
    y = (num1 - 1) * (num2 - 1);
    chave_publica_2 = common_prime(y, primes);

    fprintf(stdout, "Chaves publicas mod[%lld] - pot[%lld]\n", chave_publica_1, chave_publica_2);

    // gera chaves privadas
    long long chave_privada_1, chave_privada_2;
    chave_privada_1 = chave_publica_1;
    chave_privada_2 = (y * 2 + 1) / chave_publica_2;
    
    fprintf(stdout, "Chaves privadas mod[%lld] - pot[%lld]\n", chave_privada_1, chave_privada_2);

    return 0;
}