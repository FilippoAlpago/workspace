//puntatori
/*
    quando lancio un programma, gli viene riservato una parte di memoria
    Indirizzo=posizione esatta di dove si trova una vraibile in memeoria.
                posso sapere questo indirizzo tramite l'operatore &
                es. &x;
*/
#include <stdio.h>
#include <stdlib.h>


void inc(int* x)//sto copiando l'indirizzo
{//funzione che prende un valore e lo incrementa
    (*x)++;
}

void swap(int*x,int*y)
{
    int* app=x;
    x=y;
    y=app;
}

/*int *f(int b)
{
    int c=b+1;//siccome c è interno alla funzione, dopo esecuzione di f la memoria allocata per tale funzione viene deallocata
                // e quindi il int* di ritorno ha un indirizzo di memoria non valido
    return &c;
}*/

int main()
{
    int x=100;
    int *p_x=&x;//&x torna l'indirizzo di memoria. *p_x è una puntatore ad un intero il cui valore ora è quello di &x
    int *p_z=p_x;
    int **p_w=&p_x;//puntatore ad una  variabile di tipo int*. p_w->p_x->x
    printf("%p \n",(void*)p_x);
    printf("%p \n",(void*)p_z);
    printf("%p \n",(void*)p_w);

    //posso vedere cosa c'è dentro ad un area di memoria puntata da un puntatore: *puntatore. * operatore di dereference
    //vai a quella zona di memoria e leggi cosa c'è dentro. stiamo stampando il valore dell'area di memoria che si trova in corrispondenza di un puntatore
    printf("%d \n",*p_x);

    //operatore di dereference vale sia in lettura che in scrittura
    *p_x=101;//modifico il valore puntato dalla variabile p_x !!!modifico direttamente il valore di x, dato che x è puntata da p_x
    printf("%d \n",*p_x);
    printf("%d \n",x);
    inc(&x);
    printf("%d \n",x);
    printf("\n");
    int y=10;
    printf("%p \n",(void*)&x);
    printf("%p \n",(void*)&y);
    
    swap(&x,&y);
    printf("%d %d\n",x,y);
    printf("%p \n",(void*)&x);
    printf("%p \n",(void*)&y);
    return 0;
}