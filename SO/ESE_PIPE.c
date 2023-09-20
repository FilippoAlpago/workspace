/*
 * Soluzione di crypto per il corso di Sistemi Operativi 2020
 * Prima verifica: pipe
 *
 * NOTA: Eseguire in questo modo per evitare che parta prima che crypto 
 * abbia creato le pipe (in alternativa lanciare i due programmi su due 
 * terminali diversi)
 *
 * (sleep 1; ./soluzione) & ./crypto -i /tmp/pipeIn -o /tmp/pipeOut
 * 
 * Author: Riccardo Focardi
 *
 * Commento generale (NECESSARIO per una valutazione positiva):
 *
 * La soluzione proposta consiste in un ciclo while(1) che svolge
 * le seguenti operazioni:
 *
 * 1. Legge dalla pipe di output del programma crypto il primo carattere,
 *    che sa essere 'A' (tutte le frasi iniziano con ALBERT EISTEN). 
 *    Se la read ritorna 0 esce: questo avviene quando crypto finisce 
 *    di mandare frasi e chiude la pipe di output;
 * 2. Calcola la chiave key sottraendo da 'A' il carattere letto c.
 *    Infatti, c = 'A' - key e quindi key = 'A' - c. Poiché i char sono
 *    byte questa operazione aritmetica si puo' fare direttamente tra 
 *    variabili di tipo char;
 * 3. Invia 'A' sulla pipe di input di crypto;
 * 4. Legge il resto della frase un carattere alla volta, lo decifra 
 *    sommando key e lo invia sulla pipe di input di crypto. Quando il 
 *    carattere decifrato e' '#' esce dal ciclo e si prepara a leggere
 *    la frase successiva (torna al punto 1).
 *
 * Si noti che tutte le letture/scritture su pipe avvengono carattere per 
 * carattere. Questo ci permette di gestire la decifratura e l'invio a 
 * crypto facilmente evitando la creazione di stringhe.
 * 
 * Si noti inoltre che per uscire correttamente dal ciclo del punto 4
 * si deve testare che il carattere DECIFRATO sia '#' e si deve inoltre
 * inviare '#' sulla pipe di input di crypto. Per questa ragione verra'
 * usato un ciclo do-while che permette, appunto, di verificare la
 * condizione di uscita alla fine del blocco di codice.
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PIPEIN  "/tmp/pipeIn"
#define PIPEOUT "/tmp/pipeOut"

int main() {
    int fd0,fd1;    // descrittori per le pipe
    char c,d,key;   // variabili per lettura, scrittura e chiave 

    /*
     * Apre PIPEOUT in lettura e PIPEIN in scrittura. Se una delle
     * due operazioni di apertura fallisce stampa un messaggio di
     * errore e termina l'esecuzione
     */
    fd0 = open(PIPEOUT,O_RDONLY);
    fd1 = open(PIPEIN,O_WRONLY);
    if ( fd0<0 || fd1<0) {
        perror("Errore apertura pipe");
        exit(EXIT_FAILURE);
    }

    /*
    * Legge un carattere che verrà usato per calcolare la chiave
    * in quanto tutte le frasi cominciano per 'A'.
    * Se la read ritorna 0 significa che crypto ha chiuso la pipe
    * e il programma esce.
    */
    while( read(fd0,&c,1) ) {
        /* 
         * Calcola la chiave sottraendo ad 'A' il carattere letto.
         * Poiche' la cifratura avviene per sottrazione sappiamo che
         * c = 'A'-key da cui otteniamo key = 'A'-c.
         */
        key = 'A'-c;

        /*
         * Manda il carattere in chiaro 'A' a crypto. Attenzione: la
         * write vuole un puntatore a char quindi è necessario salvare
         * 'A' su una variabile char d e passare &d alla write.
         */
        d = 'A';            // mette 'A' nella variabile char d
        write(fd1,&d,1);    // invia 'A' sulla pipe PIPEIN

        /*
         * legge da PIPEOUT fino al carattere (decifrato) '#'. 
         * Ogni carattere letto viene decifrato al volo e scritto 
         * immediatamente su PIPEIN in modo da non dover costruire 
         * una stringa. Di fatto PIPEIN funge da buffer.
         */
        do {
            read(fd0,&c,1);  // legge il carattere cifrato c
            d = c+key;       // decifra c e salva in d la decifratura
            write(fd1,&d,1); // invia d su PIPEIN
        } while (d != '#');  // esce quando il carattere è '#'
    }
}