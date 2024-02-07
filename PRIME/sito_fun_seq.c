#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


void printPrimes(char* tab, unsigned long n, unsigned long m){
	unsigned long counter = 0;
	printf( "Primes numbers: \n" );
	for(unsigned long i=0; i<n-m+1; i++){
		if(counter%10==0 && tab[i]=='1' && counter!=0){
			printf("%lu, ", m+i);
			counter++;
			printf("\n");
		}
		else if(tab[i]=='1'){
			printf("%lu, ", m+i);
			counter++;
		}
	}
	printf("\nLiczb pierwszych ogolem: %lu\n", counter);
}

unsigned long * find_primes(unsigned long max){
	char * prime = malloc(max + 1);
	memset(prime, '1', max + 1);
	unsigned long counter = max - 1;
	unsigned long squarter = sqrtl(max);

	for(unsigned long p=2; p<=squarter; p++){
		if(prime[p] == '1'){
			for(unsigned long i=p*p; i<=max; i+=p){
				if(prime[i] == '1'){
					prime[i] = '0';
					counter--;
				}
			}
		}	
	}

	unsigned long found = 0;
	unsigned long *only_primes = malloc(sizeof(unsigned long) * (counter+1));
	for(unsigned long i = 2; i <= max; i++){
		if(prime[i] == '1'){
			only_primes[found+1] = i;
			found++;
		}
	}
	only_primes[0] = found;
	return only_primes;
}

void mainProcessing(char* tab, unsigned long* only_primes,  unsigned long n, unsigned long m){
	for(unsigned long i=1; i<=only_primes[0]; i++)
    {
		for(unsigned long j=only_primes[i]*2; j<=n; j+=only_primes[i]){
			if(j>=m){
				tab[j-m] = '0';
			}
		}
    }
}

void allToDo(unsigned long n, unsigned long m){
	char *tab = (char*)malloc(n-m+1);
	memset(tab, '1', n-m+1);
	unsigned long * only_primes = find_primes(sqrtl(n));
	mainProcessing(tab, only_primes, n, m);
    
	//printPrimes(tab, n, m);
	free(only_primes);
	free(tab);
}

int main(int arc, char* argv[])
{
	if(arc!=3){
		return 0;
	}
	unsigned long m, n;
	m = atoll(argv[1]);
	n = atoll(argv[2]);
	
	allToDo(n,m);
	
    return 0;
}