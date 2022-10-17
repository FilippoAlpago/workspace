#include"player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
struct mossa
{
    Player::piece Campo_gioco [8][8];//campo da gioco di dama
    mossa* next=nullptr;//mossa succesiva
};

struct Player::Impl
{

    mossa* history;//history tiene traccia di tutte le mosse
    int Player_Number;
    player_exception exc;
    int contaMosse=0;//mi serve poi per accedere alla i-esima history es, se ho 8 mosse e voglio accedere alla terzultima vado avanti finche contaotre!=contaMosse-i
};

Player::~Player()
{
    delete this->pimpl;
}

Player::Player(int player_nr = 1)
{
    pimpl->history=new mossa;
    this->pimpl->Player_Number=player_nr;
}

void Player::init_board(const std::string& filename) const
{//create and store an initial board to file
    //Player 1 is the one starting in the low row values (rows 0,1,2), 
	//player 2 starts in the high row values (rows 5,6,7).
    //se sono in colonna 7 e metto una pedina in riga 7
    this->pimpl->history= new mossa;
    
    ofstream Myfile(filename);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(0<=i<3||4<i<8)
            {//sono nel 'campo' di player 1 o player 2
                if((i%2==0&&j%2==0)||(i%2!=0&&j%2!=0))
                {//riempi con x o o se riga pari colonna pari o riga dispari colonna dispari
                //siccome sto costruendo con un vettore le posizioni di Player 1/2 sono 'rovesciati'
                    if(0<=i<3)
                    {//sono nel campo di player 2
                        this->pimpl->history->Campo_gioco[i][j]=this->x;
                        if(j==7)
                        {
                            Myfile<<x;
                        }
                        else
                        {
                            Myfile<<x<<" ";
                        }
                        
                    }
                    else
                    {//sono nel campo di player 1
                        this->pimpl->history->Campo_gioco[i][j]=this->o;
                        if(j==7)
                        {
                            Myfile<<o;
                        }
                        else
                        {
                            Myfile<<o<<" ";
                        }
                        
                    }
                    
                }
                else
                {//riempo con vuoto
                    this->pimpl->history->Campo_gioco[i][j]=this->e;
                    Myfile<<" ";
                }
            }
            else
            {//sono in mezzo e riempo con vuoto
                this->pimpl->history->Campo_gioco[i][j]=this->e;
                Myfile<<" ";
            }
        }
        Myfile<<"\n";
    }
    Myfile.close();
}

void Player::pop()
{
    if(this->pimpl->history!=nullptr)
    {
        mossa* app=this->pimpl->history;
        while(app->next!=nullptr)
        {
            app=app->next;
        }
        delete(app);
        app=nullptr;
    }
    
}

Player::piece Player::operator()(int r, int c, int history_offset = 0) const
{
    //vedere se esiste la hystory-esima(legge al contrario), capire come lanciare errore
    /*
        1) arrivare alla hystory-esima, difficile, se non la trovo errore index_out_of_bounds
        2)dopo che sono arrivato accedo a campo e ritorno il valore (r,c), se sono dentro i limiti sennò index_out_of_bounds
    */
   
    
}

bool Player::wins() const
{
    //se player 1 vedo se non ci sono più o/O con player 2 viceversa
    piece PedineDaControllare;
    piece DameDaControllare;
    if(this->pimpl->Player_Number==1)
    {
        PedineDaControllare=o;
        DameDaControllare=O;
    }
    else
    {
        PedineDaControllare=x;
        DameDaControllare=X;
    }
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            //metodo at da implementare
        }
    }
}
