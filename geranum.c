/* 

	Aluno: Thiago Nunes Sampaio Pires
	Data: 08/12/2020

*/

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

int is_prime(long long n) {
    if (n <= 1)  return 0; 
    if (n <= 3)  return 1; 
  
    if (n % 2 == 0 || n % 3 == 0) return 0; 
  
    for (int i = 5; i * i <= n; i += 6) 
        if (n % i == 0 || n % (i + 2) == 0) 
           return 0; 
  
    return 1; 
}

int coprime(long long phi, long long num1, long long num2) {

	long long i, e;
	for(i = 2; i < phi; i++){

		if(phi%i != 0 && is_prime(i) && i != num1 && i != num2){
			e = i;
			break;
		}
	}

	return e;
}

long long gdc_extended(long long a, long long b){
	
	long long r, q, xB = 1, yB = 0, x = 0, y = 1, alpha, beta, phi;
	phi = r = a;

	while(r != 0){
		if(a >= 0) {
            q = 0;
            r = a;
            while(r >= b) {

                r -= b;
                q += 1;
            }
        }
		a = b;
		b = r;
		if(r > 0) {
			alpha = xB - q *x;
			beta = yB - q * y;

			xB = x;
			yB = y;
			x = alpha;
			y = beta;
		}
	}

	if(beta < 0)
		beta = phi + beta;

	return beta;

}

int save_file(const char * filename, long long key1, long long key2) {
    FILE * fptr = fopen(filename, "w"); 
    
    if (fptr == NULL) { 
        fprintf(stdout, "Nao e possivel criar o arquivo %s\n", filename); 
        return -1; 
    } 
    
    fprintf(fptr, "%lld\n%lld", key1, key2);
    
    if (fptr) {
        fclose(fptr); 
    }

    return 0;
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

    // verifica se os numeros sao primos
    if (!is_prime(num1)) {
        fprintf(stdout, "Entrada <primo_1> nao e primo\n");
        return -1;
    }
    
    if (!is_prime(num2)) {
        fprintf(stdout, "Entrada <primo_2> nao e primo\n");
        return -1;
    }

    // gera chaves publicas
    long long chave_publica_1, chave_publica_2, y;
    chave_publica_1 = num1 * num2;
    y = (num1 - 1) * (num2 - 1);
    chave_publica_2 = coprime(y, num1, num2);
    
    // salva chaves publicas (criptografia)
    if (save_file("numcripto.txt", chave_publica_2, chave_publica_1) != 0) {
        return -1;
    }

    // gera chave privada (usado aritmetica do GDC extended)
    long long chave_privada = gdc_extended(y, chave_publica_2);
    // long long chave_privada = (y * 2 + 1) / chave_publica_2; 

    // salva chaves privada e mod (decriptografia)
    if (save_file("numdescripto.txt", chave_privada, chave_publica_1) != 0) {
        return -1;
    }
    
    return 0;
}