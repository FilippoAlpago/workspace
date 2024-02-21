#include<stdlib.h>
#include<stdio.h>
#include<string.h>
//STRINGHE
//non esisotono i tipi strighe, ma i pointer a char. N.B. i char sono tipi per caratteri SINGOLI
int main()
{
    char* s1="ciao mi chiamo filippo";
    printf("%s \n",s1);
    //char c=*s1;//contiene la prima lettera della variabile s1, non tutto
    //char c=s1[2];//*(s1+2);
    char *s2="ciao";
    //char c=s2[4];//mi torna un byte 0, ma sono uscito, come è possibile? perchè vi è un carattere in più alla fine dall stringa, 
                    //il carattere terminatore. Mi serve per capire quando finisce la stringa
    printf("%s\n",s2);//in questo caso con %s mi stampa TUTTO FINO al carattere terminatore
    printf("%c\n",*s2);//stampa solo il primo carattere

    char c[4]={'c','i','a','o'};//4B di dimensione.Differenza con s2 sta che non non c'è il terminatore visto che uso un array.
    //Se invece alloco come s2 ho 4 +1 B perchè uso "" ed il compilatore aggiunge il terminatore
    char stringa[]="ciao";
    printf("%d \n",strlen(stringa));
    printf("%d \n",strlen(s2));
    int l1=strlen(s2);//contiene 4, non conta il carattere terminatore
    int l2=strlen(c);//se abbiamo sfiga va avanti all'infinito, perchè non sa quando il char termina, visto che il carattere terminatore non è presente
    char* s3="ciao";
    if(s2==s3)
    {
        printf("sono uguali\n");
        //non arriva mai a qusta printf, perchè CONFRONTA I PUNTATORI(se puntano alla stessa area di memoria), non il contenuto
    }

    if(strcmp(s1,s2))//funzione fatta apposta per confrontare il contenuto delle stringhe
    {
        printf("sono uguali\n");
    }
    /*siccome la memoria per le strighe in s1,s2,s3 sono nello STACK non è possibile allungare la loro memoria. In generale le stringhe dichia
        rate in questo modo sono costanti e non possono essere modificate.
    */
    return 0;
}