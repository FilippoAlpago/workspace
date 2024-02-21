#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
/*

*/

bool stoc(float* M,int num_cools)
{//matrice stocastica
    float sum;
    bool is_stoc=true;
    for(int row=0;row<num_cools&& is_stoc;row++)
    {
        sum=0.0f;//0.0f, la f sta per
        for(int cool=0;cool<num_cools&& is_stoc;cool++)
        {
            if(M[row*num_cools+cool]<0.0f)
            {
                is_stoc= false;
            }
            sum+=M[row*num_cools+cool];
        }
        if(sum-1.0f!=0.0f)//non andrebbe bene sum!=1.0f, visto che ciò porta probelmi nel confronto fra float; correttamente sarebbe vedere se la differenza fra i 2 è 0.0f
        {
            is_stoc= false;
        }
    }
    return is_stoc;
}

char* drop(char* a, char* b)
{
    int a_len=sizeof(a),b_len=sizeof(b);
    char* dest=(char*) malloc(a_len*sizeof(char)+1);//+1 per aggiungere il /0
    int dest_index=0;
    for(int i=0;i<a_len;i++)
    {
        bool is_in_b=false;
        for(int j=0;j<b_len&& !is_in_b;j++)
        {
            if(a[i]==b[j])
            {
                is_in_b=true;
            }
        }

        if(!is_in_b)
        {
            dest[dest_index++]=a[i];
        }
    }
    dest[dest_index]='\0';
    dest=realloc(dest,dest_index);//!!!!!metto 'apposto' la memoria, la restringo.
    return dest;
}



int main(int argc,char*argv[])
{



    return 0;
}