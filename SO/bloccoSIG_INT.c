#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
int main() {
        sigset_t newmask,oldmask;

        sigemptyset(&newmask);          // insieme vuoto
        sigaddset(&newmask, SIGINT);    // aggiunge SIGINT alla "maschera"
        // setta la nuova maschera e memorizza la vecchia
        if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0) {
                perror("errore settaggio maschera"); exit(1); }

        printf("Sono protetto!\n");
        
        sleep(3);

        // reimposta la vecchia maschera
        if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0) {
                perror("errore settaggio maschera"); exit(1); }

        printf("Non sono piu' protetto!\n");
        sleep(3);
}