#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>

#define SHMSZ   27

main()
{
    char c;
    int shmid;
    char *shm, *s;
    key_t key = 5678;
    shmid = shmget(key,SHMSZ,IPC_CREAT|0666);
    if (shmid < 0)
    {
        perror("shmger");
        exit(1);
    }
    shm = shmat(shmid,NULL,0);
    if (shm == (char *) -1)
    {
        perror("shmat");
        exit(1);
    }
    for(s = shm; *s != NULL; s++)
        putchar(*s);
    putchar('\n');
    *shm = '*';
    exit(0);
}

