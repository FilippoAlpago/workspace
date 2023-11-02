#include <stdio.h>
//scrivere un algortimo che calcoli la radice quadrata di un numero Z con il metodo di Erone


float square_algorithm(float z){
    //inizio con una stima x0, poi calcolare xi+1=1/2(xi+z/xi). per 10 iterazioni
    //float x=2.0,app=0.0;
    /*for(int i=0;i<10;i++)
    {   
        app=0.5*(x+(z/x));
        x=app;
        //printf("%f \n", x);
    }*/

    //altra versione
    float x_new=z/2.0,X_old=z;
    
    while(x_new!=X_old)
    {
        X_old=x_new;
        x_new=0.5*(X_old+(z/X_old));
    }
    return x_new;
}
//funzione che data un intero N stampa una schacchiera NxN
void scacchiera(unsigned int N)
{
    for(int i=0;i<N;i++)
    {

        for(int j=0;j<N;j++)
        {
            if((i%2==0&&j%2==0)||(i%2!=0&&j%2!=0))
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }

}

int main()
{
    //float x=square_algorithm(250);
    //printf("%f \n", x);
    scacchiera(5);

    return 0;
}