#include<stdlib.h>
#include<stdbool.h>
#include<stdlib.h>

struct matrix
{
    short int val_1_rows;
    short int val_1_cools;
    short int val_2_rows;
    short int val_2_cools;
} typedef Matrix;

typedef struct matrix* MatrixPosition;

struct card
{
    short int val_1;
    short int val_2;
    PointerToCard SX;
    PointerToCard DX;
    PointerToCard SX_low;
    PointerToCard DX_low;
    bool is_vertical;
    bool is_used;
    bool is_swapped;
    MatrixPosition P;
} typedef Card;

typedef struct card* PointerToCard;
struct list_cards 
{
    PointerToCard First;
    PointerToCard SpecialCards;
} typedef List_Cards;

typedef struct list_cards* ListOfCard;

//metodi
void print_game_rules();//da fare

//ciò che riguarda le tessere
PointerToCard createCard(short int x, short int y);//fatto
PointerToCard copyCard(PointerToCard C);
void swapCard(PointerToCard Card);//"giro" una tessera
void freeCard(PointerToCard C);


//creazione tessere disponibili: sempre e solo 3 tessere speciali per ogni partita
ListOfCard createListOfCard();
ListOfCard createStandardGame();//partita standard con 21 tessere
ListOfCard create_N_random_cards(int N);//tessere random
ListOfCard create_N_cards(int N);//N tessere scelte da me // SONO ARRIVATO QUI
void addCard(ListOfCard L, PointerToCard C);
void printNotUsedCard(ListOfCard L);
PointerToCard get_I_card(ListOfCard L,int i);//se troppo grande richiedo al volo e lo faccio ricorsivo


//soluzione: il campo specialCard è NULL
ListOfCard createSolution();
void addCardToSolution(ListOfCard Solution,PointerToCard CardToAdd);

int solutionScore(ListOfCard Solution);


void printSolution(ListOfCard Solution);
void freeList(ListOfCard L);//faccio univoca per Solution e listaNormale
