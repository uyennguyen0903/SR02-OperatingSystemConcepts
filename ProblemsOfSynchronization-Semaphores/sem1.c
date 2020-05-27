#include "sem_pv.h"

main()
{
    init_semaphore();
    val_sem(2,1);
    P(2);
    sleep(5);
    V(2);
    detruire_semaphore();
}

//gcc -c sem_pv.c
//ar rvs libsempv.a sem_pv.o
//gcc -o sem1 sem1.c -L. -lsempv