#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>

struct sigaction act_pa, act_ch;
pid_t pid;
char i,j;
int x,y;

void handler_pa(int xx)
{
    for(int ind = 1; ind <= x; ind++)
    {
        printf("%c",i);
        fflush(stdout);
        i++;
        if (i > 'z') {exit(0);}
    }
    x++;
    kill(pid,SIGUSR1);
}


void handler_ch(int xx)
{
    for(int ind = 1; ind <= y; ind++)
    {
        printf("%c",j);
        fflush(stdout);
        j++;
        if (j > 'Z') {kill(pid,SIGUSR1);exit(0);}
    }
    y++;
    kill(getppid(),SIGUSR2);
}


main() {
    pid = fork();
    if (pid == 0)
    {
        y = 1; j = 'A';
        act_ch.sa_handler = handler_ch;
        sigaction(SIGUSR1,&act_ch,NULL);
        while (1);
    } else
    {
        x = 1; i = 'a';
        act_pa.sa_handler = handler_pa;
        sigaction(SIGUSR2,&act_pa,NULL);
        kill(getpid(),SIGUSR2);
        while (1);
    }
}


