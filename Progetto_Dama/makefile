play.exe: play.o player.o
		g++ --std=c++14 -c play.o player.o -o play.exe

play.o: play.cpp player.hpp
		g++ --std=c++14 -c play.cpp -o play.o

player.o: player.cpp player.hpp
		g++ --std=c++14 -c player.cpp -o player.o

		