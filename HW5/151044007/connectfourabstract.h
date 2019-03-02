#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"

#ifndef CONNECTFOURABSTRACT_H
#define CONNECTFOURABSTRACT_H

namespace ConnectFour
{
	class ConnectFourAbstract
	{
		public:
			ConnectFourAbstract();  //creates a 5*5 game
			ConnectFourAbstract(string filename);
			ConnectFourAbstract(int take_row , int  take_column);  //takes number of rows and columns
			ConnectFourAbstract(const ConnectFourAbstract& gameboard);  //copy constructor;
			~ConnectFourAbstract();  //destructor
		
			bool setGameRow(int input);  //set the row from taken inputs
			bool setGameColumn(int input); 	//set the column from taken inputs
			bool setPVPorPVC(char gametype); //set the gametype p or c from taken input	
			virtual bool setPosition(string take_position);  //set whether the position is illegal from taken position
		
			inline int getGameRow() const {return row;}	
			inline int getGameColumn() const {return column;}	
			inline char getPVPorPVC() const {return pvpOrpvc;}	
			inline string getPosition() const {return position;}
			
			void pVpOrpVc(); //to choose game type
		
			bool playGame(); 	
	
			ConnectFourAbstract& operator =(const ConnectFourAbstract& rightSide);	//overload assignment operator

		protected:
			int row;
			int column;
			char pvpOrpvc;
			char symbol;
			string position;
			Cell **gameBoard;
		
			void takePosition();   //take position from user
			void displayGame() const;
			virtual int moveComputer(int loc);	 //move computer input
			
		 	virtual bool play();
		 	virtual bool play(string& take_input) ;
		 	
		 	const void takeRow();
			const void takeColumn();
		
		 	virtual int loadTheGame(const string & filename , char sym);
			virtual void saveTheGame(const string & filename , char sym) const;	
		 	
		 	virtual bool controlWinner(int _row,int _pos);
		 	
		 	 const int check_LF(int pos_row,int pos_col) const; //controls the game from left to right for single mod
		 	 const int check_UD(int pos_row,int pos_col) const; ///controls the game from up to down for single mod
		     const int check_RD(int pos_row,int pos_col) const; ///controls the game rightdia for single mod
		 	 const int check_LD(int pos_row,int pos_col) const; ///controls the game  leftdia for single mod
		 	 	
		 	 const int comp_LF() const; //controls the game from left to right for computer to complete 4 symbol
		 	 const int comp_UD() const; //controls the game from up to down for computer to complete 4 symbol
		 	 const int comp_RD() const; //controls the game rightdia for computer to complete 4 symbol
		 	 const int comp_LD() const; //controls the game leftdia for computer to complete 4 symbol
		 	
		 	 const int compAttack_LF() const; //to complete 3 left to right for computer
		 	 const int compAttack_UD() const;
		 	 const int compAttack_RD() const;
		 	 const int compAttack_LD() const;
		 	
		 	 const int compB_LF() const;//check a gap between 3 symbol left to right
		 	 const int compB_RD() const;//check a gap between 3 symbol rightdia
		 	 const int compB_LD() const;//check a gap between 3 symbol leftdia     
		 	 
		 	
	};
	

}
#endif 


