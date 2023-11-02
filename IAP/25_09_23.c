#include<stdio.h>
int main()
{
    float raggio=20;
    float pi=3.1415927,circonferenza=0;
    circonferenza=2.0*raggio*pi;
    printf("%f \n",circonferenza);//%f il formato di come voglio visualizzare la variabile: in qusto caso un float. dopo la , dico cosa voglio stampare
    //printf("%d \n",circonferenza);// con questo dico interpreta come intero; se passo un float non avviene un casting, ma un troncamento
    ;;;;;;//questa espressione è legale
    ;
    ;
    ;
    int b;
    int a=(b=7)+3;
    return 0;
}

/*
    Le Variabili, una zona di memoria con un identificatore,un nome, vi è memorizzata un'informazione
    Dichiarazione, sto dichiarando qualcosa di nuovo
    Main funzione principale che il programma esegue

    Statement { codice   }
    le operazioni sono definite solo tra tipi omogenei
    Assegnamento, quando do un valore ad una variabile
    Il nostro programma è una serie di statement
    Espressioni= sono una combinazione valide di costanti variabili,operatori e chiamate di funzione
        es. int a=(b=7)+3; è un espressione valida
*/