/*Exemple de segment de mémoire partagé*/
/*shm_serveur.c s'attache a la partie de memoire partagee creee et utilise la chaine*/

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ 27

main() {
    char c;
    int shmid;
    key_t key;
    char *shm, *s;
    key = 5678;   //nom du segment "5678"
    if ((shmid = shmget(key, SHMSZ, IPC_CREAT|0666)) < 0) //creer le segment
    {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) //attacher le segment
    {
        perror("shmat");
        exit(1);
    }
    //mettre qqc dans la memoire pour l'autre processus
    s = shm;
    for(c = 'a'; c <= 'z'; c++)
        *s++ = c;
    *s = NULL;
    /*Enfin, attendant que l'autre processus modifie le premier caractere de notre 
    memoire en '*', indiquant qu'il a lu ce que l'on a mis*/
    while (*shm != '*')
        sleep(1);
    exit(0);
}