#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int* isPrime;
int N;

void fonction_calcul(int debut, int fin)
{
    int i;
    int j;
    for(i = debut; i<= sqrt(fin); i++)
    {
        if (isPrime[i])
        {
            for(j = i * i; j <= fin; j += i)
            {
                isPrime[j] = 0;
            }
        }
    }
}

void displayPrimeNumbers(int N)
{
    int cnt = 0;
    for(int i = 2; i <= N; i++)
    {
        if (isPrime[i] == 1) cnt++;
    }
    printf("Il y a %d nombres premiers <= %d : \n", cnt, N);
}

int main()
{
    printf("Entrez la valeur N:\n");
    scanf("%d", &N);
    
    struct timeval stop, start;
    gettimeofday(&start, NULL);
 
    isPrime = (int *)(malloc(sizeof(int) * (N+1)));
    int i;
    for(i = 2; i <= N; i++) isPrime[i] = 1;
    isPrime[0] = 0; isPrime[1] = 0;
    
    fonction_calcul(2,N);
    displayPrimeNumbers(N);
    
    gettimeofday(&stop, NULL);
    double secs;
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("Temps d'execution : %.6f secondes\n", secs);
    
    return 0;
}