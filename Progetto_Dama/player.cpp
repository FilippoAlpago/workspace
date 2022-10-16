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
    //int contaMosse=0;//mi serve poi per accedere alla i-esima history es, se ho 8 mosse e voglio accedere alla terzultima vado avanti finche contaotre!=contaMosse-i
};

Player::~Player()
{
    
    delete this->pimpl;
}

Player::Player(int player_nr = 1)
{
    pimpl->history=new mossa;
}

void Player::init_board(const std::string& filename) const
{//create and store an initial board to file
    //Player 1 is the one starting in the low row values (rows 0,1,2), 
	//player 2 starts in the high row values (rows 5,6,7).
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
                        Myfile<<o;
                    }
                    else
                    {//sono nel campo di player 1
                        this->pimpl->history->Campo_gioco[i][j]=this->o;
                        Myfile<<x;
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
            //ciao sono un commento
            
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
        delete(app->next);
        app->next=nullptr;
    }
    
}
