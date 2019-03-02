#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourplus.h"
#include "connectfourabstract.h"
#include "connectfourplusundo.h"
using namespace std;


namespace ConnectFour
{
	int ConnectFourPlusUndo::movecount=0;


	ConnectFourPlusUndo::ConnectFourPlusUndo() :ConnectFourPlus()
	{
	
	}
	ConnectFourPlusUndo::ConnectFourPlusUndo(int take_row , int  take_column) :ConnectFourPlus(take_row ,take_column)//takes number of rows and columns
	{

	}
	ConnectFourPlusUndo::ConnectFourPlusUndo(const ConnectFourPlusUndo& gameboard) :ConnectFourPlus(gameboard)  //copy constructor;
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
			
	ConnectFourPlusUndo::~ConnectFourPlusUndo() //destructor
	{
		for(int i=0;i<row*column;++i)
			delete [] undo[i];
		delete [] undo;
	}
	ConnectFourPlusUndo::ConnectFourPlusUndo(string filename)
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
	ConnectFourPlusUndo& ConnectFourPlusUndo::operator =(const ConnectFourPlusUndo& rightSide)	//overload assignment operator
	{
		if(&rightSide==this)
			return *this;
		ConnectFourPlus::operator =(rightSide);
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
	
	
	bool ConnectFourPlusUndo::setPosition(string take_position)
	{
		if(take_position[0]<'A'||take_position[0]>'Z'&&take_position.length()==1){//input is lowecase
			cerr<<"Wrong Position ! try again use UpperCase"<<endl;
			return false;
		}
		if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			cerr<<"False type! Enter position again"<<endl;
			return false;
		}
		for(int i=row-1;i>=0&&take_position.length()==1;--i){
			if(take_position.length()==1&&gameBoard[i][take_position[0]-'A'].getCell()=='*'){
				position=take_position[0];		
				return true;
			}	
			else if(i==0&&take_position.length()==1&&gameBoard[i][take_position[0]-'A'].getCell()!='*'||gameBoard[i][take_position[0]-'A'].getCell()==' '){
				cerr<<"Wrong Position ! try again use "<<endl;
				return false;
			}	
		}
		if(take_position.find("UNDO")==0){// if user's input is UNDO
			position=take_position;
			return true;
		}	
		if(take_position.length()<6&&take_position.length()>1){//if input not load or save and lenth bigger from 1
			cerr<<"Missing Input! try again"<<endl;
			return false;
		}
		if(take_position=="SAVE"||take_position=="LOAD"){//writes only LOAD or SAVE and dont write file name
			cerr<<"Wrong Input! try again"<<endl;
			return false;
		}
		if(take_position.find("LOAD")==0||take_position.find("SAVE")==0&&take_position.length()>5){
			position=take_position;
			return true;
		}	
	}
	
