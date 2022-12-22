#include "player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::string;

int main(int argc, char **argv){
	
	int player_nr ;
	cin>>player_nr;
	
	Player p(player_nr);//decido il player
	cout << "Playing as player " << player_nr << endl;
	string board_name ="board_0.txt";
	p.init_board(board_name);
	cout<<"ho inizializzato la board "<<board_name<<endl;
	cout<<"ora carico la board "<<board_name<<endl;
	p.load_board(board_name); 
	cout<<"ho fatto la load board \n";

	cout<<"qui sotto stampo quello che ho appena caricato con load_board() \n";
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<p(i,j,0);
		}
		cout<<endl;
	}
	cout<<"carico la board_2"<<endl;
	p.load_board("board_2.txt");
	p.store_board("board_3.txt",0);
	cout<<"carico la board_3"<<endl;
	p.load_board("board_3.txt");
	
	cout<<"carico la board senza o"<<endl;
	p.load_board("board_4.txt");
	/*Player p2(2);
	p2=p;
	cout<<"ora stampo p2 \n";
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			cout<<p2(i,j,0);
		}
		cout<<endl;
	}
	cout<<"ora carico board 2"<<endl;
	p.load_board("board_2.txt");
	cout<<"ora stampo board_1 \n";
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			cout<<p(i,j,1);
		}
		cout<<endl;
	}
	cout<<"qui sotto stampo quello che ho appena caricato con load_board() \n";
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			cout<<p(i,j,0);
		}
		cout<<endl;
	}
	p.store_board("board_3.txt",0);
	p.load_board("board_3.txt");
	cout<<"ora carico board 3"<<endl;
	p2=p;
	cout<<"ora ristampo  p2 \n";
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			cout<<p2(i,j,0);
		}
		cout<<endl;
	}*/
	cout<<" vedo se ho vinto"<<endl;
	if(p.wins()==true)
	{
		cout<<"ho vinto \n";
	}
	else
	{
		cout<<"non ho vinto"<<endl;
	}
	
	cout<<" vedo se ho perso"<<endl;
	if(p.loses()==true)
	{
		cout<<"ho perso \n";
	}
	else
	{
		cout<<"non ho perso"<<endl;
	}
	cout<<"testo l'altro wins"<<endl;
	if(p.wins(2)==true)
	{
		cout<<"player 2 ha vinto ed io ho perso"<<endl;
	}
	else
	{
		cout<<" player 2 non ha vinto mentre io non ho perso "<<endl;
	}

	if(p.wins(1)==true)
	{
		cout<<"io ho vinto"<<endl;
	}
	else
	{
		cout<<"io non ho vinto"<<endl;
	}

	cout<<"testo l'altro loses"<<endl;
	if(p.loses(2)==true)
	{
		cout<<"player 2 ha perso ed io ho vinto"<<endl;
	}
	else
	{
		cout<<" player 2 non ha perso mentre io non ho vinto "<<endl;
	}

	if(p.loses(1)==true)
	{
		cout<<"io ho perso"<<endl;
	}
	else
	{
		cout<<"io non ho perso"<<endl;
	}
	cout<<"ora faccio la pop dell'ultima scahcchiera"<<endl;
	//p.pop();
	cout<<"ho fatto la pop"<<endl;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			cout<<p(i,j,0);
		}
		cout<<endl;
	}
	cout<<"ora muovo"<<endl;
	p.move();
	cout<<"ho mosso"<<endl;
	/*int round = player_nr; // 1 or 2
		
	while(true){
		
		string board_name =  "board_" + std::to_string(round) + ".txt";
		ifstream infile(board_name);//apro il file
		
		if(infile.good()){
		
			cout << "Reading board " << board_name << endl;
		
			infile.close();
			std::this_thread::sleep_for (std::chrono::milliseconds(100));
			
			p.load_board(board_name);//leggo la board da file e la carico sulla hystory
			p.move();//muovo
			board_name =  "board_" + std::to_string(++round) + ".txt";
			p.store_board(board_name);//salvo la board su un file
			round++;
			
		}
		
	}*/
	return 0;
	
}
