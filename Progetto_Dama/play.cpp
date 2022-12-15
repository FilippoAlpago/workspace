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
	for(int i=0;i<7;i++)
	{
		for(int j=0;j<7;j++)
		{
			cout<<p(i,j,0)<<" ";
		}
		cout<<endl;
	}
	//Player p2(2);
	//p2=p;

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
