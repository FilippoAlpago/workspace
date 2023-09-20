#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

#define MAX 1000000  // numero di incrementi

int count=0; // contatore globale inizializzato a 0

void * codice_thread(void * a) {
    pthread_t tid;
    int ptid;
    int i;

    tid  = pthread_self();      // library tid
    ptid = syscall(SYS_gettid); // tid assegnato dal SO (funziona solo in Linux)

    printf("Sono il thread %lu (%i) del processo %i\n",tid,ptid,getpid());
    
    // il thread incrementa il contatore globale MAX volte
    // questo può INTERFERIRE e alcuni incrementi vengono persi!
    for (i=0;i<MAX;i++) count++;

    pthread_exit(NULL);
}

int main() {
    pthread_t tid[2];
    int i,err;

    // crea i thread (ritorna 0 quando ha successo, vedere il man!)
    for (i=0;i<2;i++) {
        if (err=pthread_create(&tid[i],NULL,codice_thread,NULL)) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE); }
    }
    // attende i thread. Non si legge il valore di ritorno (secondo parametro NULL)
    for (i=0;i<2;i++) {
        if (err=pthread_join(tid[i],NULL)) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE); }
    }
    printf("I thread hanno terminato l'esecuzione correttamente %d\n",count);
}