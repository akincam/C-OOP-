all: connectfourabstract

connectfourabstract: main.o connectfourabstract.o cell.o connectfourplus.o connectfourdiag.o connectfourplusundo.o
	g++ main.o connectfourabstract.o cell.o connectfourplus.o connectfourdiag.o connectfourplusundo.o -o exe

main.o: main.cpp
	g++ -c main.cpp -std=c++11

connectfourabstract.o: connectfourabstract.cpp
	g++ -c connectfourabstract.cpp -std=c++11

cell.o: cell.cpp
	g++ -c cell.cpp -std=c++11
connectfourplus.o: connectfourplus.cpp
	g++ -c connectfourplus.cpp -std=c++11
connectfourdiag.o: connectfourdiag.cpp
	g++ -c connectfourdiag.cpp -std=c++11
connectfourplusundo.o: connectfourplusundo.cpp
	g++ -c connectfourplusundo.cpp -std=c++11

clean:
	rm *.o exe
