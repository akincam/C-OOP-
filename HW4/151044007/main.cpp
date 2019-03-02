#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;

class ConnectFour
{
	public:
		ConnectFour();  //creates a 5*5 game
		ConnectFour(string filename);	//take a filename and create a game according the file
		ConnectFour(int take_row , int  take_column);  //takes number of rows and columns
		ConnectFour(const ConnectFour& gameboard);  //copy constructor;
		~ConnectFour();  //destructor
		
		bool setGameRow(int input);  //set the row from taken inputs
		bool setGameColumn(int input); 	//set the column from taken inputs
		bool setPVPorPVC(char gametype); //set the gametype p or c from taken input	
		bool setPosition(string take_position);  //set whether the position is illegal from taken position
		
		inline int getGameRow() const {return row;}	
		inline int getGameColumn() const {return column;}	
		inline char getPVPorPVC() const {return pvpOrpvc;}	
		inline string getPosition() const {return position;}
			
		int readFile();
		bool MP(); //multiplayer game
		void pVpOrpVc(); //to choose game type
		bool playGame(); 	
	
		ConnectFour& operator =(const ConnectFour& rightSide);	//overload assignment operator
		friend bool operator ==(const ConnectFour& c1, const ConnectFour& c2);
		friend bool operator !=(const ConnectFour& c1, const ConnectFour& c2);
		static int returnLivingCell();
	
	private:
		class Cell
		{
			public:
				Cell();
				Cell(char cell);
				Cell(int cell_row ,int cell_column);
			
				inline void setRow(int cell_row) {return_row=cell_row;}
				inline void setColumn(int cell_column) {return_column=cell_column;}
				inline void setCell(char content_cell) {cell=content_cell;}
			
				inline int getRow() const {return return_row;}	
				inline int getColumn() const {return return_column;}	
				inline char getCell() const {return cell;}
				
				Cell operator ++(int);
				Cell& operator ++();
				
				Cell operator --(int);
				Cell& operator --();
					
				bool operator ==(const Cell &c1) const;
				friend istream& operator >>(istream& inputStream , Cell& c1);
				friend ostream& operator <<(ostream& outputStream , const Cell& c1);			
			private:
				int return_row;
				int return_column;
				char cell;	
		};
		friend istream& operator >>(istream& inputStream , Cell& c1);
		friend ostream& operator <<(ostream& outputStream ,const Cell& c1);
		
		int row;
		int column;
		char pvpOrpvc;
		char symbol;
		string position;
		Cell **gameBoard;
		static int LivCell;
		
		void takePosition();   //take position from user
		void displayGame() const;
		int moveComputer(int loc);	 //move computer input
			
     	bool play();
     	bool play(string& take_input) ;
     	
     	int loadTheGame(const string & filename , char sym);
		void saveTheGame(const string & filename , char sym) const;	
     	
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
int ConnectFour::LivCell=0;
void Multiplayer();


int main(){
	char sm;//single ya da multi oyuna karar vermek için
	ConnectFour gameA;
	do{
		cout<<"SİNGLE /S/ MULTİ /M/---->";
		cin>>sm;
		cout<<endl;
		if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			cerr<<"Try again"<<endl;
		}
	}while(sm!='M'&&sm!='S');
	if(sm=='S')//single oyun için	
		gameA.playGame();
	if(sm=='M')
		Multiplayer();		
	return 0;
}

istream& operator >>(istream& inputStream , ConnectFour::Cell& c1){


	inputStream>>c1.return_column;	
	inputStream>>c1.return_row;
	inputStream>>c1.cell;
	
	return inputStream;
}
ostream& operator <<(ostream& outputStream ,const ConnectFour::Cell& c1) {
	
	outputStream<<"row-> "<<c1.return_row<<endl;
	outputStream<<"column-> "<<c1.return_column<<endl;
	outputStream<<"cell-> "<<c1.cell<<endl;
	return outputStream;
}


bool ConnectFour::Cell::operator ==(const Cell &c1) const{

	return((return_row==c1.return_row)&&
		   (return_column==c1.return_column)&&(cell==c1.cell));
}

