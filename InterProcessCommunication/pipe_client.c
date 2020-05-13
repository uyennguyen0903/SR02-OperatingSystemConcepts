/*Exemple : communication client-serveur via un pipe nommé*/

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <fcntl.h>

#define PIPE "fifo"

int main() {
    int fd;
    char writebuf[20] = "Hello";
    fd = open(PIPE, O_WRONLY, 0); // Ouvrir le pipe
    write(fd, writebuf, sizeof(writebuf));
    exit(0);
}