#include "player.hpp"

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


Player::piece CharToPiece(char c)//conclusa definitivo
{        
    if(c=='x')
    {
        return Player::piece::x;
    }
    else
    {
        if(c=='X')
        {
            return Player::piece::X;
        }
        else
        {
            if(c=='o')
            {
                return Player::piece::o;
            }
            else
            {
                if(c=='O')
                {
                    return Player::piece::O;
                }
                else
                {
                    return Player::piece::e;
                }
            }
        }
    }
    
}

mossa* copy( mossa* source)//metodo interno per copia, servira per copy costructor e =
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

void sistemaRiga(string& rigaDasistemare)//concluso definitivo//metodo che elimina spazi in eccesso
{//assunto il formato che la riga deve avere sul file
    int i=1,countSpaziEliminati=0;
    while(i<8)
    {
        if(i+countSpaziEliminati%2!=0)//se la somma dei 2 è dispari allora in quella posizione i vi è sicuramente un spazio in eccesso da eliminare
        {
            rigaDasistemare.erase(i,1);
            countSpaziEliminati++;
        }
        i++;
    }  
}
int countBoard(mossa* hystory)//concluso definitivo//metodo per "contare" le hystory, mi serve per operator() e storeBoard
{
    //cout<<"ciao sono all'inizio"<<endl;
    if(hystory==nullptr)
    {
        //cout<<"sono dentro if"<<endl;
        return 0;
    }
    else
    {
        //cout<<"sono nell'else"<<endl;
        int i=1;
        while(hystory->next!=nullptr)
        {
            //cout<<i<<endl;
            i++;
            hystory=hystory->next;
        }
        return i; 
    }
}
bool boardApposto(Player::piece board[8][8])//concluso definitivo mi serve per load_board e valid_move; verifica se la board è valida, numero pedine giusto e al proprio posto
{
    int NumPedine_o=0,numDame_O=0,NumPedine_x=0,numDame_X=0;
    int rows=0,cools=0;
    bool BoardValida=true;
    while (rows<8&&BoardValida==true)
    {
        while(cools<8&&BoardValida==true)
        {
            

            if(board[rows][cools]!=Player::piece::e)
            {
                //cout<<"ho trovato qualcosa !=e, è "<<to_string(board[rows][cools])<<endl;
                if((rows+cools)%2!=0)//leggo qualcosa diverso da e
                {//pedina o dama devono stare in posizione in cui Rows P e Cool P  o  Rows D e Cools D(la somma di rows e cool è pari), altrimenti sono fuori posto
                    //cout<<"ho trovato qualcosa !=e in posizione errata"<<endl;
                    BoardValida=false;
                }
                else
                {
                    if(board[rows][cools]==Player::piece::x)
                    {
                        if(rows==0)
                        {//in riga zero non ci devono essere le x ma X
                            //cout<<"ho trovato una x in posizione sbagliata, ci deve essere una X"<<endl;
                            BoardValida=false;
                        }
                        NumPedine_x++;
                    }
                    else
                    {
                        if(board[rows][cools]==Player::piece::X)
                        {
                            numDame_X++;
                        }
                        else
                        {
                            if(board[rows][cools]==Player::piece::o)
                            {
                                if(rows==7)
                                {//in riga 7 non ci devono essere le o,ma le O
                                    BoardValida=false;
                                }
                                NumPedine_o++;
                            }
                            else
                            {
                                numDame_O++;
                            }
                        }
                    }
                }
            }
            cools++;
            
        }
        cools=0;      
        rows++;
    }

    if((NumPedine_o+numDame_O>12||NumPedine_x+numDame_X>12)||(NumPedine_o+numDame_O==0&&NumPedine_x+numDame_X==0))
    {//se somma delle 2 >12 ci sono troppo pedine in campo; oppure se la somma di entrambe=0 la scacchiera è vuota
        BoardValida=false;
    }

    return BoardValida;
}
char pieceToChar(Player::piece p)//concluso definitivo
{
    if(p==Player::e)
    {
        return ' ';
    }
    else
    {
        if(p==Player::o)
        {
            return 'o';
        }
        else
        {
            if(p==Player::O)
            {
                return 'O';
            }
            else
            {
                if(p==Player::x)
                {
                    return 'x';
                }
                else
                {
                    return 'X';
                }
            }
        }
    }
}

