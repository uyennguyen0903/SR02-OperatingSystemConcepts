#include <stdio.h>       /* standard I/O routines                 */
#include <pthread.h>     /* pthread functions and data structures */

void* PrintHello(void* data)
{
    pthread_t tid = (pthread_t)data;    /* data received by thread */

    //pthread_join(tid, NULL);            /* wait for thread tid     */
    printf("Hello from new thread %u - got %u\n", pthread_self(), data);
    pthread_exit(NULL);	                /* terminate the thread    */
}

/* like any C program, program's execution begins in main */
int main(int argc, char* argv[])
{
    int        rc;         	       /* return value                  */
    pthread_t  tid, thread_id;     	       /* thread's ID (just an integer) */
            

    tid = pthread_self();

    rc = pthread_create(&thread_id, NULL, PrintHello, (void*)tid);  
    if(rc)                             /* could not create thread */
    {
        printf("\n ERROR: return code from pthread_create is %d \n", rc);
        exit(1);
    }
    pthread_join(thread_id, NULL);
    sleep(1);
    printf("\n Created new thread (%u) ... \n", thread_id);
    pthread_exit(NULL);		
}