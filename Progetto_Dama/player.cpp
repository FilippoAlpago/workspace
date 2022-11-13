#include "player.hpp"
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
};

Player::Player(int player_nr = 1)
{
    if(player_nr==1||player_nr==2)
    {
        pimpl->history=new mossa;
        this->pimpl->Player_Number=player_nr;
    }
    else
    {
        
        string str="player number"+to_string(player_nr) +"non permesso";
        throw player_exception{player_exception::index_out_of_bounds,str};
        
    }
    
}

Player::~Player()
{
    delete this->pimpl;
}

Player::Player(const Player& p)
{
    this->pimpl->Player_Number=p.pimpl->Player_Number;
    //deep copy della hystory  di p in quella di this
    mossa* app1=this->pimpl->history;
    mossa* app2=p.pimpl->history;
    
}

Player& Player::operator=(const Player&)
{

}

Player::piece Player::operator()(int r, int c, int history_offset = 0) const
{
    //vedere se esiste la hystory-esima(legge al contrario), capire come lanciare errore
    /*
        1) arrivare alla hystory-esima, difficile, se non la trovo errore index_out_of_bounds
        2)dopo che sono arrivato accedo a campo e ritorno il valore (r,c), se sono dentro i limiti sennò index_out_of_bounds
    */
    
    
}

void Player::load_board(const std::string& filename)
{

}

void Player::store_board(const std::string& filename, int history_offset = 0) const
{

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
                    
                    Myfile<<" ";
                }
            }
            else
            {//sono in mezzo e riempo con vuoto
                
                Myfile<<" ";
            }
        }
        Myfile<<"\n";
    }
    Myfile.close();
}

void Player::move()
{

}

bool Player::valid_move() const
{

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
    }
    else
    {
        throw player_exception{player_exception::index_out_of_bounds};
    }
    
}

bool Player::wins(int player_nr) const
{

}

bool Player::wins() const
{
    //se player 1 vedo se non ci sono più o/O con player 2 viceversa
    piece PedineDaControllare;
    piece DameDaControllare;
    mossa* app=this->pimpl->history;
    if(this->pimpl->Player_Number==1)
    {//in base al player cerco determinate pedine, se non sono presenti allora vuol dire che ho vinto
        PedineDaControllare=o;
        DameDaControllare=O;
    }
    else
    {
        PedineDaControllare=x;
        DameDaControllare=X;
    }
    int i,j=0;
    bool trovato=false;
    if(app!=nullptr)
    {//hystory non vuota
        while(app->next!=nullptr)
        {//vai all'ultima board
            app=app->next;
        }

        while(i<=7&&trovato==false)
        {
            while(j<=7&&trovato==false)
            {
                if(app->Campo_gioco[i][j]==PedineDaControllare||app->Campo_gioco[i][j]==DameDaControllare)
                {//se in quella cella è presenta una pedina/dama che sto cercando, allora vuol dire che non ho vinto ancora
                    trovato=true;
                }
                j++;
            }
            i++;
        }
        return !trovato;//siccome sto cercando determinate pedine, non trovarle vuol dire che ho vinto(trovato=false ho vinto), altrimenti vuol dire che non ho vinto

    }
    else
    {
        return false;//non ho nessuna board su cui verificare se ho vinto
    }
    
}

bool Player::loses(int player_nr) const
{

}

bool Player::loses() const
{
    return !this->wins();
}

int Player::recurrence() const
{

}