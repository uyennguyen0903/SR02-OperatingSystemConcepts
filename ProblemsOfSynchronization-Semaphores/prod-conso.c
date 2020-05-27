#include <signal.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include "sem_pv.h"

#define prod 0
#define conso 1
#define synchro 0
#define ctrl_taille 1
#define tbuf 5

int shmid, *ptr, *status;
int ptr_cons, ptr_prod;

void fin(int sig)
{
    shmctl(shmid, IPC_RMID, 0);
    if(sig != -1) 
        detruire_semaphore();
    exit(sig);
}

main()
{
    if((shmid=shmget(IPC_PRIVATE, 5*sizeof(int), IPC_CREAT|0600)) == -1)
    {
        perror("Creation du segment");
        exit(2);
    }
    if((ptr=(int *)shmat(shmid, NULL, 0)) == (int *)-1)
    {
        perror("Attachement du segment");
        fin(-1);
    }
    if (init_semaphore() < 0) fin(-1);
    if (val_sem(synchro,0) < 0) fin(-2);
    if (val_sem(ctrl_taille,tbuf) < 0) fin(-2);
    ptr_cons = 0;
    ptr_prod = 0;
    switch(fork())
    {
        case -1 :
            perror("fork");
            fin(-2);
            break;
        case 0 :
            sleep(1);
            for(int i = 0; i <= 50; i++)
            {
                P(ctrl_taille);
                printf("fils produit %d\n", i);
                if(ptr_prod >= 5) ptr_prod=0;
                ptr[(ptr_prod++)]=i;
                V(synchro);
            }
            break;
        default :
            sleep(0);
	        int i = 0;
            while(i++ < 50)
            {
                printf("pere %d\n",i);
                P(synchro);
                if(ptr_cons >= 5) ptr_cons=0;
                printf("PERE : LECTURE=%d --- VALEUR= %d\n",i ,ptr[(ptr_cons++)]);
                V(ctrl_taille);
            }
            wait(NULL); printf("\nfin\n");
            fin(-2);
    }
}