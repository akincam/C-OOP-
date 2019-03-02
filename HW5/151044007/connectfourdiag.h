#ifndef CONNECTFOURDIAG_H
#define CONNECTFOURDIAG_H

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourabstract.h"
using namespace std;

namespace ConnectFour
{

	class ConnectFourDiag :public ConnectFourAbstract
	{
		public:
			ConnectFourDiag();  //creates a 5*5 game
			ConnectFourDiag(string filename);
			ConnectFourDiag(int take_row , int  take_column);  //takes number of rows and columns
			ConnectFourDiag(const ConnectFourDiag& gameboard);  //copy constructor;
			~ConnectFourDiag();  //destructor
		
			ConnectFourDiag& operator =(const ConnectFourDiag& rightSide);	//overload assignment operator
			
			
		
		private:

     		bool play();
			bool controlWinner(int _row, int _pos);
		  
	};


}
#endif 
