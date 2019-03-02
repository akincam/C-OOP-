#ifndef CONNECTFOURPLUS_H
#define CONNECTFOURPLUS_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourabstract.h"

using namespace std;


namespace ConnectFour
{

	class ConnectFourPlus : public ConnectFourAbstract
	{
		public:
			ConnectFourPlus();  //creates a 5*5 game
			ConnectFourPlus(string filename);
			ConnectFourPlus(int take_row , int  take_column);  //takes number of rows and columns
			ConnectFourPlus(const ConnectFourPlus& gameboard);  //copy constructor;
			~ConnectFourPlus();  //destructor
		
			ConnectFourPlus& operator =(const ConnectFourPlus& rightSide);	//overload assignment operator
			

		protected:		
			bool play();
			bool controlWinner(int _row,int _pos);
	};

 
}
#endif 		
