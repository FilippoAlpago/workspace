#include<stdio.h>
#include<stdlib.h>
/*

*/
int max(int* a,int rows,int cools)//funzione che accetta un puntatore ad un intero
{
    int max=*a;

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cools;j++)
        {
            if(max<a[i*cools +j])//a[i*cools +j], perchè accedo alla memoria in modo lineare; a[1,1] diventa a[3*1 +1], a[2,0] diventa a[3*2 +0]
            {
                max=a[i*cools +j];
            }
        }
    }

    return max;
}
int main(int argc,char* argv[])
{
    int M[][3]={{30,18,28},{30,19,29},{30,20,27}};

    int*x=&(M[0][0]);//puntatore al primo elemento della mia matrice
    printf("%d\n",x[0]);
    printf("%d\n",x[5]);
    printf("%d\n",x[6]);
    printf("%d\n",x[8]);
    max(&(M[0][0]),3,3);//li passo un puntatore ad un intero, che è un puntatore ad una matrice
    int **a;//se in questo modo vuol dire, il primo * a dx, dereferenzia a, che mi  torna un puntatore(* a sx), che punta ad una cella di un int
            //è un pointer ad un pointer
            //sono MOLTO Utili quando devo memorizzare matrici di grandi dimensioni
            //int**, varaibile che punta ad un array di puntatori ad int.-> int*, puntatore ad int.-> int (->=punta)
            //!!! per liberalo, devo andare a liberare(free) prima tutti i puntatori a cui punti, e poi la variabile
    free(x);
    return 0;
}

//con la malloc creo un vettore nello heap, ed è valido fino a quando non faccio una free
//con v[x], creo nello stack ed hanno vinto solo all'interno dello scoop ini cui sono stati dichiarati