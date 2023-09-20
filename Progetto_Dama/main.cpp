#include "player.hpp"
#include <iostream>
using namespace std;
int main(){
//arrivo ad un punto in cui non riesco a vincere-> le pedine si muovono su e giù e basta, non cercano di mangiarsi a vicenda o muoversi verso gli altri-> intervenire sulla move quando devo muovere e basta
    try{
        
        Player p1;
        Player p2(2);
        p1.init_board("1.txt");
        int cont=1;
        string s="1.txt";
        
        do{
            p1.load_board(s);
             cout<<s<<"   ";
            p1.move();
            cout<<"p1 dopo move"<<endl;
            
            cout<<endl;
           
            
            if(p1.valid_move()==true)
            {
                cout<<" mossa valida"<<endl;
            }
            else
            {
                cout<<"mossa invalida!!!!!!"<<endl;
            }
            cont++;
            s=to_string(cont)+".txt";
            cout<<"p1 carico la mossa su "<<s<<endl;
            p1.store_board(s);
            cout<<endl;
            if(!p1.wins()){
                cout<<"carico la board su P2"<<endl;
                p2.load_board(s);
                cout<<s<<"   ";
                p2.move();
                cout<<"p2 dopo move"<<endl;
                
                cout<<endl;
                
                //cout<<p2.valid_move()<<endl;
                if(p2.valid_move()==true)
            {
                cout<<" mossa valida"<<endl;
            }
            else
            {
                cout<<"mossa invalida!!!!!!"<<endl;
            }
                cont++;
                s=to_string(cont)+".txt";
                cout<<"P2 carico la board su"<<s<<endl;
                p2.store_board(s);
            }
        }while(cont<100 && !p1.wins() && !p2.wins());

        /*Player p1(2);
        Player p2(2);
        p1.load_board("1.txt");
        p1.move();
        cout<<p1.valid_move()<<endl;
        p1.store_board("2.txt");*/
    }catch(player_exception e)
    {
        cout<<e.msg<<endl;
    }
    return 0;
}