#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <pthread.h>

int N, L, nthreads;
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
            if (k == 2) k++; else k += 2;
        } while (isPrime[(k-3)/2] == 0 && k <= sqrt(N));
        pthread_mutex_unlock(&var_mutex);
        if (isPrime[(h-3)/2])
        {
            int j;
            if (h == 2) continue;
            for(j = h * h; j <= N; j += 2*h)
            {
                isPrime[(j-3)/2] = 0;
            }   
        }
    }
}

void displayPrimeNumbers(int N)
{
    int cnt = 1;
    for(int j = 0; j <= L; j++)
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
    
    L = (N-3)/2;
    isPrime = (int *)(malloc(sizeof(int) * (L+1)));
    int i;
    for(i = 0; i <= L; i++) isPrime[i] = 1;

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