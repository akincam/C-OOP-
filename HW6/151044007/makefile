all: hw6

hw6: main.o gtusetbase.o gtuset.o    gtumap.o
	g++ main.o gtusetbase.o gtuset.o gtumap.o   -o exe
	
main.o: main.cpp
	g++ -c main.cpp -std=c++11

gtusetbase.o: gtusetbase.cpp
	g++ -c gtusetbase.cpp -std=c++11		
	
gtuset.o: gtuset.cpp
	g++ -c gtuset.cpp -std=c++11
	
gtumap.o: gtumap.cpp
	g++ -c gtumap.cpp -std=c++11
clean:	
	rm* .o exe
