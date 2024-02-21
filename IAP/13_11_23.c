/*

*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
int sovrapp(char* a,char* b)
{
    int count=0;
    for(size_t i=0;i<strlen(b)-(strlen(a)-1);i++)
    {
//scorto fino alla lunghezza di b-a -1, perchè altrimenti andrei a confrontare la stringa di a con delle stringhe finali di lunghezza minore, che sono sempre diverse
// -1 perchè altrimenti ignorerei l'ultimo carattere
        bool match=true;
        for(int j=0;j<strlen(a);j++)
        {//scorro un sottostringa della lunghezza di a
            if(a[j]==b[i+j])
            {
                match=false;
            }
        }
        if(match)
        {
            match++;
        }
    }
    return count;
}


int main(int argc,char* argv[])
{
    printf("sovrapposizioni %d \n", sovrapp("abab","ababxabababx"));
//vedere funzionamento di realloc

    return 0;
}