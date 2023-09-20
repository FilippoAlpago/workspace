#include <unistd.h>
#include<stdio.h>
int main()
{
    printf("setto sveglia di 3 secondi");
    alarm(3);
    //while(1){}
    pause();
    printf("termino!\n");
}