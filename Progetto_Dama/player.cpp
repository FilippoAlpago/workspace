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
                string str="c="+to_string(c) +", colonna non esistente";
                throw player_exception{player_exception::index_out_of_bounds,str};
            }
        }
        else
        {
            string str="r="+to_string(r) +", riga non esistente";
            throw player_exception{player_exception::index_out_of_bounds,str};
        }
    }
    
}

void Player::load_board(const std::string& filename)
{
    /*
        1) controllare se formato file corretto .txt
        2) vedere se file si è aperto corretamente
        3) leggere riga per riga, elimnare spazi in eccesso e controlare che la board sia valida; numero pedine giusto, lunghezza riga==15, pedine su posizione correta{riga P colonna P, riga D colonna D}
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
            mossa* app=this->pimpl->history;
            if(app!=nullptr)
            {
                while (app->next!=nullptr)
                {
                    app=app->next;
                }
                        
            }
            app=new mossa;//creo la nuova 'mossa'
            while(getline(Myfile,riga)&&rigaApposto==true)
            {//ad ogni riga letta, prima la "pulisco" dagli spazi in eccesso
                if(riga.length()!=15)
                {
                    rigaApposto=false;
                }
                else
                {//modifico e aggiungo riga alla mia board
                    sistemaRiga(riga);//pulisci riga
                    
                    for(int i=0;i<riga.length();i++)
                    {
                        app->Campo_gioco[rows][cools]=CharToPiece(riga.at(i));
                        cools++;
                    }
                    rows++;
                    cools=0;
                }
                
            }
            //dopo aver finito di aggiungere alla mia board, controllo numero pedine e dame(0<=Ped+Dame<=12) e la loro posizione

            if(rigaApposto==false)
            {
                string str="il file "+filename+" contiene una riga non valida";
                throw player_exception{player_exception::invalid_board,str};
            }

            Myfile.close();
        }
        else
        {//erroe nell'apertura del file
            string str="errore nell'apertura di "+filename+", probabilmente il file non esiste";
            throw player_exception{player_exception::missing_file,str};
        }
   }
   else
   {
        string str="filename "+filename+" non ha un estensione corretta";
        throw player_exception{player_exception::missing_file,str};
   }
}

bool boardApposto(Player::piece board[8][8]);//mi serve per load_board e valid_move; verifica se la board è valida, numero pedine giusto e al proprio posto

Player::piece CharToPiece(char c )
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
void sistemaRiga(string& rigaDasistemare)//metodo che elimina spazi in eccesso
{//assunto il formato che la riga deve avere sul file
    int i=1,countSpaziEliminati=0;
    while(i<8)
    {
        if(i+countSpaziEliminati%2!=0)//se la somma dei 2 è dispari allora in quella posizione i vi è sicuramente un spazio in eccesso da eliminare
        {
            rigaDasistemare.erase(i);
            countSpaziEliminati++;
        }
        i++;
    }  
}

void Player::store_board(const std::string& filename, int history_offset) const
{
    int NumBoard=countBoard(this->pimpl->history);
    if(NumBoard<history_offset||history_offset<0||NumBoard==0)
    {
        string str="history numero"+to_string(history_offset) +"non esistente";
        throw player_exception{player_exception::index_out_of_bounds,str};
    }
    else
    {
        ofstream Myfile(filename);
        int counter=NumBoard-history_offset;
        int i=0;
        mossa* app=this->pimpl->history;
        while(i!=counter)
        {
            app=app->next;
            i++;
        }
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {//se ritorna e devo scrivere " "
                if(to_string(app->Campo_gioco[i][j])!="e")
                {
                    Myfile<<to_string(app->Campo_gioco[i][j]);
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
                            Myfile<<"o"<<"\n";
                            
                        }
                        else
                        {
                            Myfile<<"o"<<" ";
                        }
                        
                    }
                    else
                    {//sono nel campo di player 1
                        
                        if(j==7)
                        {
                            if(i==7)
                            {//ultima riga e colonna
                                Myfile<<"x";
                            }
                            else
                            {
                                Myfile<<"x"<<"\n";
                            }
                               
                        }
                        else
                        {
                            Myfile<<"x"<<" ";
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
        {//ultima hystory
            app=app->next;
        }
        piece pedinaDaMuovere,DamaDaMuovere;
        if(this->pimpl->Player_Number==1)
        {
            pedinaDaMuovere=x;
            DamaDaMuovere=X;
        }
        else
        {
            pedinaDaMuovere=o;
            DamaDaMuovere=O;
        }
        /*x sposto con --di riga e ++ di colonna oppure -- di riga e -- colonna; 
          o sposrto con ++ riga e ++ colonna oppure -- colonna e ++ riga
          Dame si possono muovere in qualsiasi direzione
        1) scelgo a caso una pedina fra le mie(genero 2 cordinate e cerco in quella posizione) e la muovo(scelgo a caso la mossa??????)
        2) se posso mangiare mangio
        3) se se arriva a riga=0 allora diventa Dama
        */

        int max=7,min=0,range=max-min+1;
        int rows=rand()%range+min, cools=rand()%range+min;
        while(app->Campo_gioco[rows][cools]!=pedinaDaMuovere||app->Campo_gioco[rows][cools]!=DamaDaMuovere)
        {//continuo a 'ceracare' finchè non ho trovato una mia pedina/dama
            rows=rand()%range+min;
            cools=rand()%range+min;
        }

        //muovere, prima controllo se posso mangiare(difficile, controllare se adicente c'è una pedina e vedere se nella diagonale dopo c'e uno spazio libero)
        
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
        if((player_nr==1&&player_nr==this->pimpl->Player_Number)||(player_nr==2&&player_nr==this->pimpl->Player_Number))
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