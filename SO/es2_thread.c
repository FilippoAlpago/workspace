#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/syscall.h>   /* For SYS_xxx definitions */

void * codice_thread(void * a) {
    pthread_t tid;
    int ptid;
    // ottiene un puntatore a int passato dal main
    // *num punta a num[i] dove i è il numero del thread
    int *num = (int *)a; 
    
    tid  = pthread_self();      // library tid
    ptid = syscall(SYS_gettid); // tid assegnato dal SO (funziona solo in Linux)

    printf("Sono il thread %lu (%i) del processo %i e ho letto %i\n",
        tid,ptid,getpid(),*num);
    sleep(1);
    // calcola il quadrato di num[i] puntato da num e mette il risultato
    // direttamente in num[i]. In questo modo dopo le join il main può
    // trovare il quadrato direttamente in num[i]
    *num = *num * *num;
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t tid[2];
    int i,err;
    int num[2]; // array per passaggio parametri
    if (argc < 3) {
        printf("Usage: %s num1 num2\n",argv[0]);
        exit(EXIT_FAILURE);
    }

    // crea i thread: passa i parametri ai thread copiando argv[i+i]
    // in num[i] e facendo un cast a (void *) di &num[i]. 
    // In questo modo ogni thread lavora su una variabile distinta
    // 
    for (i=0;i<2;i++) {
        num[i] = atoi(argv[i+1]); // copia argv[i+i] in num[i]
        // crea i thread passando come parametro (void *)&num[i]
        if (err=pthread_create(&tid[i],NULL,codice_thread,(void *)&num[i])) {
            printf("errore create [%i]\n",err);
            exit(EXIT_FAILURE); }
    }
    // attende i thread. 
    for (i=0;i<2;i++) {
        if (err=pthread_join(tid[i],NULL)) {
            printf("errore join [%i]\n",err);
            exit(EXIT_FAILURE); }
    }
    // il risultato è direttamente in num[i]!
    printf("I thread hanno terminato l'esecuzione correttamente: %d + %d = %d\n",
        num[0],num[1],num[0]+num[1]);
}