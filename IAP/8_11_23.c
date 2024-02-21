/*
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc,char* argv[])
{//argc è un contatore dei parametri passati al programma, mentre argv è un puntatore ai parametri passati
    // argv[0] contiene sempre il nome del programma lanciato
    char a=66;
    printf("%c \n",a);
    printf("%c \n",a-1);
    printf("%c \n",66+('A'-'a'));

    char c[]="Hello!";//le stringhe con doppi apici sono dette nullTerminated, perchà sono terminate da un carattere terminatore \0
    printf("%s \n",c);//visto che è una stringa nullTerminated questa printf viene eseguita con successo
    //printf("%d \n",strlen(c));

    char * b="World";
    printf("%s\n",b);
    c[0]='*';//c è un array che può essere modificato
    b[0]='*';//non può essere modificato
    printf("%s \n",c);
    printf("%s \n",b);

    return 0;
}