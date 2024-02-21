#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>
struct card
{
    int val_1;
    int val_2;
    struct card* SX;
    struct card* DX;
    struct card* SX_low;
    struct card* DX_low;
    bool is_vertical;
    bool is_used;
    bool is_swapped;
} typedef Card;

typedef struct card* PointerToCard;
struct List 
{
    PointerToCard First;
    PointerToCard Last;
} typedef Solution;

typedef struct List* ListOfCard;


ListOfCard createListOfCard();//creo una soluzione

void addCardToList(ListOfCard S,PointerToCard C);//mi serve per quando ho le tessere disponibili

void swapCard(PointerToCard Card);//"giro" una tessera



// boleano Vertical mi discrimina se devo inserirla in verticale, ritornno false se mossa non è andata a buon fine-> se verticale rimetto in orizzonatale,se swappo prima verifico se va bene
bool insertSX(ListOfCard MySolution, PointerToCard CardToInsert);//inserisco a SX 

bool insertSX_low(ListOfCard MySolution, PointerToCard CardToInsert);//inserisoc a SX in basso

bool insertDX(ListOfCard MySolution, PointerToCard CardToInsert);//inserisci a DX

bool insertDX_low(ListOfCard MySolution, PointerToCard CardToInsert);//inserisic a DX in basso

int solutionScore(ListOfCard S);

void printCardList(ListOfCard S);



void freeEverithing(ListOfCard S);

void showNotUsedcard(ListOfCard L);//stampa a schermo la lista di carte ancora utilizzabili


void GenerateNCards_random(ListOfCard L,int N);//N tessere in modo random

//void GenerateNCards(ListOfCard L,int x, int y);//chiama mi dice i valori da inserrie, se non vanno bene errore

void StandardCards(ListOfCard L);


ListOfCard Game();
