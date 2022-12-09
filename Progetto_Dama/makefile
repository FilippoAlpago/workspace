play.exe: player.o play.o
		g++ -std=c++14 player.o play.o -o play.exe

player.o: player.cpp player.hpp
		g++ -std=c++14 -c player.cpp -oplayer.o

play.o: play.cpp player.hpp
		g++ -std=c++14 -c play.cpp -oplay.o
 

		