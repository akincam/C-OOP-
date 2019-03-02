#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourabstract.h"
using namespace std;

namespace ConnectFour
{
	ConnectFourAbstract::ConnectFourAbstract()
		: row(5) , column(5)
	{
		gameBoard=new Cell *[5];
	
		for(int i=0; i<row; ++i)
			gameBoard[i] = new Cell[5];
		
		for(int i=0; i<row; ++i){
			for(int j=0; j<column; ++j){
				gameBoard[i][j].setCell('*');
				gameBoard[i][j].setRow(i);
				gameBoard[i][j].setColumn(j);	
			}
		}								
	}

	ConnectFourAbstract::ConnectFourAbstract(const ConnectFourAbstract& gameboard)//copy constructor	
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
	ConnectFourAbstract::ConnectFourAbstract(string filename)
	{
		ifstream loadGame;
		int i=0;
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
	 		
	 		for(i=0;!(loadGame.eof());++i){//find the gameboard column
	 			getline(loadGame,test);
	 			if(i==row-1){
	 				column=test.length();
	 				break;
	 			}
	 		}
	 		loadGame.close();
	 		char**game;
	 		game=new char *[row];
			for(i=0; i<row; ++i)
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
	ConnectFourAbstract::ConnectFourAbstract(int take_row , int  take_column)//takes row and column allocate memory 
	{
		gameBoard=new Cell *[take_row];
	
		for(int i=0; i<row; ++i)
			gameBoard[i] = new Cell[take_column];
		
	
		for(int i=0; i<row; ++i){
			for(int j=0; j<column; ++j){
				gameBoard[i][j].setCell('*');
				gameBoard[i][j].setRow(i);
				gameBoard[i][j].setColumn(j);	
			}
		}								
	}
	ConnectFourAbstract& ConnectFourAbstract::operator =(const ConnectFourAbstract& rightSide)
	{
		if(&rightSide==this)
			return *this;
		
		if(row!=rightSide.row || column!=rightSide.column)
		{
			for(int i=0;i<row;++i)
				delete [] gameBoard[i];
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
	ConnectFourAbstract::~ConnectFourAbstract()//destructor
	{
		
		for(int i=0;i<row;++i)
			delete []  this->gameBoard[i];
		delete [] gameBoard;
	}

	bool ConnectFourAbstract::setGameRow(int input)//if row is legal
	{
		if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			cerr<<"False type! Enter row again"<<endl;
			return false;
		}		
		else if(input>=4&&input<=100){
			row=input;
			return true;
		}			
		else{
			cerr<<"False input! Enter row again between 4 and 100"<<endl;
			return false;
		}	
	}

	bool ConnectFourAbstract::setGameColumn(int input)
	{
		if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			cerr<<"False type! Enter row again"<<endl;
			return false;
		}		
		else if(input>=0&&input<=26){
			column=input;
			return true;
		}
		else{
			cerr<<"False input! Enter column again"<<endl;
			return false;
		}
	}		
	bool ConnectFourAbstract::setPVPorPVC(char gametype)//determine gametype
	{
		if(gametype>='a'&&gametype<='z'){
			cerr<<"Use UpperCase! try again"<<endl;
			return false;
		}	
		else if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			cerr<<"False type! Enter  again"<<endl;
			return false;
		}
		else if(gametype!='P'&&gametype!='C'){
			cerr<<"Wrong input! enter again"<<endl;
			return false;
		}
		else{
			pvpOrpvc=gametype;
			return true;
		}				

	}
	bool ConnectFourAbstract::setPosition(string take_position)
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
	const void ConnectFourAbstract::takeRow()
	{
		bool check=false;
		int row1=0;	
		while(!check){
			cout<<endl<<endl<<"Enter row---->";
			cin>>row1;   
			cout<<endl;
			check=setGameRow(row1);
		}
				
	}	

	const void ConnectFourAbstract::takeColumn()
	{
		bool check=false;
		int column1=0;
		while(!check){
			cout<<endl<<endl<<"Enter column---->";
			cin>>column1; 
			cout<<endl;		
			check=setGameColumn(column1);
		}			
	}

