#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */
#include <semaphore.h>
// codice dei thread. Notare che e' una funzione che prende 
// un puntatore e ritorna un puntatore (a void)

sem_t sinc; // semaforo globale di sincronizzazione

void * T1(void * j) {
    sleep(3);
    printf("Eseguito < A >\n");

    // il semforo è rosso
    sem_post(&sinc); // OK a D di T2!

    sleep(3);
    printf("Eseguito < B >\n");
}

void * T2(void * j) {
    printf("Eseguito < C >\n");

    // il semaforo è rosso
    sem_wait(&sinc); // attende A di T1

    printf("Eseguito < D >\n");
}

int main() {
    pthread_t tid[2];
    int i,err;

    sem_init(&sinc,0,0); // semaforo rosso!

    if (err=pthread_create(&tid[0],NULL,T1,NULL)) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE); }
    if (err=pthread_create(&tid[1],NULL,T2,NULL)) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE); }

    // attende i thread

    for (i=0;i<2;i++) {
        if (err=pthread_join(tid[i],NULL)) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE); }
    }

    sem_destroy(&sinc);
    printf("I thread hanno terminato l'esecuzione correttamente.\n");
}