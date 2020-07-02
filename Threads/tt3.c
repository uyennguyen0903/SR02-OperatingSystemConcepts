#include <stdio.h>
#include <math.h>
#include <pthread.h>
#include <stdbool.h>
#include <sys/time.h>

int n, nthreads, prochain_nombre;
bool *prime;
pthread_mutex_t prochain_nombre_lock = PTHREAD_MUTEX_INITIALIZER;

pthread_t *threads;

void erathostene_k(int k)
//Mettre en non premiers toutes valeurs multiples de k
{
    for (int i = k * k; i <= n; i += k)
        prime[i] = 0;
}

int *faire_erathostene(int thread)
{
    int lim = sqrt(n), nombre_a_evaluer;
    while (1)
    {
        pthread_mutex_lock(&prochain_nombre_lock);
        nombre_a_evaluer = prochain_nombre;
        do
        {
            prochain_nombre++;
        } while (prime[prochain_nombre] == 0);
        pthread_mutex_unlock(&prochain_nombre_lock);

        //fprintf(stderr, "Le thread %d s'occupe du nombre %d\n", thread, nombre_a_evaluer);
        if (nombre_a_evaluer <= lim)
        {
            if (prime[nombre_a_evaluer])
            {
                erathostene_k(nombre_a_evaluer);
            }
        }
        else
            return 0;
    }
}

int main()
{
    void *result;
    struct timeval stop, start;

    printf("Entrez la valeur n:\n");
    scanf("%d", &n);

    printf("Entrez le nombre de threads:\n");
    scanf("%d", &nthreads);

    //Début chronométrage
    gettimeofday(&start, NULL);

    prime = (bool *)malloc(sizeof(bool) * n);
    threads = (pthread_t *)malloc(sizeof(pthread_t) * nthreads);

    //Initialisation du tableau
    for (int i = 1; i <= n; i++)
        prime[i] = 1;

    prochain_nombre = 2;

    for (int i = 0; i < nthreads; i++)
    //Lancer les threads sur chaque valeur à vérifier
    {
        pthread_create(&threads[i], NULL, faire_erathostene, i);
    }

    for (int i = 0; i < nthreads; i++)
    {
        // Attendre que les threads aient toutes finies
        pthread_join(threads[i], &result);
    }

    int nb_nombres_premiers = 1;
    for (int i = 2; i <= n; i++)
        if (prime[i])
            //printf("%d\n", i); // Inutile quand grands nombres
            nb_nombres_premiers++;

    //Fin chronométrage
    gettimeofday(&stop, NULL);
    double secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
    printf("On trouve %d nombres premiers, exécuté en %.6f secondes\n", nb_nombres_premiers, secs);

    return 0;
}