	bool ConnectFourPlusUndo::playGame()
	{
		bool check=false;
		symbol='O';
		int i;
		for(int i=0;i<row;++i)
			delete [] gameBoard[i];
		delete [] gameBoard;
		
		takeRow();
		takeColumn();
		pVpOrpVc();
		
		undo=new int *[row*column];//memory allocate to save moves
		for(int i=0;i<row*column;++i)
			undo[i]=new int[3];
			
			
		for(int i=0; i<row*column; ++i)
			for(int j=0; j<2; ++j)
				undo[i][j]=0;
		cin.ignore(999,'\n');
	 	gameBoard=new Cell *[row];
		for(int i=0; i<row; ++i)
			gameBoard[i] = new Cell[column];
		for(int i=0; i<row; ++i){
			for(int j=0; j<column; ++j){
				gameBoard[i][j].setCell('*');
				gameBoard[i][j].setRow(i);
				gameBoard[i][j].setColumn(j);	
			}
		}								
		displayGame();
		string strL="LOAD";
		string strS="SAVE";
		int cnt=0;
		while(!check){
			if(pvpOrpvc=='P'){
				if(check==false&&pvpOrpvc=='P'&&(cnt==0||cnt==2)){//game type is P
					symbol='X';
					cnt=0;
					position.clear();
					takePosition();
					while(true){
						while(position.find(strL)==0){//if input is load
							position.erase(0,5);//delete the Load there is only file name
							loadTheGame(position,symbol);//load the game
							position.clear();
							if(symbol=='X')
								cnt=2;
							else
								cnt=3;	
						}	
			
						while(position.find(strS)==0){//if input is save
							position.erase(0,5);
							saveTheGame(position,symbol);
							position.clear();
							takePosition();
						}
						while(position.find("UNDO")==0){
							undogame();
							displayGame();	
							position.clear();
							takePosition();
						}
					if(position.find("LOAD")!=0&&position.find("SAVE")!=0&&position.find("UNDO")!=0)
						break;	
					}	
					if(position.length()!=0)
						check=play(position);
					displayGame();
				}						
				if(check==false&&pvpOrpvc=='P'&&(cnt==0||cnt==3)){//for user 2
					symbol='O';	
					cnt=0;		
					position.clear();
					takePosition();
					while(true){
						while(position.find(strL)==0){//if input is load
							position.erase(0,5);//delete the Load there is only file name
							loadTheGame(position,symbol);//load the game
							position.clear();
							if(symbol=='X')
								cnt=2;
							else
								cnt=3;	
						}	
			
						while(position.find(strS)==0){//if input is save
							position.erase(0,5);
							saveTheGame(position,symbol);
							position.clear();
							takePosition();
						}
						while(position.find("UNDO")==0){
							undogame();
							displayGame();	
							position.clear();
							takePosition();
						}
					if(position.find("LOAD")!=0&&position.find("SAVE")!=0&&position.find("UNDO")!=0)
						break;	
					}
					if(position.length()!=0)
						check=play(position);
					displayGame();
				}
			}
			if(pvpOrpvc=='C'){//for to play computer vs user
			
				symbol='X';
				cnt=0;
				position.clear();
				takePosition();
				while(true){
					while(position.find(strL)==0){//if input is load
						position.erase(0,5);//delete the Load there is only file name
						loadTheGame(position,symbol);//load the game
						position.clear();
						if(symbol=='X')
							cnt=2;
						else
							cnt=3;	
					}	
			
					while(position.find(strS)==0){//if input is save
						position.erase(0,5);
						saveTheGame(position,symbol);
						position.clear();
						takePosition();
					}
					while(position.find("UNDO")==0){
						undogame();			
						displayGame();	
						position.clear();
						
					}
				if(position.find("LOAD")!=0&&position.find("SAVE")!=0&&position.find("UNDO")!=0)
					break;	
				}
				if(position.length()!=0)
					check=play(position);
				displayGame();
				if(check==false&&pvpOrpvc=='C'&&(cnt==0||cnt==3)){	
					symbol='O';
					check=play();
					displayGame();
					cnt=0;
					if(check==true){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}
				}	
			}		
	
		}
		return check;
	}
	bool ConnectFourPlusUndo::play(string& take_input) 
	{
		int i;
		int control=0;
			
		for(int j=0;j<row;++j){//check whether bord is full
			for(int i=0; i<column;++i)
				if(gameBoard[j][i].getCell()!='*'){
					++control;
				
			}		
		}	
		if(control==column*row-1){//if board is full
			for(i=row-1;i>=0;--i){//move the symbol legal location
			 	if(gameBoard[i][take_input[0]-'A'].getCell()=='*'){
				 	gameBoard[i][take_input[0]-'A'].setCell(symbol);
				 	saveMoves(i,take_input[0]-'A');//to save moves
			 		break;
			 	}	
			}
			controlWinner(i,take_input[0]-'A');	
			cerr<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;	
			return true;						
		}
		else{//if board has still empty legal location
			for(i=row-1;i>=0;--i){//move the symbol legal location
			 	if(gameBoard[i][take_input[0]-'A'].getCell()=='*'){
				 	gameBoard[i][take_input[0]-'A'].setCell(symbol);
				 	saveMoves(i,take_input[0]-'A');//to save moves
			 		break;
			 	}	
			}
			return controlWinner(i,take_input[0]-'A');					
		}	
		return false;		
	}
}

namespace ConnectFour
{	
	
