#include <stdio.h>
#include <fcntl.h>

main() {
    int tab[10];
    int i,fd;
    fd = open("titi.dat",O_RDWR,0666);
    read (fd,tab,10*sizeof(int));
    close(fd);
    for (i=0;i<10;i++) printf("%d\n",tab[i]);
    return 0;
}
