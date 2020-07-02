#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>

int N, nthreads;
pthread_t* threads;
pthread_mutex_t var_mutex = PTHREAD_MUTEX_INITIALIZER;;
int* isPrime;
int k;

void *sieveEratosthenes(void *numThread)
{
    while (k <= sqrt(N))
    {   
        pthread_mutex_lock(&var_mutex);
        int h = k;
        do
        {
            k++;
        } while (isPrime[k] == 0 && k <= sqrt(N));
        pthread_mutex_unlock(&var_mutex);
        if (isPrime[h] && h != 2)
        {
            int j;
            for(j = h * h; j <= N; j += 2*h)
            {
                isPrime[j] = 0;
            }   
        }
    }
}

void displayPrimeNumbers(int N)
{
    int cnt = 1;
    for(int j = 0; j <= N; j++)
    {
        
        if (isPrime[j] == 1) cnt++;
    }
    printf("Il y a %d nombres premiers <= %d : \n", cnt, N);
}

int main()
{
    printf("Entrez un nombre N: \n");
    scanf("%d", &N);

    printf("Entrez le nombre de threads:\n");
    scanf("%d", &nthreads);
    
    struct timeval stop, start;
    gettimeofday(&start, NULL);

    threads = (pthread_t *) (malloc(sizeof(pthread_t) * nthreads));
    
    isPrime = (int *)(malloc(sizeof(int) * (N+1)));
    isPrime[0] = 0; isPrime[1] = 0;
    int i;
    for(i = 2; i <= N; i++) 
        if (i % 2 == 1)
            isPrime[i] = 1;
        else 
            isPrime[i] = 0;

    k = 2;
    
    for(i = 0; i < nthreads; i++)
    {
        int tmp;
        tmp = pthread_create(&threads[i], NULL, sieveEratosthenes, (void *) i);
        if (tmp)
        {
            fprintf(stderr,"pthread_create() code retour : %d\n", tmp);
            exit(EXIT_FAILURE);
        }
    }
 
    for (i = 0; i < nthreads; i++)
    {
        pthread_join(threads[i], NULL);
    }

    displayPrimeNumbers(N);
    
    gettimeofday(&stop, NULL);
    double secs;
    secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("Temps d'execution : %.6f secondes\n", secs);
 
    return 0;
}