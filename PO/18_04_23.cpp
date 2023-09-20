


#include<iostream>//tutte le include sono gestite dal pre-processore, il compilatore non sa cosa sono
//c++ è fit per la generic programming
/* tutte queste sono gestite dal pre-processore
#define Mymacro ...

#define Mymacro2(abc)(a+b+c)

#ifdef
    #else
#endif

#pragma
*/

void swap(int*a,int*b)
{
    int app=*a;
    *a=*b;
    *b=app;
}

void swap_double(double*a,double*b)
{
    double app=*a;
    *a=*b;
    *b=app;
}

#define SWAP(T)\
void swap_##T(T* a,T* b){\
    T tmp=*a;\
    *a=*b;\
    *b=app;\
}\
SWAP(int);\
SWAP(double);

int main()
{

    return 0;
}