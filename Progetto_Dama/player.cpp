#include"player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
struct mossa
{
    
    int Campo_gioco [8][8];//campo da gioco di dama
    mossa* next;//mossa succesiva
};
struct Player::Impl
{
    mossa* history=nullptr;//history tiene traccia di tutte le mosse
    
};

Player::Player(int player_nr = 1)
{
    //prima creo una nuova mossa, poi la attaco alla history
    mossa* app=new mossa;
    

    
}