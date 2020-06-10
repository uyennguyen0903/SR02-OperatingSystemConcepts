#include <pthread.h> 
#include <stdio.h> 
#include <stdlib.h> 

void *mess(void *ptr);

int main()
{
    pthread_t t1, t2;
    const char *m1 = "thread 1";
    const char *m2 = "thread 2";
    int it1, it2;
    it1 = pthread_create(&t1, NULL, mess, (void *) m1);
    if (it1)
    {
        fprintf(stderr, "pthread_creat() code retour:%d\n", it1);
        exit(EXIT_FAILURE);
    }
    it2 = pthread_create(&t2, NULL, mess, (void *) m2);
    if (it2)
    {
        fprintf(stderr, "pthread_creat() code retour:%d\n", it2);
        exit(EXIT_FAILURE);
    }
    printf("pthread_creat() code retour:%d\n", it1);
    printf("pthread_creat() code retour:%d\n", it2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    exit(EXIT_SUCCESS);
}

void *mess(void *ptr)
{
    char *message;
    message = (char *) ptr;
    printf("%s\n",message);
    pthread_exit(NULL);
}