#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <sys/stat.h>



int main(){
  int i,fd;
  i=0;
  fd=open("titi.dat", O_RDONLY,0666);
  struct stat etat_fichier;
  stat("titi.dat", &etat_fichier);
  long taille_fichier = etat_fichier.st_size;
  int* tab1 = (int*)mmap(NULL, taille_fichier,PROT_READ, MAP_PRIVATE,fd,0);
  if(tab1 == (int*)MAP_FAILED){
    perror("mmap");
    exit(0);
  }
  close(fd);
  while(1){
    scanf("%d",&i);
    if(i == 99) break;
    for(int k=0; k<10; k++)
      printf("%d\n",tab1[k]);
  }

  munmap((void*) tab1, taille_fichier);
  return 0;
}
