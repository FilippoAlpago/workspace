#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

// codice dei thread. Notare che e' una funzione che prende 
// un puntatore e ritorna un puntatore (a void)
void * codice_thread(void * a) {
    pthread_t tid;
    int ptid;
    
    tid  = pthread_self();      // library tid
    ptid = syscall(SYS_gettid); // tid assegnato dal SO (funziona solo in Linux)

    printf("Sono il thread %lu (%i) del processo %i\n",tid,ptid,getpid());
    sleep(1);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[2];
    int i,err;

    // crea i thread (ritorna 0 quando ha successo, vedere il man!)
    // - gli attributi sono quelli di default (il secondo parametro e' NULL)
    // - codice_thread e' il nome della funzione da eseguire
    // - non vegnono passati parametri (quarto parametro e' NULL)
    for (i=0;i<2;i++) {
        if (err=pthread_create(&tid[i],NULL,codice_thread,NULL)) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE); }
    }

    // distacca il primo thread
    if (err=pthread_detach(tid[0])) {
          printf("errore detach [%i]\n",err);  
    } 

    // attende i thread. Non si legge il valore di ritorno (secondo parametro NULL)
    for (i=0;i<2;i++) {
        if (err=pthread_join(tid[i],NULL)) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE); }
    }
    printf("I thread hanno terminato l'esecuzione correttamente\n");
}