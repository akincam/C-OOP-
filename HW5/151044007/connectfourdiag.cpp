#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourdiag.h"
#include "connectfourabstract.h"
using namespace std;


namespace ConnectFour
{
	ConnectFourDiag::ConnectFourDiag() :ConnectFourAbstract()
	{
		//deliberately empty
	}
	ConnectFourDiag::ConnectFourDiag(int take_row , int  take_column) :ConnectFourAbstract(take_row ,take_column) //takes number of rows and columns
	{
		//deliberately empty
	}
	ConnectFourDiag::ConnectFourDiag(const ConnectFourDiag& gameboard)   //copy constructor;
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
			
	ConnectFourDiag::~ConnectFourDiag()  //destructor
	{
		//empty
	}
	ConnectFourDiag::ConnectFourDiag(string filename)
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
	ConnectFourDiag& ConnectFourDiag::operator =(const ConnectFourDiag& rightSide)	//overload assignment operator
	{
		if(&rightSide==this)
			return *this;
		ConnectFourAbstract::operator =(rightSide);//abstract assignment operator
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
	bool ConnectFourDiag::controlWinner(int _row,int _pos)
	{
		if(check_LD(_row,_pos)>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_RD(_row,_pos)>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		return false;						
	}		
	
	bool ConnectFourDiag::play()
	{
		symbol='O';//control and if the game end return true
			if(comp_LD()!=2017){
				moveComputer(comp_LD());
	
					return true;
			}	
			if(comp_RD()!=2017){
				moveComputer(comp_RD());
			
					return true;
			}		
			if(compB_LD()!=2017){
				moveComputer(compB_LD());
				
					return true;
			}	
			if(compB_RD()!=2017){
				moveComputer(compB_RD());
			
					return true;	
			}
				
			symbol='X';//to prevent users's win the game
			if(comp_LD()!=2017){
				moveComputer(comp_LD());
				return false;
			}	
			if(comp_RD()!=2017){
				moveComputer(comp_RD());
				return false;
			}		
			if(compB_LD()!=2017){
				moveComputer(compB_LD());
				return false;
			}	
			if(compB_RD()!=2017){
				moveComputer(compB_RD());
				return false;	
			}		
	
		symbol='O';//to complete 3 for computer				
		if(compAttack_RD()!=2017){
			moveComputer(compAttack_RD());
			return false;
		}	
		else if(compAttack_LD()!=2017){
			moveComputer(compAttack_LD());
			return false;
		}	
		//to complete 2
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(gameBoard[i][j].getCell()==symbol){
					if(j+1<column&&i+1<row&&gameBoard[i+1][j+1].getCell()!='*'&&gameBoard[i][j+1].getCell()=='*'){
						moveComputer(j+1);
						return false;
					}	
					else if(j+1<column&&i-1>=0&&gameBoard[i-1][j+1].getCell()=='*'&&gameBoard[i-1][j].getCell()!='*'){
						moveComputer(j+1);
						return false;
					}
					else if(i+1<row&&j-1>=0&&gameBoard[i+1][j-1].getCell()=='*'){
						moveComputer(j-1);
						return false;
					}
					else if(i-1>=0&&j-1>=0&&gameBoard[i-1][j-1].getCell()=='*'&&gameBoard[i][j-1].getCell()!='*'){
						moveComputer(j-1);
						return false;
					}	
							
				}
			}
		}
		//for first move or other legal moves from column 2
		for(int i=row-1;i>=0&&column>=2;--i){
			for(int j=2;j<column;++j){				
				if(gameBoard[i][j].getCell()=='*'){
					moveComputer(j);
					return false;
				}
			}
		}//for first move or other legal moves from column 0
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

				
