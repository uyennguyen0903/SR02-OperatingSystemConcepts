/*Exemple : communication client-serveur via un pipe nommé*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h>

#define PIPE "fifo"

int main() {
    int fd;
    char readbuf[20];
    mknod(PIPE, S_IFIFO|0660, 0); //Création du pipe
    fd = open(PIPE, O_RDONLY, 0); //Ouvrier le pipe
    for(;;)
    {
        if (read(fd, &readbuf, sizeof(readbuf)) < 0) //Lire du pipe
        {
            perror("Error reading pipe");
            exit(1);
        }
        printf("Received string : %s\n", readbuf);
    }
    exit(0);
}