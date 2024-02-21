#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*
    Dynamic vectors, array che possono cambiare la loro dimensione
    In c avviene con realloc, gli elementi precedenti vengono copiati e succesivamente devo aggiungere io il nuovo elemento
    Malloc e realloc sono molto onerose, perchè sono chiamate a sistema, che deve trovare un zona di memoria sufficentemente grande
    Soluzioni
    1) alloco uno spazio sufficentemente grande, quando mi serve di più chiamo realloc
    2)soluzione migliore, realloc del doppio dello spazio dell'array, quando esaurisco, realloc del doppio dello spazio dell vextor corrente
        ogni volta che esaurisco. Andando più in la chiamarò meno realloc visto che lo spazio allocato cresce di molto
        Ho 3 informazioni da mantenere
        1. puntatore alla testa del vettore
        2. dimensione degli elementi del vettore
        3. capacity effetiva del vettore, quanta memoria ho allocato

*/
#define lato (8);//direttiva del pre-processore, definisce una macro-> ogni volta che utilizzi lato, sostituiscilo con quello che sta dentro ()
                //NON è una varaibile, ma serve solo come "rimpiazzo"

//meglio utilizzare una variabile globale, che è appunto una VARIABILE
const int Lato=8;

typedef int Vdata;
struct vector
{
    size_t size;
    size_t capacity;
    Vdata* data;
};

typedef struct vector vector_t;

vector_t* v_create()
{
    vector_t* nuovo=(vector_t*) malloc(sizeof(vector_t));
    nuovo->size=0;
    nuovo->capacity=16;
    nuovo->data=(Vdata*) malloc(nuovo->capacity*sizeof(Vdata));
    return nuovo;
}

void v_free(vector_t* v)
{
    free(v->data);//libero memoria del vettore
    free(v);//poi il puntatore
}

void v_print(vector_t* v)
{
    for(size_t i=0;i<v->size;i++)
    {
        printf("%d ",v->data[i]);
    }
    printf("\n");
}


void v_extends(vector_t* v)
{
    if(v->size>=v->capacity)
    {
        v->data=(Vdata*) realloc(v->data,sizeof(Vdata)*v->capacity*2);
        if(!v->data)
        {
            printf("error in realloc\n");
            exit(EXIT_FAILURE);
        }
        v->capacity*=2;
    }
}
void push_back(vector_t* v,Vdata x)
{
    v_extends(v);
    v->data[v->size]=x;
    v->size++;
}

void v_push_front(vector_t* v, Vdata x)
{
    v_extends(v);
    for(size_t i=v->size;i>=1;i--)
    {
        v->data[i]=v->data[i-1];
    }
    v->data[0]=x;
    v->size++;

}

bool v_binary_search(const Vdata* v, size_t v_size, Vdata x)//CONST è una  keyword in cui dichiaro che la variabile non può essere modificata
{
/*
    Const di un PUNTATORE vuol dire che PUNTA ad un qualcosa di costante,il contenuto di un punatore non può cambiare, ma il puntore si
    Puntatori costanti: type* const pointer=.....; il puntarore non può cambiare indirizzo di memoria, ma posso modificare il suo contenuto

*/
    if(v_size==0)
    {
        return false;
    }
    else
    {
        size_t mid=v_size/2;

        if(v[mid]==x)
        {
            return true;
        }
        else
        {
            if(v[mid]>x)
            {//vado a sx
                return v_binary_search(v,mid,x);
            }
            else
            {//vado a dx
                return v_binary_search(v+mid+1,v_size-(mid+1),x);
            }
        }
    }
}




//assumo che v sia già ordinato in modo crescente
bool v_search(vector_t* v, Vdata x)
{//sfruttiamo il fatto che è ordinato-> ricerca binaria
    

}


struct card {
int value; // 1,2,3, ...
int suit; // hearts, diamonds, ...
};

struct player {
struct card cards[5];
};

struct game {
struct player *players;
int num_players;
};

int fun_A(struct game *G) {
    int i,j;
    for (i=0; i<G->num_players; i++) {
      int color = 1;
    for (j=1; j<5; j++){
    color = color && G->players[i].cards[j].suit==G->players[i].cards[0].suit;
    }
    if (color){
        return 1;

    }

    }
    return 0;
}

int main(int argc,char* argv[])
{
    //leggere da tastierea
    int a;
    scanf("%d",&a);//%d che tipo di dato andrò a leggere, dopo mi serve un puntatore ad un tipo che corrisponde al tipo che ho letto,&a;
    vector_t* prova=v_create();
    prova->data[0];
    return 0;
}