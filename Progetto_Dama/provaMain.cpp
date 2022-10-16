#include "player.cpp"
#include"player.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
using namespace std;
int main()
{
    int Player_nr;
    cout<<"inserisci player";
    cin>>Player_nr;
    Player P1(Player_nr);
    
    return 0;
}