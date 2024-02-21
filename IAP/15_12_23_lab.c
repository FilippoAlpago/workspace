#include<stdlib.h>
#include<stdio.h>

//RICORSIONE

size_t strlen_rec(char* s)
{
    if(s==NULL)
    {
        return 0;
    }
    else
    {
        return 1+strlen_rec(s+1);
    }
}

size_t fib_i(unsigned int N)
{
    int N_1=1,N_2=0,n=0;
    unsigned int val=N_2+N_1;
    while (n!=N)
    {
        val=N_2+N_1;
        N_2=N_1;
        N_1=val;
        n++;
    }
    return val;
    
}

void swap(char* a,char* b)
{
    char t=*a;
    *a=*b;
    *b=t;
}

void strrev_recursive(char* s,size_t i)
{
    if(i==strlen(s)/2)
    {
        return;
    }
    else
    {
        swap(s+i,s+strlen(s)-i-1);
        strrev_recursive(s,i+1);
    }
}


int main(int argc, char* argv[])
{


    return 0;
}