#include <stdio.h>
#include <stdbool.h>
int main()//da qui inizia l'esecuzione
{
    printf("hello world \n");
    printf("true %d \n",true);
    printf("false %d \n",false);
    return 0;//non ci sono stati errori nell'esecuzione
}

//per compilare da shell con gcc : gcc -std=c99 -pedantic -Wall -o2 base.c -o base.exe
// N.B. non usare g++, è per il mitico c++

