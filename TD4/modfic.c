#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

main() {
    int* projection;
    int i,fd;
    long taille_fichier;
    fd = open("titi.dat",O_RDWR,0666);
    struct stat etat_fichier;
    stat("titi.dat", &etat_fichier);
    taille_fichier = etat_fichier.st_size;
    projection = (int*) mmap(NULL,taille_fichier,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if (projection == (int*) MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    close(fd);
    for(i = 0; i < taille_fichier; i++){
        if (projection[i] == 99)
            exit(0);
        else
            projection[i]++;
    }
    munmap((void *)projection,taille_fichier);
    return 0;
}
