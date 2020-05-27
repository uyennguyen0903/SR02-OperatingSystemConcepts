#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdlib.h>
#include <time.h>
#include <sys/shm.h>

int myrand(){
	int a;
	a = (rand() / RAND_MAX) % 80 + 20;
	return a;
}

void main()
{
    int shmid, *ptr;
    pid_t pere, fils;
    int x, y, z, w, a;
    srand(time(NULL));
    if ((shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT|0600)) == -1)
    {
        perror("echec");
        exit(1);
    }
    if ((ptr = shmat(shmid,NULL,0)) == -1)
    {
        perror("echec");
        exit(1);
    }
    *ptr = 0;
    switch(fork()) 
    {
        case 0 :
            for(int i = 0; i < 100; i++)
            {
                a = *ptr;
                x = myrand();
                usleep(x);
                a++;
                *ptr = a;
                y = myrand();
                usleep(y);
                printf("fils %d\n",*ptr);
            }
            break;
        default :
            for(int i = 0; i < 100; i++)
            {
                a = *ptr;
                z = myrand();
                usleep(z);
                a++;
                *ptr = a;
                w = myrand();
                usleep(w);
                printf("pere %d\n",*ptr);
	        }
    }
}
//gcc -o excl-mutu-none excl-mutu-none.c -L. -lsempv