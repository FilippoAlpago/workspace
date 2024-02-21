#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
//scrivere una funzione che implementa una strategia che mi dice quanto comprare e quando vendere bitcoin
/*
    Andremo ad utilizzare gli array
    array=serve per memorizzare una sequenza di dati dello stesso tipo (Omogenei). hanno una dimensione fissa quando li creo
          Non è possibile aumentare o diminuire la sua grandezza. L'array è Contiguo, elementi posizionati in sequenza in memoria
          tipo Nome_variabile[dimensione_array]; se non lo inizializzo, all'interno è pieno di valori sporchi(casuali)
          es. float x[7]; mi crea una array di float di dimensione 7
          Per accedere Nome_array[posizione_a_cui_voglio_accedere-1];  se faccio x[100] vado fuori dall'array e ritornerà una parte di memoria non valida
          Si può inizializzare con x[]={1,2,3,4,5,6,7} -> si può fare a meno di mettere la dimensione in questo modo
          oppure x[7]={1} -> array di dimensione 7 con il primo elemento di valore 1 ed i restanti di valore 0
          N.B. non è possibile fare x=y ossia la copia dell'array, a meno che non la implemento io o la tiro dentro io con delle librerie
    Il linguaggio C tratta gli array come puntatori:
        è consentito
            float A[7];  
            float* B=A;//casting implicito, B puntarore di tipo Float che punta alla prima cella di meomoria dell'array A
*/
int main()
{
    float A[]={1,2,3,5,9,10};
    int G[5]={1,2,3};
    printf("%d %d\n",G[3],G[4]);
    float* B=A;
    printf("%f\n",A[0]);
    printf("%f\n",*B);
    *B=66;//vale la stessa regola dei puntatori, se ciò a cui punta è puntato anche da un altro  valore, allora anche quello punterà al nuovo valore
    printf("%f\n",A[0]);
    printf("%f\n",++(*B));

    float *C=&A[2];//C puntatore che punta al 3° elemento di A
    printf("%f\n",*C);
    *(C++);//sposta il puntatore di una posizione, quindi ora C punta al 4° elemento di A
    printf("%f\n",*C);
    float *D=&A[2];//puntatore che punta alla 3° cella dell'array
    printf("%f\n",D[0]);//stampo la 1° cella a cui punta il puntaore, in questo caso la 3° di A
    printf("%f\n",D[1]);//stampo la 2° cella a cui punta il puntaore, in questo caso la 4° di A
    printf("%f\n",D[2]);//stampo la 3° cella a cui punta il puntaore, in questo caso la 5° di A
    return 0;
}