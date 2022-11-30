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

Player::Player(int player_nr )
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
int countBoard(mossa* hystory)//metodo per "contare" le hystory, mi serve per operator() e storeBoard
{
    if(hystory==nullptr)
    {
        return 0;
    }
    else
    {
        int i=0;
        while (hystory->next!=nullptr)
        {
            i++;
        }
        return i; 
    }
}
Player::~Player()
{
    delete this->pimpl;
}

Player::Player(const Player& p)
{
    this->pimpl->Player_Number=p.pimpl->Player_Number;
    mossa* newHystory=nullptr;
    newHystory=copy(p.pimpl->history);
}
mossa* copy(mossa* source)//metodo interno per copia, servira per copy costructor e =
{
    if(source==nullptr)
    {
        return nullptr;
    }
    else
    {
        mossa* destination=new mossa;
        //deep copy campo da gioco
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                destination->Campo_gioco[i][j]=source->Campo_gioco[i][j];
            }
        }
        
        destination->next=copy(source->next);
        return destination;
    }
}

Player& Player::operator=(const Player& p)
{
    if(this!= &p)
    {
        //distuggi hystory this e poi copia quello che ci sta in p
        delete(this->pimpl->history);
        this->pimpl->history=copy(p.pimpl->history);
        this->pimpl->Player_Number=p.pimpl->Player_Number;
    }
    return *this;
}

Player::piece Player::operator()(int r, int c, int history_offset) const
{
    //vedere se esiste la hystory-esima(legge al contrario) e r,c sono validi(0<=r,c<8)
    /*
        1) arrivare alla hystory-esima, se non la trovo errore index_out_of_bounds
        2)dopo che sono arrivato accedo a campo e ritorno il valore (r,c), se sono dentro i limiti sennò index_out_of_bounds
    */
    int NumBoard=countBoard(this->pimpl->history); 
    if(NumBoard<history_offset||history_offset<0||NumBoard==0)
    {//history_offset > della history effetiva o non accetabile(negativa) o history vuota, intercettare
        string str="history numero"+to_string(history_offset) +"non esistente";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {//history_offset è "dentro il range " della mia history 
        //andiamo a quella history_offset
        int NumHystory=NumBoard-history_offset;
        int i=0;
        mossa* app=this->pimpl->history;
        while(i!=NumHystory)
        {
            app=app->next;
            i++;
        }

        if(0<=r<8)//r,c siano cordinate esistenti
        {
            if(0<=c<8)
            {
                return app->Campo_gioco[r][c];
            }
            else
            {
                string str="c="+to_string(c) +" colonna non esistente";
                throw player_exception{player_exception::index_out_of_bounds,str};
            }
        }
        else
        {
            string str="r="+to_string(r) +"riga non esistente";
            throw player_exception{player_exception::index_out_of_bounds,str};
        }
    }
    
}

void Player::load_board(const std::string& filename)
{

}

void Player::store_board(const std::string& filename, int history_offset) const
{

}

void Player::init_board(const std::string& filename) const
{//create and store an initial board to file
    //Player 1 is the one starting in the low row values (rows 0,1,2), 
	//player 2 starts in the high row values (rows 5,6,7).
    
    ofstream Myfile(filename);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {
            if(0<=i<=2||5<=i<=7)
            {//sono nel 'campo' di player 1 o player 2
                if((i%2==0&&j%2==0)||(i%2!=0&&j%2!=0))
                {//riempi con x oppure o se riga pari colonna pari o riga dispari colonna dispari
                //siccome sto costruendo con un vettore le posizioni di Player 1/2 sono 'rovesciati'
                    if(0<=i<=2)
                    {//sono nel campo di player 2
                        
                        if(j==7)
                        {
                            Myfile<<x<<"\n";
                            
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
                            if(i==7)
                            {//ultima riga e colonna
                                Myfile<<o<<"\0";
                            }
                            else 
                            {//ultima colonna, ma non riga
                                Myfile<<o<<"\n";
                            }
                            
                        }
                        else
                        {
                            Myfile<<o<<" ";
                        }
                        
                    }
                    
                }
                else
                {//riempo con vuoto
                    
                    Myfile<<"  ";
                }
            }
            else
            {//sono in mezzo e riempo con vuoto
                
                Myfile<<"  ";
            }
        }
    }
    Myfile.close();
}