	void ConnectFourAbstract::pVpOrpVc()
	{
		bool check=false;
		char gameChoice;
		while(!check){
			cout<<endl<<endl<<"Press 'P' for PvP......Press 'C' for PvC ->>>";
			cin>>gameChoice;
			check=setPVPorPVC(gameChoice);
		}	
	}
	void ConnectFourAbstract::takePosition() 
	{
		bool check1=false;
		string user_input;
		while(!check1){
			user_input.clear();
			cout<<"User "  <<symbol<<"  Enter a position  or (load or save)--->";	
			getline(cin ,user_input);
			if(cin.eof())
				exit(1);
			check1=setPosition(user_input);	
		}	
	}
	void ConnectFourAbstract::displayGame() const
	{
		char letter='A';
		cout<<endl;
		int i ; int j;
		for(i=0;i<column;++i){
			cout<<letter<<" ";
			++letter;
		}		
		cout<<endl;
		for(i=0;i<row;++i){
			for(j=0;j<column;++j)
				cout<<gameBoard[i][j].getCell()<<" ";
			cout<<endl;	
		}
	}
	bool ConnectFourAbstract::play(string& take_input) 
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
			 		break;
			 	}	
			}
			cerr<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;	
			controlWinner(i,take_input[0]-'A');	
				
			return true;						
		}
		else{//if board has still empty legal location
			for(i=row-1;i>=0;--i){//move the symbol legal location
			 	if(gameBoard[i][take_input[0]-'A'].getCell()=='*'){
				 	gameBoard[i][take_input[0]-'A'].setCell(symbol);
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
	bool ConnectFourAbstract::controlWinner(int _row,int _pos)
	{
		if(check_LF(_row,_pos)>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_UD(_row,_pos)>=4){	
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_LD(_row,_pos)>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_RD(_row,_pos)>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		return false;						
	}

}

namespace ConnectFour
{	
	bool ConnectFourAbstract::play()
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
			if(comp_LD()!=2017){
				moveComputer(comp_LD());
					return true;
			}	
			if(comp_RD()!=2017){
				moveComputer(comp_RD());
					return true;
			}	
			if(compB_LF()!=2017){
				moveComputer(compB_LF());
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
			if(comp_LF()!=2017){
				moveComputer(comp_LF());
				return false;	
			}
			if(comp_UD()!=2017){
				moveComputer(comp_UD());
				return false;
			}
			if(comp_LD()!=2017){
				moveComputer(comp_LD());
				return false;
			}	
			if(comp_RD()!=2017){
				moveComputer(comp_RD());
				return false;
			}	
			if(compB_LF()!=2017){
				moveComputer(compB_LF());
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
		if(compAttack_UD()!=2017){
			moveComputer(compAttack_UD());
			return false;
		}	
		else if(compAttack_LF()!=2017){
			moveComputer(compAttack_LF());
			return false;
		}	
		else if(compAttack_RD()!=2017){
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
	bool ConnectFourAbstract::playGame()
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
					while(position.find(strL)==0){//if input is load
						position.erase(0,5);//delete the Load there is only file name
						loadTheGame(position,symbol);//load the game
						if(symbol=='X')
							cnt=2;
						else
							cnt=3;	
						position.clear();
					}	
			
					while(position.find(strS)==0){//if input is save
						position.erase(0,5);
						saveTheGame(position,symbol);
						position.clear();
						takePosition();

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
					if(position.length()!=0)
						check=play(position);
					displayGame();
				if(check==false&&pvpOrpvc=='C'&&symbol!='O'&&(cnt==0||cnt==3)){	
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
	int ConnectFourAbstract::loadTheGame(const string & filename , char sym)
	{
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
	 		loadGame>>row
	 			>>column
	 			>>symbol
	 			>>pvpOrpvc;
	 		char game[row][column];
	 		string test;
	 		getline(loadGame,test);		
	 		for(int i=0;getline(loadGame,test);++i)
	 				for(int k=0;k<column;++k)	
	 					game[i][k]=test[k];					
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
}

namespace ConnectFour
{	
	void ConnectFourAbstract::saveTheGame(const string & filename , char sym) const
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
	 	}		
	 	saveGame.close();	
	}
	const int ConnectFourAbstract::check_UD(int pos_row,int pos_col) const
	{
		int counter=0;
		for(int i=pos_row;i<row;++i){
			if(gameBoard[i][pos_col].getCell()==symbol){
				++counter;
				if(counter>=4)
					for(int i=pos_row;i<row;++i)
						gameBoard[i][pos_col].setCell(tolower(symbol));
				}		
			else
				break;	
		}	
		return counter;
	}
	const int ConnectFourAbstract::check_LF(int pos_row,int pos_col) const
	{
		int counter=0;
		for(int i=pos_col;i>=0;--i){
			if(gameBoard[pos_row][i].getCell()==symbol)
				++counter;
			else
				break;
		}				
		for(int i=pos_col+1;i<column;++i){
			if(gameBoard[pos_row][i].getCell()==symbol)
				++counter;
			else
				break;
		}
		if(counter>=4){
			for(int i=pos_col;i>=0;--i){
				if(gameBoard[pos_row][i].getCell()==symbol)
					gameBoard[pos_row][i].setCell(tolower(symbol));
				else
					break;
		}				
			for(int i=pos_col+1;i<column;++i){
				if(gameBoard[pos_row][i].getCell()==symbol)
					gameBoard[pos_row][i].setCell(tolower(symbol));
				else
					break;
			}	
	
	
		}							
		return counter;
	}
	const int ConnectFourAbstract::check_RD(int pos_row,int pos_col) const
	{
		int counter=0;
		for(int i=pos_row, j=pos_col;i>=0&&j<column;--i,++j){
			if(i>=0&&j<column&&gameBoard[i][j].getCell()==symbol)
				++counter;
			else
				break;
		}			
		for(int i=pos_row+1, j=pos_col-1;i<row&&j>=0;++i,--j){
			if(i<row&&j>=0&&gameBoard[i][j].getCell()==symbol)
				++counter;
			else
				break;
		}
		if(counter>=4){
			for(int i=pos_row, j=pos_col;i>=0&&j<column;--i,++j){
				if(i>=0&&j<column&&gameBoard[i][j].getCell()==symbol)
					gameBoard[i][j].setCell(tolower(symbol));
				else
					break;
			}			
			for(int i=pos_row+1, j=pos_col-1;i<row&&j>=0;++i,--j){
				if(i<row&&j>=0&&gameBoard[i][j].getCell()==symbol)
					gameBoard[i][j].setCell(tolower(symbol));
				else
					break;
			}	
	
	
		}				
		return counter;
	}
	
	const int ConnectFourAbstract::check_LD(int pos_row,int pos_col) const
	{
		int counter=0;
		for(int i=pos_row, j=pos_col;i>=0&&j>=0;--i,--j){
			if(i>=0&&j>=0&&gameBoard[i][j].getCell()==symbol)
				++counter;
			else
				break;
		}				
		for(int i=pos_row+1, j=pos_col+1;i<row&&j<column;++i,++j){
			if(i<row&&j<column&&gameBoard[i][j].getCell()==symbol)
				++counter;
			else
				break;
		}
		if(counter>=4){
			for(int i=pos_row, j=pos_col;i>=0&&j>=0;--i,--j){
				if(i>=0&&j>=0&&gameBoard[i][j].getCell()==symbol)
					gameBoard[i][j].setCell(tolower(symbol));
				else
					break;
			}				
			for(int i=pos_row+1, j=pos_col+1;i<row&&j<column;++i,++j){
				if(i<row&&j<column&&gameBoard[i][j].getCell()==symbol)
					gameBoard[i][j].setCell(tolower(symbol));
				else
					break;
			}	
		}			
		return counter;
	}
	const int ConnectFourAbstract::comp_LF() const
	{
		int counter=0;
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(gameBoard[i][j].getCell()==symbol){
					++counter;	
					if(counter==3&&j+1<column&&i+1<row&&gameBoard[i][j+1].getCell()=='*'&&gameBoard[i+1][j+1].getCell()!='*')		
						return j+1;
					else if(counter==3&&j-3>=0&&gameBoard[i][j-3].getCell()=='*')	
						return j-3;
				}
				else
					counter=0;				
			}
		}	
		return 2017;
	}
	const int ConnectFourAbstract::comp_UD() const
	{
		int counter=0;
		for(int i=0;i<column;++i){
			for(int j=row-1;j>=0;--j){
				if(gameBoard[j][i].getCell()==symbol){
					++counter;
					if(counter==3&&j-1>=0&&gameBoard[j-1][i].getCell()=='*'){	
						return i;
					}	
				}
				else
					counter=0;			
			}
		}	
		return 2017;
	}
	const int ConnectFourAbstract::comp_LD() const
	{
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(i+2<row&&j+2<column&&gameBoard[i][j].getCell()==symbol&&
				gameBoard[i+1][j+1].getCell()==symbol&&gameBoard[i+2][j+2].getCell()==symbol){
					if(j+3<column&&i+3<row&&gameBoard[i+3][j+3].getCell()=='*')
						return j+3;	
					else if(j-1>=0&&i-1>=0&&gameBoard[i-1][j-1].getCell()=='*')
						return j-1;	
				}
			}
		}							
		return 2017;
	}

	const int ConnectFourAbstract::comp_RD() const
	{
		for(int i=row-1;i>=0;--i){
			for(int j=0;j<column;++j){
				if(i-2>=0&&j+2<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i-1][j+1].getCell()==symbol&&
				gameBoard[i-2][j+2].getCell()==symbol){
					if(j+3<column&&i-3>=0&&gameBoard[i-3][j+3].getCell()=='*')
						return j+3;	
					else if(j-1>=0&&i+1<row&&gameBoard[i+1][j-1].getCell()=='*')
						return j-1;	
				}
			}
		}							
		return 2017;
	}
	const int ConnectFourAbstract::compAttack_LF() const
	{
		int counter=0;
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(gameBoard[i][j].getCell()==symbol){
					++counter;	
					if(counter==2&&j+1<column&&gameBoard[i][j+1].getCell()=='*')	
						return j+1;
					else if(counter==2&&j-2>=0&&gameBoard[i][j-2].getCell()=='*')	
						return j-2;
				}
				else
					counter=0;				
			}
		}	
		return 2017;

	}
	const int ConnectFourAbstract::compAttack_UD() const
	{
		int counter=0;
		for(int i=0;i<column;++i){
			for(int j=row-1;j>=0;--j){
				if(gameBoard[j][i].getCell()==symbol){
					++counter;
					if(counter==2&&j-1>=0&&gameBoard[j-1][i].getCell()=='*')	
						return i;
				}
				else
					counter=0;			
			}
		}	
		return 2017;

	}
	const int ConnectFourAbstract::compAttack_RD() const
	{
		for(int i=row-1;i>=0;--i){
			for(int j=0;j<column;++j){
				if(i-1>=0&&j+1<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i-1][j+1].getCell()==symbol){
					if(j+2<column&&i-2>=0&&gameBoard[i-2][j+2].getCell()=='*')
						return j+2;	
					else if(j-1>=0&&i+1<row&&gameBoard[i+1][j-1].getCell()=='*')
						return j-1;	
				}
			}
		}							
		return 2017;
	}
	const int ConnectFourAbstract::compAttack_LD() const
	{
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(i+1<row&&j+1<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i+1][j+1].getCell()==symbol){
					if(j+2<column&&i+2<row&&gameBoard[i+2][j+2].getCell()=='*')
						return j+2;	
					else if(j-1>=0&&i-1>=0&&gameBoard[i-1][j-1].getCell()=='*')
						return j-1;	
				}
			}
		}							
		return 2017;
	}
	const int ConnectFourAbstract::compB_LF() const
	{
		int counter=0;
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(j+3<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i][j+1].getCell()==symbol&&
					gameBoard[i][j+3].getCell()==symbol&&gameBoard[i][j+2].getCell()=='*')
					return j+2;
				if(j+3<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i][j+1].getCell()=='*'&&
					gameBoard[i][j+2].getCell()==symbol&&gameBoard[i][j+3].getCell()==symbol)
					return j+1;				
			}
		}	
		return 2017;
	}
	const int ConnectFourAbstract::compB_LD() const
	{
		for(int i=0;i<row;++i){
			for(int j=0;j<column;++j){
				if(i+3<row&&j+3<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i+1][j+1].getCell()==symbol&&
					gameBoard[i+2][j+2].getCell()=='*'&&gameBoard[i+3][j+3].getCell()==symbol)
						return j+2;	
					else if(i+3<row&&j+3<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i+1][j+1].getCell()=='*'&&
					gameBoard[i+2][j+2].getCell()==symbol&&gameBoard[i+3][j+3].getCell()==symbol)
						return j+1;	
			}
		}							
		return 2017;
	}
	const int ConnectFourAbstract::compB_RD() const
	{
		for(int i=row-1;i>=0;--i){
			for(int j=0;j<column;++j){
				if(i-3>=0&&j+3<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i-1][j+1].getCell()==symbol&&
					gameBoard[i-2][j+2].getCell()=='*'&&gameBoard[i-3][j+3].getCell()==symbol)
						return j+2;	
					else if(i-3>=0&&j+3<column&&gameBoard[i][j].getCell()==symbol&&gameBoard[i-1][j+1].getCell()=='*'&&
					gameBoard[i-2][j+2].getCell()==symbol&&gameBoard[i-3][j+3].getCell()==symbol)
						return j+1;	
			}
		}							
		return 2017;
	}

	int ConnectFourAbstract::moveComputer(int loc)
	{
		for(int i=row-1;i>=0&&loc>=0;--i){//inputu ilgili lokasyona yerleştirir
			if(gameBoard[i][loc].getCell()=='*'){
				gameBoard[i][loc].setCell('O');
				return 1;
			 }	
		}
		return 2;
	}
}	