bool operator ==(const ConnectFour& c1, const ConnectFour& c2) 
{
	if((c1.row!=c2.row)||(c1.column!=c2.column))
		return false;
	else if((c1.row==c2.row)&&(c1.column==c2.column)){
		for(int i=0;i<c1.row;++i){
			for(int j=0;j<c1.column;++j){
				if(c1.gameBoard[i][j].getCell()!=c2.gameBoard[i][j].getCell())
					return false;
			}
		}
	}
	return true;				
}
bool operator !=(const ConnectFour& c1, const ConnectFour& c2) 
{
	if((c1.row!=c2.row)||(c1.column!=c2.column))
		return true;
	else if((c1.row==c2.row)&&(c1.column==c2.column)){
		for(int i=0;i<c1.row;++i){
			for(int j=0;j<c1.column;++j){
				if(c1.gameBoard[i][j].getCell()!=c2.gameBoard[i][j].getCell())
					return true;
			}
		}
	}
		return false;				
}
ConnectFour::Cell& ConnectFour::Cell::operator ++()
{
	if(cell=='*')
		cell='A';
	else if(cell=='A')
		cell='B';
	else if(cell=='B')
		cell='C';
	else if(cell=='C')
		cell='*';	
		
	return *this;			
}
ConnectFour::Cell ConnectFour::Cell::operator ++(int)
{
	Cell c1;
	c1.cell=cell;
	if(c1.cell=='*')
		c1.cell='A';
	else if(c1.cell=='A')
		c1.cell='B';
	else if(c1.cell=='B')
		c1.cell='C';
	else if(c1.cell=='C')
		c1.cell='*';	
		
	return Cell(c1);			
}
ConnectFour::Cell& ConnectFour::Cell::operator --()
{
	if(cell=='*')
		cell='C';
	else if(cell=='C')
		cell='B';
	else if(cell=='B')
		cell='A';
	else if(cell=='A')
		cell='*';	
		
	return *this;			
}
ConnectFour::Cell ConnectFour::Cell::operator --(int)
{
	Cell c1;
	c1.cell=cell;
	if(c1.cell=='*')
		c1.cell='C';
	else if(c1.cell=='C')
		c1.cell='B';
	else if(c1.cell=='B')
		c1.cell='A';
	else if(c1.cell=='A')
		c1.cell='*';	
		
	return Cell(c1);			
}

ConnectFour::Cell::Cell() :
						   return_row(0),
						   return_column(0),
						   cell(0)
{ /*Body intentionally empty*/ }			
ConnectFour::Cell::Cell(char cell)
{
	setCell(cell);
}
ConnectFour::Cell::Cell(int cell_row ,int cell_column)
{
	setRow(cell_row);
	setColumn(cell_column);
}

ConnectFour::ConnectFour()
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

