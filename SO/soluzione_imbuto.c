/*
 * Corso di Sistemi Operativi 2020
 * Schema soluzione seconda verifica: semafori
 *
 * Author: Riccardo Focardi
 */
#include <semaphore.h>

// dichiarazione semafori e variabili globali
sem_t mutex,entrate_imbuto;
int N,palline_uscite=0;
// inizializza semafori e variabili
// ATTENZIONE dim è la dimensione del gruppo che deve entrare
// nell'imbuto.
void inizializza_sem(int dim) {
    N=dim;
    sem_init(&mutex,0,1);
    sem_init(&entrate_imbuto,0,N);
}
 
// distruggi i semafori
void distruggi_sem() {
    sem_destroy(&mutex);
    sem_destroy(&entrate_imbuto);
}
 
// attende di entrare nell'imbuto
void entra_imbuto() {
    sem_wait(&entrate_imbuto);//faccio entrare un certo tot di pallline(50), se il semaforo diventa rosso rimangono in attesa
    //
}
 
// esce dall'imbuto
// ATTENZIONE usare una variabile intera condivisa per sapere 
// quante palline sono uscite (da proteggere con una sezione critica)!
void esci_imbuto() {
    int i=0;
    sem_wait(&mutex);//mi serve per evitare interferenze
    palline_uscite++;
    if(palline_uscite==N)//ora devo far accedere altre N palline
    {
        for(i=0;i<N;i++)//libero una alla volta le palline
        {
            sem_post(&entrate_imbuto);//sblocca la pallina
            palline_uscite--;//man mano che sblocco le palline decremento il contatore
        }
        
    }
    sem_post(&mutex);

}