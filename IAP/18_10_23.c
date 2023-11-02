/*

*/

#include<stdio.h>
#include<stdlib.h>

int main()
{
    int v[]={1,2,3,4,5,6,7,8,9};
    int * a=v;
    printf("%d\n",*a);
    a++;//sposta il puntatore di una posizione
    printf("%d\n",*a);
    printf("%d\n",*(a+1));

    return 0;
}