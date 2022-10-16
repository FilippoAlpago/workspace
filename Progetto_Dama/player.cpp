#include"player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
struct mossa
{
    
    int Campo_gioco [8][8];//campo da gioco di dama
    mossa* next=nullptr;//mossa succesiva
};
struct Player::Impl
{
    mossa* history=nullptr;//history tiene traccia di tutte le mosse
    int contaMosse=0;//mi serve poi per accedere alla i-esima history es, se ho 8 mosse e voglio accedere alla terzultima vado avanti finche contaotre!=contaMosse-i
};
Player::~Player()
{
    delete this->pimpl;
}

Player::Player(int player_nr = 1)
{
    pimpl->history=new mossa;
    //impostare campo di gioco con pedine
    //Player 1 is the one starting in the low row values (rows 0,1,2), 
	//player 2 starts in the high row values (rows 5,6,7).
    
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(0<=i<3||4<i<9)
            {//sono nel 'campo' di player 1 o player 2
                if((i%2==0&&j%2!=0)||(i%2!=0&&j%2==0))
                {//riempi con x o o se riga pari colonna dispari o riga dispari colonna pari
                    if(0<=i<3)
                    {//sono nel campo di player 1
                        this->pimpl->history->Campo_gioco[i][j]=this->x;
                    }
                    else
                    {//sono nel campo di player 2
                        this->pimpl->history->Campo_gioco[i][j]=this->o;
                    }
                    
                }
                else
                {//riempo con vuoto
                    this->pimpl->history->Campo_gioco[i][j]=this->e;
                }
                    
               
            }
            else
            {//sono in mezzo e riempo con vuoto
                this->pimpl->history->Campo_gioco[i][j]=this->e;
            }
            //ciao sono un commento
            
        }
    }
    
}