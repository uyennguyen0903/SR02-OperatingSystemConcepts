
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

struct sigaction sigact_pere, sigact_fils1, sigact_fils2;
pid_t lespid[3];
int cnt_pere, cnt_fils1, cnt_fils2;

void pere_handler() {
    cnt_pere++;
    printf("\n PERE %d : signal %d recu \n", getpid(),cnt_pere);
    if (cnt_pere == 3) {
        printf("\n PERE : fin du pere , trois signals sont deja recu \n ");
        exit(2);
    }
}

void fonction_pere() {
    sigact_pere.sa_handler = &pere_handler;
    sigaction(SIGINT, &sigact_pere, NULL);
    while(1) pause();
}

void cases_afficher(int x, int y) {
    switch(y){
      case 0 :
        printf("\n FILS No %d ID %d ENVOIE UN SIGNAL AU PERE\n", x,getpid());
        kill(lespid[0], SIGINT);
        break;
      case 1 :
        printf("\n FILS No %d ID %d ENVOIE UN SIGNAL AU FILS 1\n", x, getpid());
        kill(lespid[1], SIGINT);
        break;
      case 2 :
        printf("\n FILS No %d ID %d ENVOIE UN SIGNAL AU FILS 2\n", x, getpid());
        kill(lespid[2], SIGINT);
        break;
      case 3 :
        printf("\n FILS No %d ID %d ENVOIE UN SIGNAL A TOUT LE MONDE\n", x, getpid());
        kill(lespid[0], SIGINT);
        kill(lespid[1], SIGINT);
        kill(lespid[2], SIGINT);
        break;
    }
}

void fils1_handler() {
    cnt_fils1++;
    printf("\n FILS No 1 ID %d : signal %d recu \n",getpid(), cnt_fils1);
    //rectvert(2);
    if  (cnt_fils1 == 3)
    {
        printf("\n FILS 1 : fin du fils 1, trois signaux sont deja recu\n");
        exit(1);
    }
}

void fonction_fils1() {
    int i = 0;
    initrec();
    sigact_fils1.sa_handler = &fils1_handler;
    sigaction(SIGINT, &sigact_fils1, NULL);
    while(i != -1) 	{
        i = attendreclic();
        cases_afficher(1,i);
    }
    printf("\n FILS 1 :fin du fils 1 apres clic sur FIN 1\n");
}

void fils2_handler() {
    cnt_fils2++;
    printf("\n FILS No 2 ID %d : signal %d recu \n",getpid(), cnt_fils2);
    //rectvert(2);
    if  (cnt_fils2 == 3)
    {
        printf("\n FILS 2 : fin du fils 2, trois signaux sont deja recu\n");
        exit(1);
    }
}

void fonction_fils2() {
    int j = 0;
    initrec();
    sigact_fils2.sa_handler = &fils2_handler;
    sigaction(SIGINT, &sigact_fils2, NULL);
    while(j != -1) 	{
        j = attendreclic();
        cases_afficher(2,j);
    }
    printf("\n FILS 2 :fin du fils 2 apres clic sur FIN 2\n");
}

main() {
    int n, m;
    n = fork();
    switch(n) {
        case -1 :
            printf("\n erreur dans fork\n");
            break;
        case 0 :
            lespid[0] = getppid();
            m = fork();
            switch(m) {
                case -1 :
                    printf("\n erreur dans fork\n");
                    break;
                case 0 :
                    lespid[1] = getppid();
                    lespid[2] = getpid();
                    fonction_fils2();
                    break;
                default :
                    lespid[1] = getpid();
                    lespid[2] = m;
                    fonction_fils1();
            }
            break;
        default :
            lespid[0] = getpid();
            lespid[1] = n;
            fonction_pere();
    }
}