ConnectFour::ConnectFour(const ConnectFour& gameboard)//copy constructor	
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
ConnectFour::ConnectFour(string filename)
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
ConnectFour::ConnectFour(int take_row , int  take_column)//takes row and column allocate memory 
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
ConnectFour& ConnectFour::operator =(const ConnectFour& rightSide)
{
	if(&rightSide==this)
		return *this;
		
	if(row!=rightSide.row || column!=rightSide.column)
	{
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
ConnectFour::~ConnectFour()//destructor
{
	for(int i=0;i<row;++i)
		delete [] gameBoard[i];
	delete [] gameBoard;	
}

bool ConnectFour::setGameRow(int input)//if row is legal
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

bool ConnectFour::setGameColumn(int input)
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
bool ConnectFour::setPVPorPVC(char gametype)//determine gametype
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
bool ConnectFour::setPosition(string take_position)
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
void ConnectFour::pVpOrpVc()
{
	bool check=false;
	char gameChoice;
	while(!check){
		cout<<endl<<endl<<"Press 'P' for PvP......Press 'C' for PvC ->>>";
		cin>>gameChoice;
		check=setPVPorPVC(gameChoice);
	}	
}
void ConnectFour::takePosition() 
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
void ConnectFour::displayGame() const
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
bool ConnectFour::play(string& take_input) 
{
	int i;
	string strL="LOAD"; string strS="SAVE";
	int control=0;
	while(true){
		if(take_input.find(strL)==0){//if input is load
			take_input.erase(0,5);//delete the Load there is only file name
			if(loadTheGame(take_input,symbol)==0){
				loadTheGame(take_input,symbol);//load the game
				take_input.clear();
				takePosition(); //take position again
				take_input=position;	
			}
		}	
		if(take_input.find(strS)==0){//if input is save
			take_input.erase(0,5);
			saveTheGame(take_input,symbol);
				take_input.clear();
				takePosition();
				take_input=position;
		}
		else
			break;
	}			
	for(int j=0,i=0;j<column;++j){//check whether bord is full
		if(gameBoard[i][j].getCell()!='*'||gameBoard[i][j].getCell()==' '){
			++control;
		}		
	}	
	if(control==column-1){//if board is full
		for(int i=row-1;i>=0;--i){//move the symbol legal location
		 	if(gameBoard[i][take_input[0]-'A'].getCell()=='*'){
			 	gameBoard[i][take_input[0]-'A'].setCell(symbol);
		 		break;
		 	}	
		}
		if(check_LF(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_UD(i,take_input[0]-'A')>=4){	
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_LD(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_RD(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		cerr<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;	
		return true;						
	}
	else{//if board has still empty legal location
		for(i=row-1;i>=0;--i){//move the symbol legal location
		 	if(gameBoard[i][take_input[0]-'A'].getCell()=='*'){
			 	gameBoard[i][take_input[0]-'A'].setCell(symbol);
		 		break;
		 	}	
		}
		if(check_LF(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_UD(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_RD(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}	
		else if(check_LD(i,take_input[0]-'A')>=4){
			cout<<endl<<"User " <<symbol<< " Win"<<endl<<endl;
			return true;
		}						
	}	
	return false;		
}
bool ConnectFour::play()
{
	symbol='C';//control and if the game end return true
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
				
		symbol='A';//to prevent users's win the game
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
	
	symbol='C';//to complete 3 for computer		
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
			if(gameBoard[i][j].getCell()==symbol){
				if(j+1<column&&i+1<row&&gameBoard[i+1][j+1].getCell()!='*'&&
					gameBoard[i+1][j+1].getCell()!=' '){
					moveComputer(j+1);
					return false;
				}	
				else if(i-3>=0&&gameBoard[i-1][j].getCell()=='*'&&
					gameBoard[i-3][j].getCell()=='*'){
					moveComputer(j);
					return false;
				}
				else if(j+1<column&&gameBoard[i][j+1].getCell()!='*'&&gameBoard[i][j+1].getCell()!=' '){
					moveComputer(j+1);
					return false;
				}
				else if(j-1>=0&&gameBoard[i][j-1].getCell()!='*'&&gameBoard[i][j-1].getCell()!=' '){
					moveComputer(j-1);
					return false;
				}
							
			}
		}
	}
	//for first move or other legal moves
	for(int i=row-1;i>=0;--i){
		for(int j=2;j<column;++j){				
			if(gameBoard[i][j].getCell()=='*'){
				moveComputer(j);
				return false;
			}
		}
	}			
}
bool ConnectFour::playGame()
{
	string filename;
	bool check=false;
	symbol='X';
	cout<<"File Name: ";
	cin>>filename;
	pVpOrpVc();
	ifstream loadGame;
	int i;
	for(int i=0;i<row;++i)
		delete [] gameBoard[i];
	delete [] gameBoard;
	
	cin.ignore(256,'\n');
	loadGame.open(filename.c_str());//to take file name from user
	if(loadGame.fail()){//if file name isnt appropriate exit the game
		cerr<<"Output file couldnt open"<<endl;
		exit(1);
 	}
 	else{
 		string test;
 		for(i=0;getline(loadGame,test);++i);
 		row=i;
 		loadGame.close();
 		loadGame.open(filename.c_str());
 		
 		for(int i=0;!(loadGame.eof());++i){
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
 		loadGame.open(filename.c_str());	
 		for(i=0;getline(loadGame,test);++i)
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
 	}
	displayGame();
	string strL="LOAD";
	while(!check){
		if(pvpOrpvc=='P'){
			if(check==false&&pvpOrpvc=='P'&&LivCell!=row*column){//game type is P
				symbol='A';
				position.clear();
				takePosition();
				check=play(position);
				++LivCell;
				returnLivingCell();
				displayGame();
				cout<<endl<<"livingCell->> "<<LivCell<<endl;
			}						
			if(check==false&&pvpOrpvc=='P'){//for user 2
				symbol='B';			
				position.clear();
				takePosition();
				check=play(position);
				++LivCell;
				returnLivingCell();
				displayGame();
				cout<<endl<<"livingCell->> "<<LivCell<<endl;
			}
		}
		if(pvpOrpvc=='C'&&LivCell!=row*column){//for to play computer vs user
			check=false;
			symbol='A';
			position.clear();
			takePosition();
			check=play(position);
			++LivCell;
			returnLivingCell();
			displayGame();
			cout<<endl<<"livingCell->> "<<LivCell<<endl;
			if(check==false&&pvpOrpvc=='C'&&LivCell!=row*column){	
				symbol='C';
				check=play();
				++LivCell;
				returnLivingCell();
				displayGame();
				cout<<endl<<"livingCell->> "<<LivCell<<endl;
				if(check==true){
					cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
					return true;
				}
			}	
		}		
	
	}
	return check;
}
int ConnectFour::loadTheGame(const string & filename , char sym)
{
	ifstream loadGame;
	loadGame.open(filename.c_str());//to take file name from user
	if(loadGame.fail()){//if file name isnt appropriate exit the game
		cerr<<"Output file couldnt open"<<endl;
		exit(1);
 	}
 	else{
 		int k=LivCell;
 		int a=0;
			for(int z=0;z<row;++z)//calculate the living cell
				for(int o=0;o<column;++o)
					if(gameBoard[z][o].getCell()!='*'&&gameBoard[z][o].getCell()!=' ')
							++a;
		
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
 		int b=0;
 		for(int z=0;z<row;++z)//calculate the new livingCell
				for(int o=0;o<column;++o)
					if(gameBoard[z][o].getCell()!='*'&&gameBoard[z][o].getCell()!=' ')
							++b;
 		LivCell=k+b-a;
 		returnLivingCell();	
 	}
 	return 0;
}
void ConnectFour::saveTheGame(const string & filename , char sym) const
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
const int ConnectFour::check_UD(int pos_row,int pos_col) const
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
const int ConnectFour::check_LF(int pos_row,int pos_col) const
{
	int counter=0;
	for(int i=pos_col;i>=0;--i){
		if(gameBoard[pos_row][i].getCell()==symbol)
			++counter;
		else
			break;
	}				
	for(int i=pos_row+1;i<row;++i){
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
		for(int i=pos_row+1;i<row;++i){
			if(gameBoard[pos_row][i].getCell()==symbol)
				gameBoard[pos_row][i].setCell(tolower(symbol));
			else
				break;
		}	
	
	
	}							
	return counter;
}
const int ConnectFour::check_RD(int pos_row,int pos_col) const
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
const int ConnectFour::check_LD(int pos_row,int pos_col) const
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
const int ConnectFour::comp_LF() const
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
const int ConnectFour::comp_UD() const
{
	int counter=0;
	for(int i=0;i<column;++i){
		for(int j=row-1;j>=0;--j){
			if(gameBoard[j][i].getCell()==symbol){
				++counter;
				if(counter==3&&j-1>=0&&gameBoard[j-1][i].getCell()=='*')	
					return i;
			}
			else
				counter=0;			
		}
	}	
	return 2017;
}
const int ConnectFour::comp_LD() const
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

const int ConnectFour::comp_RD() const
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
const int ConnectFour::compAttack_LF() const
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
const int ConnectFour::compAttack_UD() const
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
const int ConnectFour::compAttack_RD() const
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
const int ConnectFour::compAttack_LD() const
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
const int ConnectFour::compB_LF() const
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
const int ConnectFour::compB_LD() const
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
const int ConnectFour::compB_RD() const
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

int ConnectFour::moveComputer(int loc)
{
	for(int i=row-1;i>=0;--i){//inputu ilgili lokasyona yerleştirir
		if(gameBoard[i][loc].getCell()=='*'){
			gameBoard[i][loc].setCell('C');
			return 1;
		 }	
	}
	return 2;
}
int ConnectFour::returnLivingCell()
{
	return(LivCell);
}

void Multiplayer()
{
	ConnectFour g1;ConnectFour g2;ConnectFour g3;ConnectFour g4;ConnectFour g5;
	int LivCell1=0;
	bool cntrl1=false;
	bool cntrl2=false;
	bool cntrl3=false;
	bool cntrl4=false;
	bool cntrl5=false;
			int inp;
			cout<<endl<<"****GAME 1****"<<endl;
			g1.readFile();
			g1.pVpOrpVc();
			cout<<"****GAME 2****"<<endl;
			g2.readFile();
			g2.pVpOrpVc();
			cout<<"****GAME 3****"<<endl;
			g3.readFile();
			g3.pVpOrpVc();
			cout<<"****GAME 4****"<<endl;
			g4.readFile();
			g4.pVpOrpVc();
			cout<<"****GAME 5****"<<endl;
			g5.readFile();
			g5.pVpOrpVc();
	
		while(true){
			cout<<"Choose a Object-->";
			cin>>inp;
			cout<<endl;
			if(cin.fail()){
				cin.clear();
				cin.ignore(999,'\n');
				cerr<<"False type! Enter object again"<<endl;
			}
			else if(inp>5||inp<1)
				cerr<<"False type! Enter object again"<<endl;
			switch(inp){//seçilen obje numarasına çağrılan oyun oynanır
		
				case 1:
						if(cntrl1==false){//bu bool ifadesi eğer oyun bittiyse tekrar oynamasını önlemek için
							cntrl1=g1.MP();
							LivCell1=g1.returnLivingCell();
							cout<<"All Living Cell-->"<<LivCell1<<endl;
							if(g1==g2)
								cout<<"The gameS are equal"<<endl;
							else
								cout<<"Not equal"<<endl;	
						}
						else
							cout<<"Game one is finished"<<endl;	
						break;
				case 2:
						if(cntrl2==false){
							cntrl2=g2.MP();
							LivCell1=g2.returnLivingCell();
							cout<<"All Living Cell-->"<<LivCell1<<endl;
							if(g2==g1)
								cout<<"The gameS are equal"<<endl;
							else
								cout<<"Not equal"<<endl;		
						}
						else
							cout<<"Game two is finished"<<endl;		
						break;
				case 3:
						if(cntrl3==false){
							cntrl3=g3.MP();
							LivCell1=g3.returnLivingCell();
							cout<<"All Living Cell-->"<<LivCell1<<endl;
							if(g3==g4)
								cout<<"The gameS are equal"<<endl;
							else
								cout<<"Not equal"<<endl;	
						}
						else
							cout<<"Game three is finished"<<endl;		
						break;
				case 4:
						if(cntrl4==false){
							cntrl4=g4.MP();
							LivCell1=g4.returnLivingCell();
							cout<<"All Living Cell-->"<<LivCell1<<endl;
							if(g4==g5)
								cout<<"The gameS are equal"<<endl;
							else
								cout<<"Not equal"<<endl;	
						}
						else
							cout<<"Game four is finished"<<endl;		
						break;
				case 5:
						if(cntrl5==false){
							cntrl5=g5.MP();
							LivCell1=g5.returnLivingCell();
							cout<<"All Living Cell-->"<<LivCell1<<endl;
							if(g5==g1)
								cout<<"The gameS are equal"<<endl;
							else
								cout<<"Not equal"<<endl;	
						}
						else
							cout<<"Game five is finished"<<endl;		
						break;
		
			}
		}
}
int ConnectFour::readFile()
{
	string filename;
	cin.ignore(256,'\n');
	cout<<"File Name: ";
	cin>>filename;
	ifstream loadGame;
	int i;
	loadGame.open(filename.c_str());//to take file name from user
	if(loadGame.fail()){//if file name isnt appropriate exit the game
		cerr<<"Output file couldnt open"<<endl;
		exit(1);
 	}
 	else{
 		string test;
 		for(i=0;getline(loadGame,test);++i);
 		row=i;
 		loadGame.close();
 		loadGame.open(filename.c_str());
 		
 		for(int i=0;!(loadGame.eof());++i){
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
 		loadGame.open(filename.c_str());	
 		for(i=0;getline(loadGame,test);++i)
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
 	}
 	return 0;
}
bool ConnectFour::MP()
{	
	bool check=false;

	cin.ignore(256,'\n');
	string strL="LOAD";
		if(pvpOrpvc=='P'){
			if(check==false&&pvpOrpvc=='P'&&LivCell!=row*column){
				symbol='A';
				position.clear();
				takePosition();
				check=play(position);
				++LivCell;
				returnLivingCell();
				displayGame();
			}						
			if(check==false&&pvpOrpvc=='P'&&position.find(strL)!=0){
				symbol='B';			
				position.clear();
				takePosition();
				check=play(position);
				++LivCell;
				returnLivingCell();
				displayGame();
			}
		}
		if(pvpOrpvc=='C'&&LivCell!=row*column){//bilgisayarla oynamak isteyen kullanıcılar için
			check=false;
			symbol='A';
			position.clear();
			takePosition();
			check=play(position);//return değerini kontrol eder eğer true ise bitirir
			++LivCell;
			returnLivingCell();
			displayGame();
			if(check==false&&pvpOrpvc=='C'&&LivCell!=row*column){	
				symbol='C';
				check=play();
				++LivCell;
				returnLivingCell();
				displayGame();
				if(check==true){
					cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
					return true;
				}
			}	
		}		
	return check;		
}




