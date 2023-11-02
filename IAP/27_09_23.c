#include <stdio.h>
#include <math.h>
int main()
{
    /*
    operazioni tra interi unsigned sono calcolate modulo 2^b, dove b è num.bit
    unsigned char x=255+1; x vale 256 perchè a destra la + è difinita solo tra interi, quindi; prima calcolo intero e poi converto in unsigned
    char ossia 1
    */
   unsigned char x=255+1;
   printf("%c \n",x);
    return 0;

    /*
    costrutto if(espressione)
                { se espressione ritorna vero allora esegue questo statement


                    se non vero non lo esegue
                }

    */
}

