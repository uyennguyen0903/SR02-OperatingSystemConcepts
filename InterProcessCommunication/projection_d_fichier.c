/* Exemple de projection de fichier en memoire */
/* mmap, munmap */
/* Problem : Ecrire un programme qui projette un fichier en mémoire, ensuite il l’inverse (inverse son
contenu) et affiche son nouveau contenu. */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>

int main(int argc, char* argv[])
{
    char *projection;
    int fichier;
    struct stat etat_fichier;
    long taille_fichier;
    if (argc != 2)
    {
        printf("Syntaxe : %s fichier a inverser\n", argv[0]);
        exit(1);
    }
    fichier = open(argv[1], O_RDWR);
    stat(argv[1], &etat_fichier);
    taille_fichier = etat_fichier.st_size;
    projection = (char *) mmap(NULL, taille_fichier, PROT_READ | PROT_WRITE, MAP_SHARED, fichier, 0);
    if (projection == (char *) MAP_FAILED)
    {
        perror("mmap");
        exit(0);
    }
    close(fichier);
    for(int i = 0; i < taille_fichier/2; i++)
    {
        char tmp = projection[i];
        projection[i] = projection[taille_fichier-i-1];
        projection[taille_fichier-i-1] = tmp;
    }
    munmap((void *) projection, taille_fichier);
    return 0;
}