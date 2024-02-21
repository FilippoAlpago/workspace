#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*
finora abbiamo usato dei tipi forniti dal linguaggio,'primitivi'. Il linguaggio permette di definirci dei nostri tipi
*/
struct carta{
    int valore;
    char seed;

};

void f(struct carta c)//crea un copia, modifico e poi muore tutto. le struct sono soggette agli stessi vincoli dei tipi primitivi
{
    c.valore++;
}
void g(struct carta* c)//in questo caso modifico ciò che passo come parametro
{
    c->valore++;
}
typedef struct nodo list_t;

struct nodo
{
    int data;
    struct nodo* next;
};

void print_list(struct nodo *n)//riceve un puntatore ad una lista
{
    while (n!=NULL)
    {
        printf("%d",(*n).data);
        n=n->next;
    }
    
}

void append(struct nodo* list, int n)//inserisco alla fine il valore n
{
    //struct nodo nuovo={n,NULL};//facendo così si modifico la lisa in input, ma poi quando termina la funzione questo blocco muore
    struct nodo *nuovo=(struct nodo*) malloc(sizeof(struct nodo));//così facendo questa nuova parte soppravive al di fuori della funzione
    nuovo->data=n;
    nuovo->next=NULL;

    while(list->next!=NULL)
    {
        list=list->next;
    }
    list->next=&nuovo;
}
void free_list(struct nodo*list)
{
    
    while(list)
    {
        struct nodo *succ=list->next;
        free(list);
        list=succ;
        
    }
}

void list_push(struct nodo** l,int v)
{//l è il mio puntatore alla lista; siccome la mia lista è una sequenza di puntatori l è un puntatore di puntatori 
    struct nodo* nuovo;//crea nuovo nodo
    nuovo->next=*l;
    *l=nuovo;
}

struct nodo* concat(struct nodo* a, struct nodo* b)
{
    if(!a&&!b)
    {
        return NULL;
    }
    if(!a)//a non è un puntatore valido
    {
        return b;
    }

    if(!b)
    {
        return a;
    }
    struct nodo* c=a;
    while(c->next!=NULL)
    {
        c=c->next;
    }
    c->next=b;
    return a;

}

list_t* reversset(list_t* l)
{
    list_t* rev=malloc(sizeof(list_t));

    list_t* revsublist=reversset(l->next);
    return l;
}

int main(int argc, char* argv[])
{
    struct carta a={3,'c'};//in memoria viene allocato lo spazio per un intero ed un char
    struct carta b;
    b=a;//copia le informazioni di a in b; SHALLOW copy. se la mia struct contiene dei puntatori, prima devo liberare la memoria del puntatore 
    //dentro a e poi posso copiare, altrimenti causo in leak di memoria.

    struct carta* d=&a;//in memoria creo un PUNTATORE e metti dentro l'indirizzo della variabile a.

    struct carta mazzo[3]={{1,'c'},{2,'c'},{3,'c'}};//creo un ARRAY di carte di lunghezza 3

    //per leggere dentro una variabile che mi sono creato, non vi è un formato specifico-> devo stampare i valori primitivi
    printf("%d",a.seed);//a. è il modo per poter accedere ai campi della variabile a.

    (*d).seed='p';//siccome d è un puntatore modifico anche il contenuto di ciò a cui punta,a
    //se voglio accedere tramite il puntatore d, NON posso usare l'operatore .
    printf("%d",(*d).seed);//prima dereferenzio con *, poi posso usare operatore .
    //N.B. d->seed è un modo per scrivere (*d).seed, solo che è più elegante
    //N.B. usare sempre le parentesi, perchè operatore punto ha priorità maggiroe rispetto all'operatore *

    struct nodo primo={1,NULL};
    struct nodo secondo={2,NULL};
    struct nodo terzo={3,NULL};

    primo.next=&secondo;
    secondo.next=&terzo;
    printf("%d",(*primo.next).data);
    printf("%d",primo.next->data);//2 modi per stampare la stessa cosa

}
