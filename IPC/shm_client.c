/*Exemple de segment de mémoire partagé*/
/*shm_client.c cree simplement la chaine et la partie de memoire partagee*/

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
    key = 5678;   //obtenir le seg.nomme "5678", cree par le serveur
    if ((shmid = shmget(key, SHMSZ, 0666)) < 0) //localiser le segment
    {
        perror("shmget");
        exit(1);
    }
    if ((shm = shmat(shmid, NULL, 0)) == (char *) -1) //attacher le segment a l'espace de donnee
    {
        perror("shmat");
        exit(1);
    }
    //lire ce que le serveur a mis dans la memoire
    for (s = shm; *s != NULL; s++)
    {
        putchar(*s);
    }
    putchar('\n');
    /*changer le 1er caractere du segment en '*'
    indiquant que l'on a lu le segment*/
    *shm = '*';
    exit(0);
}