#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourplus.h"
#include "connectfourabstract.h"
using namespace std;


namespace ConnectFour
{

	ConnectFourPlus::ConnectFourPlus() :ConnectFourAbstract()
	{
	
	}
	ConnectFourPlus::ConnectFourPlus(int take_row , int  take_column) :ConnectFourAbstract(take_row ,take_column)//takes number of rows and columns
	{

	}
	ConnectFourPlus::ConnectFourPlus(const ConnectFourPlus& gameboard) :ConnectFourAbstract(gameboard)  //copy constructor;
	{
		row=gameboard.getGameRow();
		column=gameboard.getGameColumn();
		gameBoard=new Cell*[row];
		for(int i=0; i<row; ++i)
			gameBoard[i] = new Cell[column];
		for(int i=0; i<row; ++i){
			for(int j=0; j<column; ++j){
				gameBoard[i][j]=gameboard.gameBoard[i][j];
				gameBoard[i][j].setRow(i);
				gameBoard[i][j].setColumn(j);	
			}
		}	
	}
			
	ConnectFourPlus::~ConnectFourPlus() //destructor
	{

		//empty
	}
	ConnectFourPlus::ConnectFourPlus(string filename)
	{
		ifstream loadGame;
		int i;
		cin.ignore(256,'\n');
		loadGame.open(filename.c_str());//to take file name from user
		if(loadGame.fail()){//if file name isnt appropriate exit the game
			cerr<<"Output file couldnt open"<<endl;
			exit(1);
	 	}
	 	else{
	 		string test;
	 		for(i=0;getline(loadGame,test);++i);//find the gameboard row
	 		row=i;
	 		loadGame.close();
	 		loadGame.open(filename.c_str());
	 		
	 		for(int i=0;!(loadGame.eof());++i){//find the gameboard column
	 			getline(loadGame,test);
	 			if(i==row-1){
	 				column=test.length();
	 				break;
	 			}
	 		}
	 		loadGame.close();
	 		char**game;
	 		game=new char *[row];
			for(int i=0; i<row; ++i)
				game[i] = new char[column];
	 		loadGame.open(filename.c_str());//read the board from file	
	 		for(i=0;getline(loadGame,test);++i)
	 				for(int k=0;k<column;++k)	
	 					game[i][k]=test[k];					
	 		loadGame.close();			
	 		gameBoard=new Cell *[row];
			for(int i=0; i<row; ++i)
				gameBoard[i] = new Cell[column];
	
			for(int i=0; i<row; ++i){//assigns board from game to gameBoard
				for(int j=0; j<column; ++j){
					gameBoard[i][j].setCell(game[i][j]);
					gameBoard[i][j].setRow(i);
					gameBoard[i][j].setColumn(j);	
				}
			}								
	 	}

	}
	ConnectFourPlus& ConnectFourPlus::operator =(const ConnectFourPlus& rightSide)	//overload assignment operator
	{
		if(&rightSide==this)
			return *this;
		ConnectFourAbstract::operator =(rightSide);
		if(row!=rightSide.row || column!=rightSide.column)
		{
			for(int i=0;i<row;++i)
				delete [] this->gameBoard[i];
			delete [] gameBoard;
			gameBoard = new Cell*[rightSide.row];
		
			for(int i=0; i<rightSide.row; ++i)
				gameBoard[i] = new Cell[rightSide.column];
			for(int i=0; i<rightSide.row; ++i){
				for(int j=0; j<rightSide.column; ++j){
					gameBoard[i][j].setRow(i);
					gameBoard[i][j].setColumn(j);
					gameBoard[i][j].setCell('*');
				}
			}										
		}
		row=rightSide.row;
		column=rightSide.column;
		for(int i=0; i<row; ++i){
			for(int j=0; j<column; ++j){
				gameBoard[i][j].setRow(i);
				gameBoard[i][j].setColumn(j);
				gameBoard[i][j].setCell(rightSide.gameBoard[i][j].getCell());
			}
		}							
		return *this;			
	}			
			
			
	bool ConnectFourPlus::play()
	{
		symbol='O';//control and if the game end return true
			if(comp_LF()!=2017){
				moveComputer(comp_LF());
		
					return true;	
			}
			if(comp_UD()!=2017){
				moveComputer(comp_UD());
			
					return true;
			}		
			if(compB_LF()!=2017){
				moveComputer(compB_LF());
				
					return true;
			}			
			symbol='X';//to prevent users's win the game
			if(comp_LF()!=2017){
				moveComputer(comp_LF());
				return false;	
			}
			if(comp_UD()!=2017){
				moveComputer(comp_UD());
				return false;
			}	
			if(compB_LF()!=2017){
				moveComputer(compB_LF());
				return false;
			}	
		symbol='O';//to complete 3 for computer		
		if(compAttack_UD()!=2017){
			moveComputer(compAttack_UD());
			return false;
		}	
		else if(compAttack_LF()!=2017){
			moveComputer(compAttack_LF());
			return false;
		}		
		//to complete 2
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(gameBoard[i][j].getCell()=='O'){
					if(j+1<column&&i+1<row&&gameBoard[i+1][j+1].getCell()!='*'&&gameBoard[i][j+1].getCell()=='*'){
						moveComputer(j+1);		
						return false;
					}	
					else if(j-1>=0&&i+1<row&&gameBoard[i+1][j-1].getCell()!='*'&&gameBoard[i][j-1].getCell()=='*'){	
						moveComputer(j-1);
						return false;
					}	
				}			
			}
		}

		int counter=0;
		for(int i=0;i<column;++i){
			for(int j=0;j<row;++j){
				if(j-1>=0&&gameBoard[j][i].getCell()=='O'&&gameBoard[j-1][i].getCell()=='*'){
					++counter;
					if(counter>=1){
						moveComputer(i);
						return false;
					}			
				}
				else
					counter=0;	
			}
		}
		//for first move or other legal moves
		for(int i=row-1;i>=0&&column>=2;--i){
			for(int j=2;j<column;++j){				
				if(gameBoard[i][j].getCell()=='*'){
					moveComputer(j);
					return false;
				}
			}
		}
		for(int i=row-1;i>=0;--i){
			for(int j=0;j<column;++j){				
				if(gameBoard[i][j].getCell()=='*'){
					moveComputer(j);
					return false;
				}
			}
		}			
	}
}
namespace ConnectFour
{
	bool ConnectFourPlus::controlWinner(int _row,int _pos)
	{
		if(check_LF(_row,_pos)>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_UD(_row,_pos)>=4){	
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		return false;						
	}
		
}					
