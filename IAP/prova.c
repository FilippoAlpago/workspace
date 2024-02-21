#include<stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void manipulate(char* s)
{
    size_t i,b;
    b=strlen(s);
    for(i=0;i<strlen(s);++i)
    {
        if(*(s+i)=='!')
        {
            int c=0;
            while (i+c+1<b&&*(s+i+c+1)=='!')
            {
                c++;
            }
            for(size_t k=i+1;k<b-c && c>0;++k)
            {
                *(s+k)=*(s+k+c);
            }
            b-=c;
            
        }
    }
    s[b]='\0';
}

int main()
{

    char c[]="!He!llo world!!!!";
    printf("ciao\n");
    manipulate(c);
    printf("%s \n",c);
    printf("ciao\n");
    //printf("%c",c);

    return 0;
}