#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourabstract.h"
#include "connectfourplus.h"


#ifndef CONNECTFOURPLUSUNDO_H
#define CONNECTFOURPLUSUNDO_H


using namespace std;

namespace ConnectFour
{

	class ConnectFourPlusUndo : public ConnectFourPlus
	{
		public:
			ConnectFourPlusUndo();  //creates a 5*5 game
			ConnectFourPlusUndo(string filename);
			ConnectFourPlusUndo(int take_row , int  take_column);  //takes number of rows and columns
			ConnectFourPlusUndo(const ConnectFourPlusUndo& gameboard);  //copy constructor;
			~ConnectFourPlusUndo();  //destructor
		
			ConnectFourPlusUndo& operator =(const ConnectFourPlusUndo& rightSide);	//overload assignment operator
			
			 bool setPosition(string take_position);  
			 
			 
			static int returnmove();
			
			 bool playGame();
		private:
			int **undo;
			int loadTheGame(const string & filename , char sym);
			void saveTheGame(const string & filename , char sym) const;	
			int moveComputer(int loc);
			void saveMoves(int _row,int _column);
			bool play();
			bool play(string& take_input) ;
			bool undogame();
			static int movecount;
			
			bool controlWinner(int _row,int _pos);
			
		 	
	};

#endif  
}
