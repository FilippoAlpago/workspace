#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
/*

*/
bool palindroma(char* s,int len)//verifica se una stringa è palindroma ricorsivamente
{
    if(len<=1)
    {
        return 0;
    }
    else
    {
        return s[0]==s[len-1] && palindroma(s+1,len-2);//il paramtero è un puntatore, quindi lo sposto nella chiamata ricorsiva
    }
}


bool is_prefix(char*a, char* b)
{
    while (*a && *b && *a==*b)//*a && *b verifica se dentro *a e *b non c'è il carattere terminatore
    {
        a++;
        b++;
    }
    if(*a)
    {//sono uscito prima di finire di scorrere la stringa a
        return false;
    }
    else
    {
        return true;
    }
    
}

//contare il numero di sovrapposizioni della stringa a nella stringa b, anche con sovrapposizioni
int count(char*a,char*b)
{
    if(strlen(b)<strlen(a))
    {
        return 0;
    }
    else
    {
        return is_prefix(a,b)+ count(a,b+1);
    }
}

bool subsetsum(int* v, int v_size, int t)
{
    if(v_size==0)
    {
        return false;
    }
    if(v[0]==t)
    {
        return true;
    }

    return subsetsum(v+1,v_size-1, t-v[0])|| subsetsum(v+1,v_size-1, t);
}



int main(int argc, char* argv[])
{



    return 0;
}