int* eatPositions(Player::piece board[8][8],int rows, int cool, int dim, int player_nr)//quasi concluso, buttarci un occhio
{//ogni due posizioni del vettore che ritorno c'è la coppia riga-colonna in cui potrei mangiare; se dim==0 restituisco nullptr, altrimenti se non posso mangiare scrivo -1 nelle 2 posizioni del vettore;
    if(dim==0)
    {
        return nullptr;
    }
    else
    {
        Player::piece pedinaDaMangiare,DamaDaMangiare;
        if(player_nr==1)
        {
            pedinaDaMangiare=Player::piece::o;
            DamaDaMangiare=Player::piece::O;
        }
        else
        {
            pedinaDaMangiare=Player::x;
            pedinaDaMangiare=Player::X;
        }
        int* posValid= (int*) malloc((dim*2) *sizeof(int));//*2 perche perche le posizioni in cui posso mangiare sono a coppie
        bool eatWithDama=true;
        if(dim==2)
        {//ho 2 possibilità di mangiare, quindi sono una pedina; se è 4 allora è una dama, perchè puo magiare anche indietro
            eatWithDama=false;
        }
        bool bassoSX=true,bassoDX=true,altoSX=true,altoDX=true;
        
        if(player_nr==1&&eatWithDama==false)
        {//dato che sono player_1 mangio verso l'alto
            bassoDX=false;
            bassoSX=false;
            /*  
            se pedina si trova in cool=0,1 allora non ha senso controllare in altoSX
            se pedina si trova in cool=6,7 allora non ha senso controllare in altoDX
            se pedina si trova in riga=0,1 non ha senso controllare in altoSX e altoDX
            */
           if(rows==0||rows==1)
           {
                altoDX=false;
                altoSX=false;
           }
           else
           {
                if(cool==0||cool==1)
                {
                    altoSX=false;
                }
                else
                {
                    if(cool==6||cool==7)
                    {
                        altoDX=false;
                    }
                }
           } 
        }
        else if(player_nr==2&&eatWithDama==false)
        {//dato che sono player2 mangio verso il basso
            
            altoDX=false;
            altoSX=false;
            /*  
            se pedina si trova in cool=0,1 allora non ha senso controllare in bassoSX
            se pedina si trova in cool=6,7 allora non ha senso controllare in bassoDX
            se pedina si trova in riga=6,7 non ha senso controllare in bassoSX e bassoDX
            */
            if(rows==6||rows==7)
            {
                bassoDX=false;
                bassoSX=false;
            }
            else
            {
                if(cool==0||cool==1)
                {
                    bassoSX=false;
                }
                else
                {
                    if(cool==6||cool==7)
                    {
                        bassoDX=false;
                    }
                }
            }
        }
        else if(eatWithDama==true)
        {//non importa che giocatore sono, ma verso dove posso mangiare; il giocatore importa per stabilire quali pedine sono le nemiche
            if(cool==0||cool==1)
            {
                if(rows==0||rows==1)
                {//controllo solo bassoDX
                    altoDX=false;
                    altoSX=false;
                    bassoSX=false;
                }
                else
                {
                    if(rows=6||rows==7)
                    {//controllo solo altoDX
                        altoSX=false;
                        bassoDX=false;
                        bassoSX=false;
                    }
                    else
                    {//controllo solo bassoDX e altoDX
                        altoSX=false;
                        bassoSX=false;
                    }
                }
            }
            else if (cool==6||cool==7)
            {
                if(rows==0||rows==1)
                {//controllo solo bassoSX
                    altoDX=false;
                    altoSX=false;
                    bassoDX=false;
                }
                else
                {
                    if(rows==6||rows==7)
                    {//controllo solo altoSX
                        bassoDX=false;
                        bassoSX=false;
                        altoDX=false;
                    }
                    else
                    {//controllo solo bassoDX e altoDX
                        bassoDX=false;
                        altoDX=false;
                    }
                }
            }
            else if (cool>=2&&cool<=5)
            {
                if(rows==0||rows==1)
                {
                    altoDX=false;
                    altoSX=false;
                }
                else
                {
                    if(rows==6||rows==7)
                    {
                        bassoDX=false;
                        bassoSX=false;
                    }
                }
            }            
        }
        //in base ai flag controllo; devo stabilire quali pedine siano le nemiche
        int i=0;
        if(altoDX==true)//abbaso riga ed aumento colonna
        {// se in altoDx c'è una pedina avversaria e nella diagonale dopo è libero(c'è 'e')-> posso mangiare
            cout<<"posso mangiare in altoDX"<<endl;
            if(eatWithDama==false)
            {//non devo mangiare con una dama, se nella digonale c'è una dama non posso mangiare, perchè io sono una pedina
                
                if(board[rows-1][cool+1]!=DamaDaMangiare)
                {//se non è  dama devo controllare se c'è una pedina nemica
                    if(board[rows-1][cool+1]==pedinaDaMangiare)
                    {
                        if(board[rows-2][cool+2]==Player::piece::e)
                        {//se dopo c'è spazio allora posso aggiungere le posizioni
                            posValid[i]=rows-2;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=cool+2;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        else
                        {//dopo  non c'è spazio. quindi non posso mangiare
                            posValid[i]=-1;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=-1;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        
                    }
                    else
                    {//dopo  c'e una dama o uno spazio, quindi non posso mangiare
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {//dopo c'è dama. quindi non posso mangiare
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
            else
            {//devo mangiare con una dama, può amngiare chiunque, basta che sia nemico
                if(board[rows-1][cool+1]==pedinaDaMangiare||board[rows-1][cool+1]==DamaDaMangiare)
                {
                    if(board[rows-2][cool+2]==Player::piece::e)
                    {
                        posValid[i]=rows-2;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=cool+2;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                    else
                    {
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
        }
        else
        {
            //cout<<"move() non posso muovere in altoDX"<<endl;
            posValid[i]=-1;
            //cout<<"move() riga "<<posValid[i];
            i++;
            posValid[i]=-1;
            //cout<<"move() colonna "<<posValid[i]<<endl;
            i++; 
        }

        if (altoSX==true)//diminuisci riga e colonna
        {
            
            if(eatWithDama==false)
            {//non devo mangiare con una dama, se nella digonale c'è una dama non posso mangiare, perchè io sono una pedina
                
                if(board[rows-1][cool-1]!=DamaDaMangiare)
                {//se non è  dama devo controllare se c'è una pedina nemica
                
                    if(board[rows-1][cool-1]==pedinaDaMangiare)
                    {
                        if(board[rows-2][cool-2]==Player::piece::e)
                        {//se dopo c'è spazio allora posso aggiungere le posizioni
                            posValid[i]=rows-2;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=cool-2;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        else
                        {//dopo  non c'è spazio. quindi non posso mangiare
                            posValid[i]=-1;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=-1;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        
                    }
                    else
                    {//dopo  c'e una dama o uno spazio, quindi non posso mangiare
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {//dopo c'è dama. quindi non posso mangiare
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
            else
            {//devo mangiare con una dama, può manngiare chiunque, basta che sia nemico
                if(board[rows-1][cool-1]==pedinaDaMangiare||board[rows-1][cool-1]==DamaDaMangiare)
                {
                    if(board[rows-2][cool-2]==Player::piece::e)
                    {
                        posValid[i]=rows-2;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=cool-2;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                    else
                    {
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
        }
        else
        {
            //cout<<"move() non posso muovere in altoSX"<<endl;
            posValid[i]=-1;
            //cout<<"move() riga "<<posValid[i];
            i++;
            posValid[i]=-1;
            //cout<<"move() colonna "<<posValid[i]<<endl;
            i++; 
        }

        if (bassoDX==true)//aumento riga e colonna
        {
            if(eatWithDama==false)
            {//non devo mangiare con una dama, se nella digonale c'è una dama non posso mangiare, perchè io sono una pedina
                
                if(board[rows+1][cool+1]!=DamaDaMangiare)
                {//se non è  dama devo controllare se c'è una pedina nemica
                    if(board[rows+1][cool+1]==pedinaDaMangiare)
                    {
                        if(board[rows+2][cool+2]==Player::piece::e)
                        {//se dopo c'è spazio allora posso aggiungere le posizioni
                            posValid[i]=rows+2;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=cool+2;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        else
                        {//dopo  non c'è spazio. quindi non posso mangiare
                            posValid[i]=-1;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=-1;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        
                    }
                    else
                    {//dopo  c'e una dama o uno spazio, quindi non posso mangiare
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {//dopo c'è dama. quindi non posso mangiare
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
            else
            {//devo mangiare con una dama, può amngiare chiunque, basta che sia nemico
                if(board[rows+1][cool+1]==pedinaDaMangiare||board[rows+1][cool+1]==DamaDaMangiare)
                {
                    if(board[rows+2][cool+2]==Player::piece::e)
                    {
                        posValid[i]=rows+2;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=cool+2;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                    else
                    {
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }    
        }
        else
        {
            //cout<<"move() non posso muovere in bassoDX"<<endl;
            posValid[i]=-1;
            //cout<<"move() riga "<<posValid[i];
            i++;
            posValid[i]=-1;
            //cout<<"move() colonna "<<posValid[i]<<endl;
            i++; 
        }

        if (bassoSX==true)//aumento riga diminuisco colonna
        {
            if(eatWithDama==false)
            {//non devo mangiare con una dama, se nella digonale c'è una dama non posso mangiare, perchè io sono una pedina
                
                if(board[rows+1][cool-1]!=DamaDaMangiare)
                {//se non è  dama devo controllare se c'è una pedina nemica
                    if(board[rows+1][cool-1]==pedinaDaMangiare)
                    {
                        if(board[rows+2][cool-2]==Player::piece::e)
                        {//se dopo c'è spazio allora posso aggiungere le posizioni
                            posValid[i]=rows+2;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=cool-2;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        else
                        {//dopo  non c'è spazio. quindi non posso mangiare
                            posValid[i]=-1;
                            //cout<<"move() riga "<<posValid[i];
                            i++;
                            posValid[i]=-1;
                            //cout<<"move() colonna "<<posValid[i]<<endl;
                            i++;
                        }
                        
                    }
                    else
                    {//dopo  c'e una dama o uno spazio, quindi non posso mangiare
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {//dopo c'è dama. quindi non posso mangiare
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
            else
            {//devo mangiare con una dama, può mangiare chiunque, basta che sia nemico
                if(board[rows+1][cool-1]==pedinaDaMangiare||board[rows+1][cool+1]==DamaDaMangiare)
                {
                    if(board[rows+2][cool-2]==Player::piece::e)
                    {
                        posValid[i]=rows+2;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=cool-2;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                    else
                    {
                        posValid[i]=-1;
                        //cout<<"move() riga "<<posValid[i];
                        i++;
                        posValid[i]=-1;
                        //cout<<"move() colonna "<<posValid[i]<<endl;
                        i++;
                    }
                }
                else
                {
                    posValid[i]=-1;
                    //cout<<"move() riga "<<posValid[i];
                    i++;
                    posValid[i]=-1;
                    //cout<<"move() colonna "<<posValid[i]<<endl;
                    i++;
                }
            }
        }
        else
        {
            //cout<<"move() non posso muovere in bassoSX"<<endl;
            posValid[i]=-1;
            //cout<<"move() riga "<<posValid[i];
            i++;
            posValid[i]=-1;
            //cout<<"move() colonna "<<posValid[i]<<endl;
            i++; 
        }
        //se i flag sono false devo mettere le posizioni a -1; 
        return posValid;
    }   
}


Player::Player(int player_nr )//concluso definitivo
{
    
    if(player_nr==1||player_nr==2)
    {
        this->pimpl=new Impl;
        this->pimpl->Player_Number=player_nr;
        pimpl->history=nullptr;
        
    }
    else
    {
        string str="player number"+to_string(player_nr) +"non permesso \n";       
        throw player_exception{player_exception::err_type::index_out_of_bounds,str};
    }
    
}

Player::~Player()
{
    delete this->pimpl;
}

Player::Player(const Player& p)
{
    
    this->pimpl->Player_Number=p.pimpl->Player_Number;
    this->pimpl->history=copy(p.pimpl->history);
    //mossa* newHystory=nullptr;
    //newHystory=copy(p.pimpl->history);
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

Player::piece Player::operator()(int r, int c, int history_offset) const//concluso definitivo
{
    //vedere se esiste la hystory-esima(legge al contrario) e r,c sono validi(0<=r,c<8)
    /*
        1) arrivare alla hystory-esima, se non la trovo errore index_out_of_bounds
        2)dopo che sono arrivato accedo a campo e ritorno il valore (r,c), se sono dentro i limiti sennò index_out_of_bounds
    */
    mossa* app=this->pimpl->history;
    /*if(this->pimpl->history==nullptr)
    {
        cout<<" Operator() this->pimpl->hystory è vuoto \n"<<endl;
    }*/   
    int NumBoard=countBoard(app);
     
    //cout<<"operator() ci sono "<<NumBoard<<" board nella hystory"<<endl;
    if(NumBoard<history_offset||history_offset<0||NumBoard==0)
    {//history_offset > della history effetiva o non accetabile(negativa) o history vuota, intercettare
        
        string str="history numero "+to_string(history_offset) +"non esistente";
        cout<<"operator() "<<str<<endl;
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {//history_offset è "dentro il range " della mia history 
        //andiamo a quella history_offset
        
        //cout<<" operator() c'è qualcosa dentro la hysty"<<endl;
        int NumHystory=NumBoard-history_offset-1;
        app=this->pimpl->history;
        
        while(NumHystory>0)
        {
            app=app->next;
            NumHystory--;
        }
        //cout<<"operator() sono arrivato in posizione offSet"<<endl;
        if(0<=r<8)//r,c siano cordinate esistenti
        {
            if(c<8&&c>=0)
            {
                /*cout<<"operator() rstituisco il valore"<<endl;
                cout<<"operator() riga "<<r<<" colonna "<<c<<endl;
                if(app==nullptr)
                {
                    cout<<"operator() app è vuoto"<<endl;
                }*/
                return app->Campo_gioco[r][c];
            }
            else
            {
                string str="c="+to_string(c) +", colonna non esistente";
                cout<<"operator() "<<str<<endl;
                throw player_exception{player_exception::index_out_of_bounds,str};
            }
        }
        else
        {
            string str="r="+to_string(r) +", riga non esistente";
            cout<<"operator() "<<str<<endl;
            throw player_exception{player_exception::index_out_of_bounds,str};
        }
    }
    
}

void Player::load_board(const std::string& filename)//concluso definitivo
{
    /*
        1) controllare se formato file corretto .txt
        2) vedere se file si è aperto corretamente
        3) controllare se in riGA 0 ci sono o oppure in riga 7 ci sono x
        4) leggere riga per riga, elimnare spazi in eccesso e controlare che la board sia valida; numero pedine giusto, lunghezza riga==15, pedine su posizione correta{riga P colonna P, riga D colonna D}
    */
   if(filename.substr(filename.find_last_of(".")+1)=="txt")
   {//estensione correta
        
        ifstream Myfile;
        Myfile.open(filename);

        if(Myfile.good())
        {// è stato aperto corretamente
            
            string riga;
            bool rigaApposto=true;
            int rows=0,cools=0;//interatori per aggiungere elementi letti dal file nella board
            mossa* app=this->pimpl->history;//da qui iniziano i problemi!!!. verificare a casa.!!!!!
            if(app!=nullptr)
            {
                //cout<<"Load_board() app non è vuoto"<<endl;
                while(app->next!=nullptr)
                {
                    app=app->next;
                }
                app->next=new mossa;
                app->next->next=nullptr;
                app=app->next;
            }
            else
            {
                //cout<<" Load_board()app è vuoto"<<endl;
                app=new mossa;
                app->next=this->pimpl->history;
                this->pimpl->history=app; 
            }
            
            //cout<<" sono prima della lettura del file"<<endl;
            while(getline(Myfile,riga)&&rigaApposto==true)
            {//ad ogni riga letta, prima la "pulisco" dagli spazi in eccesso
                if(riga.length()!=15)
                {//deve essere cosi
                    //cout<<"lunghezza riga non apposto, è "<<riga.length()<<endl;
                    rigaApposto=false;
                }
                else
                {//modifico e aggiungo riga alla mia board
                    sistemaRiga(riga);//'pulisci' riga da spazi
                
                    for(int i=0;i<riga.length();i++)
                    {
                        app->Campo_gioco[rows][cools]=CharToPiece(riga.at(i));
                        
                        //cout<<app->Campo_gioco[rows][cools];
                        cools++;
                    }
                    //cout<<endl;
                    rows++;
                    cools=0;
                }
                
            }
            /*cout<<"ora stampo la board"<<endl;            
            for(int i=0;i<8;i++)
            {
                for(int j=0;j<8;j++)
                {
                    cout<<(app->Campo_gioco[i][j]);
                }
                cout<<endl;
            }*/
            //dopo aver finito di aggiungere alla mia board, controllo che sia valida
            bool BoardValida=boardApposto(app->Campo_gioco);          
            if(BoardValida==false)
            {
                cout<<" il file contiene una board invalida"<<endl;
                string str="il file "+filename+" contiene una scacchiera non valida";
                throw player_exception{player_exception::invalid_board,str};
            }
            else
            {
                if(rigaApposto==false)
                {
                    cout<<" il file contiene una riga invalida"<<endl;
                    string str="il file "+filename+" contiene una riga non valida";
                    throw player_exception{player_exception::invalid_board,str};
                }
            }
            
            Myfile.close();
        }
        else
        {//erroe nell'apertura del file
            cout<<" il file non è stao aperto corretamente"<<endl;
            string str="errore nell'apertura di "+filename+", probabilmente il file non esiste";
            throw player_exception{player_exception::missing_file,str};
        }
   }
   else
   {
        cout<<" il file non ha estensione corretta"<<endl;
        string str="filename "+filename+" non ha un estensione corretta";
        throw player_exception{player_exception::missing_file,str};
   }
}

void Player::store_board(const std::string& filename, int history_offset) const//conclusa definitivo
{
    mossa* app=this->pimpl->history;
    int NumBoard=countBoard(app);
    if(NumBoard<history_offset||history_offset<0||NumBoard==0)
    {
        string str="history numero"+to_string(history_offset) +"non esistente";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        ofstream Myfile(filename);
        int counter=NumBoard-history_offset-1;
        
        app=this->pimpl->history;
        while(counter>0)
        {
            app=app->next;
            counter--;
        }
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {//se ritorna e devo scrivere " "
                if(pieceToChar(app->Campo_gioco[i][j])!='e')
                {
                    Myfile<<pieceToChar(app->Campo_gioco[i][j]);
                }
                else
                {
                    Myfile<<" ";
                }
                     
                if(j==7)
                {
                    if(i!=7)
                    {// ogni volta che arrivo a j==7 e i!=7 faccio una newLine
                        Myfile<<"\n";
                    }
                    //non entro nel if se i==7, banalmente non scrivo niente
                }
                else
                {
                    Myfile<<" ";
                }
                
            }
        }
        Myfile.close();
    }
}

void Player::init_board(const std::string& filename) const//concluso definitivo
{//create and store an initial board to file
    //Player 1 is the one starting in the low row values (rows 0,1,2), 
	//player 2 starts in the high row values (rows 5,6,7).
    
    ofstream Myfile(filename);
    for(int i=0;i<8;i++)
    {
        for(int j=0;j<8;j++)
        {

            if((i>=0&&i<3)||(i>=5&&i<8))
            {//sono nel 'campo' di player 1 o player 2
            //riempi con x oppure o se riga pari colonna pari o riga dispari colonna dispari(se la somma delle 2 è pari)
                //siccome sto costruendo con un vettore le posizioni di Player 1/2 sono 'rovesciati'
                if((i+j)%2==0)
                {
                   if(i>=0&&i<=2)
                   {
                        if(j==7)
                        {
                            Myfile<<"o"<<"\n";
                        }
                        else
                        {
                            Myfile<<"o ";
                        }
                   }
                    else if(i>=5&&i<=7)
                   {
                        if(j==7&&i==7)
                        {
                            Myfile<<"x";
                        }
                        else
                        {
                            if(j==7)
                            {
                                Myfile<<"x"<<"\n";
                            }
                            else
                            {
                                Myfile<<"x ";
                            }
                        }
                   }
                          
                }
                else
                {//riempo in mezzo fra le pedine con spazio
                    
                    Myfile<<" ";
                    if(j==7)
                    {
                        Myfile<<"\n";
                    }
                    else
                    {
                        Myfile<<" ";
                    }
                    
                }
            }
            else
            {//sono in mezzo al campo da gioco e riempo con vuoto
                Myfile<<" ";
                if(j==7)
                {
                    Myfile<<"\n";
                }
                else
                {
                    Myfile<<" ";
                }
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
        {//ultima hystory
            app=app->next;
        }
        piece pedinaDaMuovere,DamaDaMuovere;
        if(this->pimpl->Player_Number==1)
        {
            pedinaDaMuovere=Player::x;
            DamaDaMuovere=Player::X;
        }
        else
        {
            pedinaDaMuovere=Player::o;
            DamaDaMuovere=Player::O;
        }
        /*x sposto con --di riga e ++ di colonna oppure -- di riga e -- colonna; 
          o sposrto con ++ riga e ++ colonna oppure -- colonna e ++ riga
          Dame si possono muovere in qualsiasi direzione
        1) scelgo a caso una pedina fra le mie(genero 2 cordinate e cerco in quella posizione) e la muovo(scelgo a caso la mossa??????)
        2) se posso mangiare mangio
        3) se  arriva a riga=0 allora x diventa X; se arrivo riga=7 o diventa O;
        */
        
        int max=7,min=0,range=max-min+1;
        srand((unsigned) time(NULL));
        int rows=rand()%range+min,cools=rand()%range+min;
        bool ho_trovato=false;
        while(ho_trovato==false)//rifare la ricerca della pedina da muovere
        {//continuo a 'ceracare' finchè non ho trovato una mia pedina/dama
            if(app->Campo_gioco[rows][cools]==pedinaDaMuovere)
            {
                ho_trovato=true;
            }
            else if(app->Campo_gioco[rows][cools]==DamaDaMuovere)
            {
                ho_trovato=true;
            }
            else
            {
                rows=(rand()%8);
                cools=(rand()%8);
            }
            
            //cout<<rows<<","<<cools<<endl;

        }
        cout<<"move() ho deciso di muovere "<<pieceToChar(app->Campo_gioco[rows][cools])<<" in posizione "<<rows<<","<<cools<<endl;
        //esco quando ho trovato qeuello che voglio muovere!!!!!!!!!! se passo una board con solo un tipo di pedine va avnti all'infinito
        bool pedinaIsDama=false;
        int possibiliPosizioniIncuiMangiare=2;
        if(app->Campo_gioco[rows][cools]==DamaDaMuovere)
        {
            pedinaIsDama=true;
            possibiliPosizioniIncuiMangiare=4;
        }
        cout<<" move() ora chiamo la funzione che mi ritorna le possibili posizioni in cui mangiare"<<endl;
        int* posizioniPossibili=eatPositions(app->Campo_gioco,rows,cools,possibiliPosizioniIncuiMangiare,this->pimpl->Player_Number);
        bool possoMangiare=true;
        cout<<"move() posso mangiare in qualche posizione"<<endl;
        possibiliPosizioniIncuiMangiare=possibiliPosizioniIncuiMangiare*2;
        /*ora che ho le posizioni devo:
            -vedere se posso mangiare(se tutte le coppie sono diverse da -1), altrimenti non posso mangiare
            -se una coppia è -1, allora in qualche modo devo scegliere altro fuorchè quella coppia
        */
        int i=0;

        while(i<possibiliPosizioniIncuiMangiare)
        {
            i=i+2;
        }

       Player::piece nuovaBoard[8][8];
    }
}


bool Player::valid_move() const
{
    return false;
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
    else
    {
        string str="non posso eliminare una board dalla history se la history è vuota";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    
}

bool Player::wins(int player_nr) const //concluso definitivo
{
    if((player_nr!=1&&player_nr!=2)||this->pimpl->history==nullptr)
    {
        string str;
        if(player_nr!=1&&player_nr!=2)
        {
            str="player number"+to_string(player_nr) +"non permesso \n";
        }
        else
        {
            str="history vuota, non posso controllare se hai perso";
        }
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        if(player_nr==this->pimpl->Player_Number)
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

bool Player::wins() const//concluso definitivo
{
    //se player 1 vedo se non ci sono più o/O con player 2 viceversa
    if(this->pimpl->history!=nullptr)
    {
        //cout<<"wins() sono all'inizio"<<endl;
        mossa* app=this->pimpl->history;
        piece PedineDaControllare;
        piece DameDaControllare;
        
        while(app->next!=nullptr)
        {
            app=app->next;
        }
        
        /*if(app==nullptr)
        {
            cout<<"wins() app è nullptr"<<endl; 
        }
        cout<<"wins() "<<app->Campo_gioco[2][6]<<endl; 
        cout<<"wins() sono dopo lo scorrimento"<<endl;  
        cout<<"wins() sono alle selezione delle pedine che devo cercare"<<endl;*/
        if(this->pimpl->Player_Number==1)
        {//in base al player cerco determinate pedine, se non sono presenti allora vuol dire che ho vinto; se player 1 cerco le o/O e viceversa per player 2
            PedineDaControllare=Player::o;
            DameDaControllare=Player::O;
        }
        else
        {
            PedineDaControllare=Player::x;
            DameDaControllare=Player::X;
        }
        //cout<<"wins() sono dopo la selezione delle pedine che devo cercare"<<endl;
        int i=0,j=0;
        bool trovato=false;
        //cout<<"wins() sono prima delle revisione riga per riga"<<endl;
        while(i<8&&trovato==false)
        {
            while(j<8&&trovato==false)
            {
                //cout<<"wins() sono prima del if sul controllo della tabella"<<endl;
                
                if(app->Campo_gioco[i][j]==PedineDaControllare||app->Campo_gioco[i][j]==DameDaControllare)
                {
                    trovato=true;
                }
                
                j++;
            }
            j=0;
            i++;
        }
        /*cout<<"wins() ho controllato righe "<<i<<" e colonne "<<j<<endl;
        cout<<"wins() sono dopo ls revisione riga per riga"<<endl;*/
        return !trovato;//siccome sto cercando determinate pedine, non trovarle vuol dire che ho vinto(trovato=false ho vinto), altrimenti vuol dire che non ho vinto
    }
    else
    {//non posso 
        string str="history vuota, non posso controllare se hai vinto";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
}

bool Player::loses(int player_nr) const//concluso definitivo
{
    if((player_nr!=1&&player_nr!=2)||this->pimpl->history==nullptr)
    {
        string str;
        if(player_nr!=1&&player_nr!=2)
        {
            str="player number"+to_string(player_nr) +"non permesso \n";
        }
        else
        {
            str="history vuota, non posso controllare se hai perso";
        }
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        if(player_nr==this->pimpl->Player_Number)
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

bool Player::loses() const //concluso definitivo
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

        int i=0,j=0;
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
            j=0;
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
    if(this->pimpl->history==nullptr)
    {
        string str="history vuota";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        mossa* last=this->pimpl->history;
        while(last->next!=nullptr)
        {//ultima board
            last=last->next;
        }
        int count=0;
        mossa* app=this->pimpl->history;
        int rows=0,cools=0;
        bool boardUguali=true;
        while (app!=last)
        {
            rows=0,cools=0;
            while (rows<=7&&boardUguali==true)
            {
                while(cools<=7&&boardUguali==true)
                {
                    
                    if(last->Campo_gioco[rows][cools]==app->Campo_gioco[rows][cools])
                    {
                        boardUguali=false;
                    }
                    cools++;
                }  
                cools=0;
                rows++; 
            }
            if(boardUguali==true)
            {
                count++;
            }
            
            app=app->next;
        }
        
        return count;
    }

    
}