	bool ConnectFourPlusUndo::play()
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
	
	
	int ConnectFourPlusUndo::moveComputer(int loc)
	{
		for(int i=row-1;i>=0;--i){
			if(gameBoard[i][loc].getCell()=='*'){
				gameBoard[i][loc].setCell('O');
				saveMoves(i,loc);//to undo computer move
				return 1;
			 }	
		}
		return 2;
	}
	int ConnectFourPlusUndo::loadTheGame(const string & filename , char sym)
	{
		int count=0;
		movecount=0;
		returnmove();
		ifstream loadGame;
		loadGame.open(filename.c_str());//to take file name from user
		if(loadGame.fail()){//if file name isnt appropriate exit the game
			cerr<<"Output file couldnt open"<<endl;
			exit(1);
	 	}
	 	else{
	 		for(int i=0;i<row;++i)
				delete [] gameBoard[i];
			delete [] gameBoard;
			
			for(int i=0;i<row*column;++i)
				delete [] undo[i];
			delete [] undo;	
			
				
	 		loadGame>>row
	 			>>column
	 			>>symbol
	 			>>pvpOrpvc;
	 		char game[row][column];
	 		
	 		undo=new int *[row*column];//memory allocate to save moves
			for(int i=0;i<row*column;++i)
				undo[i]=new int[3];
	 		
	 		string test;
	 		getline(loadGame,test);		
	 		for(int i=0;i<row&&getline(loadGame,test);++i)
	 			for(int k=0;k<column;++k)	
	 				game[i][k]=test[k];
	 		
	 		loadGame>>count;		
			
	 		for(int i=0;i!=count;++i){
	 			loadGame>>undo[i][0]
	 					>>undo[i][1];
	 					movecount=count;
	 		}					
	 										
	 		loadGame.close();			
	 		gameBoard=new Cell *[row];
			for(int i=0; i<row; ++i)
				gameBoard[i] = new Cell[column];
	
			for(int i=0; i<row; ++i){
				for(int j=0; j<column; ++j){
					gameBoard[i][j].setCell(game[i][j]);
					gameBoard[i][j].setRow(i);
					gameBoard[i][j].setColumn(j);	
				}
			}
															
	 		displayGame();
	 	}
	 	return 0;
	}
	void ConnectFourPlusUndo::saveTheGame(const string & filename , char sym) const
	{
	 	ofstream saveGame;
	 	saveGame.open(filename.c_str());//to take file name from user
	 	if(saveGame.fail()){//if file name isnt appropriate exit the game
	 		cerr<<"Output file couldnt open"<<endl;
	 	}
	 	else{
	 		saveGame<<row<<endl
	 			<<column<<endl
	 			<<symbol<<endl
	 			<<pvpOrpvc<<endl;
	 		for(int i=0;i<row;++i){
	 			for(int j=0;j<column;++j)
	 				saveGame<<gameBoard[i][j].getCell();	
	 			saveGame<<endl;
	 		}
	 		saveGame<<movecount<<endl;		
	 				
	 		for(int i=0;i!=movecount/2+1;++i){
	 			saveGame<<undo[i][0]<<endl
	 					<<undo[i][1]<<endl;
	 		}			
	 	}		
	 	saveGame.close();	
	}
		void ConnectFourPlusUndo::saveMoves(int _row,int _column)//save the moves
	{
		movecount+=1;
		undo[movecount-1][0]=_row;
		undo[movecount-1][1]=_column;
		
		returnmove();
	
	}
	bool ConnectFourPlusUndo::undogame()
	{
		int control=0;
		for(int j=0;j<row;++j){//check whether bord is full
			for(int i=0; i<column;++i)
				if(gameBoard[j][i].getCell()=='*'){
					++control;
				
			}		
		
		}	
		if(control==row*column){// if gameboard is empty
			cerr<<"no moves to be taken back"<<endl;
			return false;
		}
		else{
			gameBoard[undo[movecount-1][0]][undo[movecount-1][1]].setCell('*');//undo the move
			--movecount;
			returnmove();
			if(symbol=='X')//change the symbol
				symbol='O';
			else
				symbol='X';
			return true;
		}				
			
	
	}
	
	int ConnectFourPlusUndo::returnmove()
	{
		return movecount;
		
	}

	bool ConnectFourPlusUndo::controlWinner(int _row,int _pos)
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

	
	
	