void Player::move()
{//se hystori vuota errore
//prendi la board più recente in history, fai una mossa e poi metti in history la board post-mossa. la board risultante deve essere la board precedente più una mossa 'valida'
//se nessuna mossa allora perdo 
    if(this->pimpl->history==nullptr)
    {
        string str="history vuota, non posso muovere";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        mossa* app=this->pimpl->history;
        while (app->next!=nullptr)
        {
            app=app->next;
        }
        
    }
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
        string str="non posso eliminare una board dalla history se la history è vuota";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    
}

bool Player::wins(int player_nr) const
{
    if(player_nr!=1||player_nr!=2||this->pimpl->history==nullptr)
    {
        string str="history vuota, non posso controllare se hai vinto";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        if((player_nr==1&&player_nr==this->pimpl->Player_Number)||(player_nr==1&&player_nr==this->pimpl->Player_Number))
        {//se player_nr coincide con player_Number allora richiamo Player::wins()
            return this->wins();
        }
        else
        {//player_nr player_number non coincidono; 
        //se this->pimpl->Player_number differisce da player_nr allora vuol dire che, per far si che player_nr vinca, player_Number deve aver perso
            return this->loses();// se ho perso allora plyer_nr ha vinto
        }
    }
    
}

bool Player::wins() const
{
    //se player 1 vedo se non ci sono più o/O con player 2 viceversa
    if(this->pimpl->history!=nullptr)
    {
        mossa* app=this->pimpl->history;
        piece PedineDaControllare;
        piece DameDaControllare;
        while(app->next!=nullptr)
        {
            app=app->next;
        }

        if(this->pimpl->Player_Number==1)
        {//in base al player cerco determinate pedine, se non sono presenti allora vuol dire che ho vinto; se player 1 cerco le o/O e viceversa per player 2
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
    {//non posso 
        string str="history vuota, non posso controllare se hai vinto";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
}

bool Player::loses(int player_nr) const
{
    if(player_nr!=1||player_nr!=2||this->pimpl->history==nullptr)
    {
        string str="history vuota, non posso controllare se hai perso";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        if((player_nr==1&&player_nr==this->pimpl->Player_Number)||(player_nr==1&&player_nr==this->pimpl->Player_Number))
        {//se player_nr coincide con player_Number allora richiamo Player::loses()
            return this->loses();
        }
        else
        {//player_nr player_number non coincidono; 
        //se this->pimpl->Player_number differisce da player_nr allora vuol dire che, per far si che player_nr perda, player_Number deve aver vinto
            return this->wins();// se ho vinto allora plyer_nr ha perso
        }
    }
}

bool Player::loses() const
{
    if(this->pimpl->history!=nullptr)
    {
        mossa* app=this->pimpl->history;
        piece PedineDaControllare;
        piece DameDaControllare;
        while(app->next!=nullptr)
        {
            app=app->next;
        }

        if(this->pimpl->Player_Number==1)
        {// se player 1 cerco le x/X e viceversa per player 2
            PedineDaControllare=x;
            DameDaControllare=X;
        }
        else
        {
            PedineDaControllare=o;
            DameDaControllare=O;
        }

        int i,j=0;
        bool trovato=false;
        while(i<=7&&trovato==false)
        {
            while(j<=7&&trovato==false)
            {
                if(app->Campo_gioco[i][j]==PedineDaControllare||app->Campo_gioco[i][j]==DameDaControllare)
                {//se in quella cella è presenta una pedina/dama che sto cercando, allora vuol dire che non ho perso ancora
                    trovato=true;
                }
                j++;
            }
            i++;
        }
        return !trovato;
    }
    else
    {//non posso 
        string str="history vuota, non posso controllare se hai perso";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
}

int Player::recurrence() const
{

}