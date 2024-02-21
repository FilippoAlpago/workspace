/*
    Ricorsione
    Sequenza di Fibonacci: FIb(N)=Fib(N-1)+ Fib(N-2) con n>2, se n=<2 allora 1
    Nella ricorsione, ad ogni passo di ricorsione alloco spazio nello stack(espando verso l'alto)
    In generale la ricorsione è più costosa del metodo iterativo
        ci sono casi in cui è veloce tanto quanto quella iterativa per 2 motivi:
            1 ottimizzazione del compilatore tale recursion
            2 Nostre ottimizzazioni
    I problemi si possono scrivere in maniera ricorsiva e convertirli in maniera iterativa e viceversa
*/
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int fib(int n)
{//nonostante sia pulito e semplice è enormemente costoso a livello di passi di iterazione
    if(n<=2)
    {
        return 1;
    }
    else
    {
        return fib(n-1)+fib(n-2);
    }
}

//somma degli elementi  di un vettore in maniera ricorsiva
int recursiveVectorSum(int *V, int V_size)
{
    if(V_size==0)
    {
        return 0;
    }
    else
    {
        return recursiveVectorSum(V,V_size-1)+V[V_size-1];
    }
}

//dire se tutti gli elementi di un vettore sono pari
//ritorno v[size-1]%2==0 && pari(v,v_size-1)

//ordinare in maniera crescente un vettore di interi
void sort(int* v, int v_size)
{
    if(v_size==1)
    {
        return;
    }
    else
    {
        
        for(int i=0;i<v_size-1;i++)
        {
            
            if(v[i]>v[i+1])
            {//non entra qui dentro
                //printf("ciao \n");
                int app=v[i];
                //printf("%d",app);
                v[i]=v[i+1];
                v[i+1]=app;
            }
        }
        sort(v,v_size-1);   
    }  
}


int main(int argc, char* argv[])
{
    int A[]={1,2,3,4,5,6};
    printf("%d \n",recursiveVectorSum(A,6));

    printf("%d \n",fib(7));
    int B[]={5,6,0,2};
    sort(B,4);
    for(int i=0;i<4;i++)
    {
        printf("%d ",B[i]);
    }

    return 0;
}

