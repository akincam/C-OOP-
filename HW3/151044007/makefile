all:hw5

hw5: main.o
	g++ main.o -o exe 

main.o: main.cpp
	g++ -c main.cpp -std=c++11
	
hw5.o: hw5.cpp
	g++ -c hw5.cpp	-std=c++11	
	
clean:
	rm *.o exe
	
