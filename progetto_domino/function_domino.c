#include "function_domino.h"
#include<stdlib.h>
#include<stdio.h>

PointerToCard createCard(int x,int y){
    
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
    return newCard;
}

ListOfCard createListOfCard()
{
    
    ListOfCard L=(ListOfCard)malloc(1*sizeof(Solution));
    
    L->First=NULL;
    L->Last=NULL;
    
    return L;
}

void addCardToList(ListOfCard S,PointerToCard C)
{//mi serve  quando creo la lista di tessere disponibili
//printf("%p \n",C);
    if(S->First==NULL||S->Last==NULL)
    {//Lista vuota
        S->First=C;
        S->Last=C;  
    }
    else
    {//NON è vuota, scorro fino a quanndo non arrivo alla fine
        
        S->Last->DX=C;
        S->Last->DX->SX=S->Last;
        S->Last=C; 
    }
}

void swapCard(PointerToCard Card)
{
    int app=Card->val_1;
    Card->val_1=Card->val_2;
    Card->val_2=app;
    Card->is_swapped=true;
}



bool validMove(ListOfCard MySolution,PointerToCard C, bool Vertical, bool swapped, bool dx, bool sx, bool sx_low, bool dx_low);//metodo ausiliario per vedere se una futura mossa è possibile

bool SX(ListOfCard S, PointerToCard CardToInsert,bool Vertical);

bool SX_low(ListOfCard S, PointerToCard CardToInsert,bool Vertical);

bool DX(ListOfCard S, PointerToCard CardToInsert,bool Vertical);

bool DX_low(ListOfCard S, PointerToCard CardToInsert, bool Vertical);



bool insertSX(ListOfCard MySolution, PointerToCard CardToInsert)
{
    return SX(MySolution,CardToInsert,CardToInsert->is_vertical);
}

bool insertSX_low(ListOfCard MySolution, PointerToCard CardToInsert)
{
    return SX_low(MySolution,CardToInsert,CardToInsert->is_vertical);
}

bool insertDX(ListOfCard MySolution, PointerToCard CardToInsert)
{
    return DX(MySolution,CardToInsert,CardToInsert->is_vertical);
}

bool insertDX_low(ListOfCard MySolution, PointerToCard CardToInsert)
{
    return DX_low(MySolution,CardToInsert,CardToInsert->is_vertical);
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

int solutionScore(ListOfCard S)
{
    if(S==NULL)
    {
        return 0;
    }
    else
    {
        return score(S->First);
    }
}

void printCardList(ListOfCard S);

bool Libera_tessera(ListOfCard L, PointerToCard C)
{
    bool apposto=true;
    if(C->is_vertical==true&&(C->DX_low!=NULL||C->SX_low!=NULL))
    {//tessera verticale che ha qualcosa attacato in basso, NON va bene
        apposto=false;
    }
    else if(C->is_vertical==false&&(C->DX!=NULL&&C->SX!=NULL))
    {//NON verticale, ma è in mezzo
        apposto=false;
    }
    else
    {
        if(C==L->First)
        {
            L->First=C->DX;
            free(C);
        }
        else if(C==L->Last)
        {
            L->Last=C->SX;
            free(C);
        }
            
    }
    return apposto;
}

/*void freeCard(ListOfCard L, PointerToCard C)
{

    
        C->DX->SX=C->SX;
            C->SX->DX=C->DX;
            free(C);    
    
    
    
}*/




