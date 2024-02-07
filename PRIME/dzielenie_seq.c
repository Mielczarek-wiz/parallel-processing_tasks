#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isprime(unsigned long x)
{
    for( unsigned long y = 2; y * y <= x; y++)
    {
        if(x % y == 0)
            return 0;
    }
    return 1;
}
void mainProcessing(char* tab, unsigned long n, unsigned long m){
	for(unsigned long i = m; i <= n ; i++)
    {
        if(!isprime(i)){
			tab[i-m] = '0';
		}
    }
}

void printPrimes(char* tab, unsigned long n, unsigned long m){
	unsigned long counter = 0;
	printf("Primes numbers: \n");

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

void allToDo(unsigned long n, unsigned long m){
	char *tab=(char*)malloc(n-m+1);
	memset(tab, '1', n-m+1);
	
	mainProcessing(tab,n,m);
    
	//printPrimes(tab,n,m);
	free(tab);
}

int main(int arc, char* argv[])
{
	if(arc!=3){
		return 0;
	}
	unsigned long m,n;
	m=atoll(argv[1]);
	n=atoll(argv[2]);
	
	allToDo(n,m);
	
    return 0;
}