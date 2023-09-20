#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <semaphore.h>
// codice dei thread. Notare che e' una funzione che prende 
// un puntatore e ritorna un puntatore (a void)

#define MAX 1000000
int contatore=0; // variabile globale condivisa da tutti i thread
sem_t mutex; // semaforo mutua esclusione

void * codice_thread(void * a) {
    pthread_t tid;
    int ptid,i;

    tid  = pthread_self();      // library tid
    ptid = syscall(SYS_gettid); // tid assegnato dal SO (funziona solo in Linux)
    printf("Sono il thread %lu (%i) del processo %i\n",tid,ptid,getpid());

    for(i=0;i<MAX;i++) {

        // sezione critica basta mettere una sem_wait prima di contatore++
        // e una sem_post dopo contatore++. Poiche' mutex è inizializzato
        // a 1 queta costruzione realizza una sezione critica dando
        // accesso a un thread alla volta.

        sem_wait(&mutex); // P
        contatore++; // variabile globale condivisa ==> INTERFERENZE!!!
        sem_post(&mutex); // V

    }
    pthread_exit(NULL);
}

int main() {
    pthread_t tid[2];
    int i,err;
    // create
    sem_init(&mutex,0,1); // inizializziamo a 1

    // crea i thread (ritorna 0 quando ha successo, vedere il man!)
    // - gli attributi sono quelli di default (il secondo parametro e' NULL)
    // - codice_thread e' il nome della funzione da eseguire
    // - non vegnono passati parametri (quarto parametro e' NULL)
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

    // destroy
    sem_destroy(&mutex);
    printf("I thread hanno terminato l'esecuzione correttamente. contatore=%d\n",
        contatore);
}