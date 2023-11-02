/*

*/
#include<stdio.h>
#include<stdlib.h>

int main()
{
    int* nuovo=(int*) malloc(4*sizeof(int));
    

    free(nuovo);
    return 0;
}