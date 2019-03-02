all:hw4

hw4: main.o
	g++ main.o -o exe 

main.o: main.cpp
	g++ -c main.cpp -std=c++11
	
hw5.o: hw4.cpp
	g++ -c hw4.cpp	-std=c++11	
	
clean:
	rm *.o exe
	
