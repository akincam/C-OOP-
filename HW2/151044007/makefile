all:hw1

hw1: main.o
	g++ main.o -o exe 

main.o: main.cpp
	g++ -c main.cpp -std=c++11
	
hw1.o: hw1.cpp
	g++ -c hw1.cpp	-std=c++11	
	
clean:
	rm *.o exe
	
