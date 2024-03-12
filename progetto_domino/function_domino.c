#include "function_domino.h"
#include<stdlib.h>
#include<stdio.h>


MatrixPosition createMatrixposition()
{
    MatrixPosition M=(MatrixPosition)malloc(1*sizeof(Matrix));
    M->val_1_cools=-1;
    M->val_1_rows=-1;
    M->val_2_cools=-1;
    M->val_2_rows=-1;
}


PointerToCard createCard(short int x, short int y){
    
    PointerToCard newCard=(PointerToCard)malloc(1*sizeof(Card));

    newCard->val_1=x;
    newCard->val_2=y;
    newCard->DX=NULL;
    newCard->SX=NULL;
    newCard->DX_low=NULL;
    newCard->SX_low=NULL;
    newCard->is_vertical=false;
    newCard->is_used=false;
    newCard->is_swapped=false;
    newCard->P=createMatrixposition();
    return newCard;
}

//copio solo i valori x e y
PointerToCard copyCard(PointerToCard C)
{
    return createCard(C->val_1,C->val_2);
}

void swapCard(PointerToCard Card)
{
    int app=Card->val_1;
    Card->val_1=Card->val_2;
    Card->val_2=app;
    if(Card->is_swapped==true)
    {
        Card->is_swapped=false;
    }
    else
    {
        Card->is_swapped=true;
    }
    
}

int score(PointerToCard X)
{//ricorsiva che calocla punti soluzione
    if(X==NULL)
    {
        return 0;
    }
    else
    {
        return X->val_2+X->val_1+score(X->DX)+score(X->DX_low)+score(X->SX)+score(X->SX_low);
    }
}

ListOfCard createListOfCard()
{
    ListOfCard Ls=(ListOfCard)malloc(1*sizeof(List_Cards));
    Ls->First=NULL;
    Ls->SpecialCards=NULL;
    return Ls;    
}

void addCard(ListOfCard L, PointerToCard C)
{
    PointerToCard app;
    if((C->val_1<1&&C->val_2<1)||(C->val_1>6&&C->val_2>6))
    {//tessere speciali
        if(L->SpecialCards==NULL)
        {
            L->SpecialCards=C;
        }
        else
        {
            app=L->SpecialCards;
        }
    }
    else
    {
        if(L->First==NULL)
        {
            L->First=C;
        }
        else
        {
            app=L->First;
        }  
    }
    
    while (app->DX!=NULL)
    {
        app=app->DX;
    }
    app->DX=C;
    app=NULL;

}

ListOfCard createStandardGame()
{
    ListOfCard CardList=createListOfCard();
    short int Val1=1,Val2=1;
    for (int i = 0; i < 21; i++)
    {
        addCard(CardList,createCard(Val1,Val2));
        if(Val2==6)
        {
            Val1++;
            Val2=1;
        }
        else
        {
            Val2++;
        }
        
    }
    
    addCard(CardList,createCard(0,0));
    addCard(CardList,createCard(11,11));
    addCard(CardList,createCard(12,21));
}

ListOfCard create_N_random_cards(int N)
{
    ListOfCard CardList=createListOfCard();
    for(int i=0;i<N;i++)
    {
        int val1=rand()%7,val2=rand()%7;
 
        if(val1==0&&val2==0)
        {
            val1++;
            val2++;
        }
        
        addCard(CardList,createCard(val1,val2));
    }
    addCard(CardList,createCard(0,0));
    addCard(CardList,createCard(11,11));
    addCard(CardList,createCard(12,21));
}

ListOfCard create_N_cards(int N)
{
    ListOfCard CardList=createListOfCard();
    int val1,val2;
    for(int i=0;i<N;i++)
    {
        do
        {
            printf("inserisci due valori delle tessere compresi fra 1-6: ");
            scanf("val1: %d",&val1);
            scanf(" val2: %d \n",&val2);
        } while ((val1<1|val2<1||val1>6||val2>6));

        addCard(CardList,createCard(val1,val2));
    }

    addCard(CardList,createCard(0,0));
    addCard(CardList,createCard(11,11));
    addCard(CardList,createCard(12,21));
}




