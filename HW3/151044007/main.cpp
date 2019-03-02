#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
using namespace std;


class ConnectFour
{
	public:
		ConnectFour();
		ConnectFour(char inputColumn);
		ConnectFour(int inputRow,string position_input);
	
		const void takeRow();//kullanıcıdan satır sayısını alır
		const void takeColumn();//kullanıcıdan sütun sayısını alır
		void takePosition();//kullanıcıdan pozisyon alır
		const void pVpOrpVc();//kullanıcıdan oyun modunu alır
		
		const void printA() const;//oyuncuların sembollerini ekrana yazdırır.
		
		int loadTheGame(string file,char sym) ; //oyunu load eder
		const void saveTheGame(const string filename,char sym) const; //oyunu save eder
		
		int EndTheGameUpToDown(char sym);
		int EndTheGameHorizontal(char sym);
		int EndGameLeftDiagonal(char sym);
		int EndGameRightDiagonal(char sym);
		
		int putTheLocation(int col_loc);//bilgisayarın hamlesini board a yazdırı
		
		bool MP();//multiplayer için kullanıcıların oynamasını sağlayan fonksiyon
		
		void playGame(); //oyunun genel oynandığı fonksiyon
		bool play(string takeI);//kullanıcı vs kullanıcı için
		bool play();//bilgisayar fonksiyonu
		
		bool setRow(int row_num);
		bool setColumn(int column_let);
		bool setGameChoice(char pORc);
		bool setPosition(string takePos);
		
		
		inline int getRow() const  {return row;}	
		inline int getColumn() const {return column;}
		inline char getGameChoice() const {return pvpORpvc;}
		inline string getPosition() const {return position;}
		
		static int returnLivingCell();
		void initGame();
		void displayGame() const;
		private:
			class Cell
			{
				public:
					Cell();
					Cell(char contentOfCell);
					Cell(int rowNum );
				
					void setEachRow(int row_position);
					void setEachColumn(int column_position);
					void setEachCellContent(char cell);
				
					inline int getEachRow() const {return rowPos;}
					inline int getEachColumn() const {return columnPos;}
					inline char getEachContent() const {return cellContent;}
				
				private:
					int rowPos;
					int columnPos;
					char cellContent;
			};
			int ComputerLtoR(char sym ,int *loc);
			int ComputerUtoD(char sym, int *loc);
			int ComputerRD(char sym ,int *num);
			int ComputerLD(char sym, int *num);

			int row;
			int column;
			char pvpORpvc;
			char symbol='X';
			string position;
			static int LivingCell;
			
			vector<vector<Cell> >gameCells;	
};
int ConnectFour::LivingCell=0;


int main(){
	char sm;//single ya da multi oyuna karar vermek için
	int livingCell=0;
	bool cntrl1=false;
	bool cntrl2=false;
	bool cntrl3=false;
	bool cntrl4=false;
	bool cntrl5=false;
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
	if(sm=='M'){//multi oyun seçildiğinde
			ConnectFour gameOne;
			ConnectFour gameTwo;
			ConnectFour gameThree;
			ConnectFour gameFour;
			ConnectFour gameFive;
			ConnectFour control;
			int inp;
			cout<<endl<<"****GAME 1****"<<endl;
			gameOne.takeRow();
			gameOne.takeColumn();
			gameOne.pVpOrpVc();
			cout<<"****GAME 2****"<<endl;
			gameTwo.takeRow();
			gameTwo.takeColumn();
			gameTwo.pVpOrpVc();
			cout<<"****GAME 3****"<<endl;
			gameThree.takeRow();
			gameThree.takeColumn();
			gameThree.pVpOrpVc();
			cout<<"****GAME 4****"<<endl;
			gameFour.takeRow();
			gameFour.takeColumn();
			gameFour.pVpOrpVc();
			cout<<"****GAME 5****"<<endl;
			gameFive.takeRow();
			gameFive.takeColumn();
			gameFive.pVpOrpVc();
	
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
							cntrl1=gameOne.MP();
							livingCell=gameOne.returnLivingCell();
							cout<<"All Living Cell-->"<<livingCell<<endl;
						}
						else
							cout<<"Game one is finished AND BETTER OTHERS"<<endl;	
						break;
				case 2:
						if(cntrl2==false){
							cntrl2=gameTwo.MP();
							livingCell=gameTwo.returnLivingCell();	
						}
						else
							cout<<"Game two is finished AND BETTER OTHERS"<<endl;		
						break;
				case 3:
						if(cntrl3==false){
							cntrl3=gameThree.MP();
							livingCell=gameThree.returnLivingCell();
							cout<<"All Living Cell-->"<<livingCell<<endl;
						}
						else
							cout<<"Game three is finished AND BETTER OTHERS"<<endl;		
						break;
				case 4:
						if(cntrl4==false){
							cntrl4=gameFour.MP();
							livingCell=gameFour.returnLivingCell();
							cout<<"All Living Cell-->"<<livingCell<<endl;
						}
						else
							cout<<"Game four is finished AND BETTER OTHERS"<<endl;		
						break;
				case 5:
						if(cntrl5==false){
							cntrl5=gameFour.MP();
							livingCell=gameFive.returnLivingCell();
						}
						else
							cout<<"Game five is finished AND BETTER OTHERS"<<endl;		
						break;
		
			}
		}
	}
	else if(sm=='S')//single oyun için	
		gameA.playGame();	
	return 0;
}


ConnectFour::Cell::Cell() :
						   rowPos(0),
						   columnPos(0),
						   cellContent(0)
{ /*Body intentionally empty*/ }									


ConnectFour::Cell::Cell(int rowNum)
{
	setEachRow(rowNum);
	setEachColumn(rowNum);
}	


ConnectFour::Cell::Cell(char contentOfCell)
{
	setEachCellContent(contentOfCell);
}
void ConnectFour::Cell::setEachRow(int row_position)
{

	rowPos=row_position;
}


void ConnectFour::Cell::setEachColumn(int column_position)
{
	columnPos=column_position;
}

	
void ConnectFour::Cell::setEachCellContent(char cell)
{
	cellContent=cell;
}


//CONNECTFOURCLASS

ConnectFour::ConnectFour() : row(0),
							 column(0),						
							 pvpORpvc('\0')	
{ /*Body intentionally empty*/ }

ConnectFour::ConnectFour(char inputColumn)
{
	
	
	setGameChoice(inputColumn);
}
ConnectFour::ConnectFour(int inputRow,string position_input)
{
	setRow(inputRow);
	setPosition(position_input);
	setColumn(inputRow);
}
//kullanıcıdam aldığı input row u set eder
bool ConnectFour::setRow(int row_num)
{
	if(cin.fail()){
		cin.clear();
		cin.ignore(999,'\n');
		cerr<<"False type! Enter row again"<<endl;
		return false;
	}		
	else if(row_num>=4&&row_num<=100){
		row=row_num;
		return true;
	}			
	else{
		cerr<<"False input! Enter row again between 4 and 100"<<endl;
		return false;
	}	
}
//kullanıcıdam aldığı input column size ı set eder
bool ConnectFour::setColumn(int column_let)
{
	if(cin.fail()){
		cin.clear();
		cin.ignore(999,'\n');
		cerr<<"False type! Enter column again"<<endl;
		return false;
	}	
	else if(column_let>=0&&column_let<=26){
		column=column_let;
		return true;
	}

	else{
		cerr<<"False input! Enter column again"<<endl;
		return false;
	}	
}
//kullanıcıdam aldığı oyun seçimini  set eder	
bool ConnectFour::setGameChoice(char pORc)
{
	if(pORc>='a'&&pORc<='z'){
		cerr<<"Use UpperCase! try again"<<endl;
		return false;
	}	
	else if(cin.fail()){
		cin.clear();
		cin.ignore(999,'\n');
		cerr<<"False type! Enter  again"<<endl;
		return false;
	}
	else if(pORc!='P'&&pORc!='C'){
		cerr<<"Wrong input! enter again"<<endl;
		return false;
	}
	else{
		pvpORpvc=pORc;
		return true;
	}				
}


bool ConnectFour::setPosition(string takePos) 
{
	if(takePos[0]<'A'||takePos[0]>'Z'&&takePos.length()==1){//küçük harf input girilmişse
		cerr<<"Wrong Position ! try again use UpperCase"<<endl;
		return false;
	}
	else if(takePos.length()==1&&gameCells[0][takePos[0]-'A'].getEachContent()!='.'){//dolu yere hamle yapmak istiyorsa
		cerr<<"Wrong Position ! try again use "<<endl;
		return false;
	}	
	else if(cin.fail()){
		cin.clear();
		cin.ignore(999,'\n');
		cerr<<"False type! Enter position again"<<endl;
		return false;
	}
	else if(takePos[0]-'A'>=0&&takePos[0]-'A'<column&&takePos.length()==1){//doğru hamle
		position=takePos;
		return true;
	}
	else if(takePos.length()<6&&takePos.length()>1){//load save ya da input dısında birşey yazarsa
		cerr<<"Missing Input! try again"<<endl;
		return false;
	}
	else if(takePos=="SAVE"||takePos=="LOAD"){//sadece load ya da save yazarsa(dosya isimsiz)
		cerr<<"Wrong Input! try again"<<endl;
		return false;
	}
	else if(takePos.find("LOAD")==0||takePos.find("SAVE")==0&&takePos.length()>5){
		position=takePos;
		return true;
	}	
				
}	
const void ConnectFour::pVpOrpVc()
{
	ConnectFour();
	bool check=false;
	char gameChoice;
	while(!check){
		cout<<endl<<endl<<"Press 'P' for PvP......Press 'C' for PvC ->>>";
		cin>>gameChoice;
		check=setGameChoice(gameChoice);
	}	
}
const void ConnectFour::takeRow()
{
	ConnectFour();
	bool check=false;
	int row1=0;	
	while(!check){
		cout<<endl<<endl<<"Enter row---->";
		cin>>row1;   
		cout<<endl;
		check=setRow(row1);
	}
				
}	

const void ConnectFour::takeColumn()
{
	bool check=false;
	int column1=0;
	while(!check){
		cout<<endl<<endl<<"Enter column---->";
		cin>>column1; 
		cout<<endl;		
		check=setColumn(column1);
	}			
}
void ConnectFour::initGame()//oyunun oynanması için board init edilir ve nokta ile doldurulur
{
	vector<Cell>board;
	
	board.clear();
	
	Cell init;
	
	init.setEachCellContent('.'); 
	for( int j=0; j<column ; ++j){
		init.setEachColumn(j);
		board.push_back(init);
	}	
	for(int i=0 ; i<row ; ++i){
		init.setEachRow(i);
		gameCells.push_back(board);
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
			cout<<gameCells[i][j].getEachContent()<<" ";
		cout<<endl;	
	}
}				
const void ConnectFour::printA() const{
	if(pvpORpvc=='P'){		
		cout<<endl<<endl<<"   ****************************"<<endl<<endl;		
		cout<<"   *User1 is 'X'  User2 is 'O'*"<<endl;
		cout<<endl<<"   ****************************"<<endl<<endl;	
	}	
	else{
		cout<<endl<<endl<<"   ****************************"<<endl<<endl;		
		cout<<"   *User1 is 'X' Computer is 'O'*"<<endl;
		cout<<endl<<"   ****************************"<<endl<<endl;	
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
		check1=setPosition(user_input);	
	}	
}
void ConnectFour::playGame()
{
	takeRow();
	takeColumn();
	pVpOrpVc();
	printA();
	bool check=false;
	cin.ignore(256,'\n');
	
	initGame();
	displayGame();
	
	while(!check){//kullanıcılardan biri kazanana ya da oyun alanı dolana kadar oyunun sürmesi için
		if(pvpORpvc=='P'){
			symbol='X';
			takePosition();
			check=play(position);

			++LivingCell;
			returnLivingCell();
			
			displayGame();
			if(check==false&&pvpORpvc=='P'){//bu koşul kullanıcı load yapması durumunda değişmesi için
				symbol='O';			
				takePosition();
				check=play(position);//return değerini kontrol eder eğer true ise bitirir
				
				++LivingCell;
				returnLivingCell();
				
				cout<<"LivingCell->>"<<LivingCell<<endl;
				displayGame();
			}
		}
		if(pvpORpvc=='C'){//bilgisayarla oynamak isteyen kullanıcılar için
			check=false;
			symbol='X';
			takePosition();
			check=play(position);
			++LivingCell;
			returnLivingCell();
			displayGame();
			if(check==false){	
				symbol='O';

				check=play();
				++LivingCell;
				returnLivingCell();
				cout<<"LivingCell->>"<<LivingCell<<endl;
				displayGame();
			}	
		}		
	
	}
	cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
}	

bool ConnectFour::play(string takeInput) 
{
	string strL="LOAD"; string strS="SAVE";
	int control=0;
	while(true){//bu loop kullanıcı save ya da load yapmayıp doğru bir değer girdiğinde son bulur
		if(position[0]-'A'<0||position[0]-'A'>=column&&takeInput.length()==1){
				cerr<<endl<<"WRONG İNPUT !!choose another column"<<endl<<endl<<endl;		
				takePosition();
				takeInput=position;
			}	
		else if(takeInput.length()==1){
			if(gameCells[0][takeInput[0]-'A'].getEachContent()!='.'){
				cerr<<endl<<"This column is full choose another column"<<endl<<endl<<endl;
				takePosition();
				takeInput=position;
				
			}
		}
		else if(takeInput.find(strL)==0){//load yaparsa yeniden input ister
			takeInput.erase(0,5);//load yazısından sonrasını alır dosya ismi için
			if(loadTheGame(takeInput,symbol)==0){
				loadTheGame(takeInput,symbol);
				LivingCell=0;
				for(int z=0;z<row;++z)//yeniden toplam livingcell i hesaplar
					for(int o=0;o<column;++o)
						if(gameCells[z][o].getEachContent()!='.'){
							++LivingCell;
							returnLivingCell();
						}
						
				if(pvpORpvc=='P'){
					takeInput.clear();
					takePosition();
					takeInput=position;	

				}
				else if(pvpORpvc=='C'){
					takeInput.clear();
					takePosition();
					takeInput=position;	;
				}		
			}
		}	
			else if(takeInput.find(strS)==0){//save yaparsa yeniden input ister
				takeInput.erase(0,5);
				saveTheGame(takeInput,symbol);
				takeInput.clear();
				takePosition();
				takeInput=position;	
			}
			else if(takeInput.length()<6&&takeInput.length()>1){
				cerr<<endl<<"WRONG İNPUT !!choose another column"<<endl<<endl<<endl;
				position.clear();
				takePosition();
				takeInput=position;
			}
			
			if(position.length()==1&&gameCells[0][takeInput[0]-'A'].getEachContent()=='.')
				break;
			}		
			for(int j=0,i=0;j<column;++j){//board un dolup dolmadığına bakar
				if(gameCells[i][j].getEachContent()!='.'){
					++control;
				}	
		
			}
			
			if(control==column-1){//eğer board dolduysa oyun alanını kontrol eder ve bitirir
		
				gameCells[0][takeInput[0]-'A'].setEachCellContent(symbol);
					if(EndTheGameUpToDown(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					else if(EndTheGameHorizontal(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					else if(EndGameLeftDiagonal(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					else if(EndGameRightDiagonal(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					cerr<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;	
					return true;						
			}
			else{
				for(int i=row-1;i>=0;--i){//inputu ilgili lokasyona yerleştirir
		 			if(gameCells[i][takeInput[0]-'A'].getEachContent()=='.'){
			 			gameCells[i][takeInput[0]-'A'].setEachCellContent(symbol);
		 				break;
		 			}	
				 }
				 if(EndTheGameUpToDown(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					else if(EndTheGameHorizontal(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					else if(EndGameLeftDiagonal(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}	
					else if(EndGameRightDiagonal(symbol)>=4){
						cout<<endl<<"*****User " <<symbol<< " Win The Game*****"<<endl<<endl;
						return true;
					}						
			}	
			
			return false;		
			
}
int ConnectFour::loadTheGame(string file,char sym) {
	ifstream loadGame;

	loadGame.open(file.c_str());//to take file name from user
	if(loadGame.fail()){//if file name isnt appropriate exit the game
		cerr<<"Output file couldnt open"<<endl;
		return 1;
 	}
 	else{
 		gameCells.clear();
 		loadGame>>row
 			>>column
 			>>symbol
 			>>pvpORpvc;
 			initGame();	
 			char tempBoard[row][column];	
 		for(int i=0;i<row;++i)
 			for(int j=0;j<column;++j)
 				loadGame>>tempBoard[i][j];			
 		for(int i=0;i<row;i++){
 			for(int j=0;j<column;++j)
 				gameCells[i][j].setEachCellContent(tempBoard[i][j]);		
 		}

		displayGame();
 		loadGame.close();
 		return 0;	
 	}
}
const void ConnectFour::saveTheGame(const string filename,char sym) const{
 	ofstream saveGame;
 	saveGame.open(filename.c_str());//to take file name from user
 	if(saveGame.fail()){//if file name isnt appropriate exit the game
 		cerr<<"Output file couldnt open"<<endl;
 	}
 	else{
 		saveGame<<row<<endl
 			<<column<<endl
 			<<symbol<<endl
 			<<pvpORpvc<<endl;
 		for(int i=0;i<row;++i){
 			for(int j=0;j<column;++j)
 				saveGame<<gameCells[i][j].getEachContent();	
 			saveGame<<endl;
 		}			
 	}		
 	saveGame.close();						
} 	

int ConnectFour::EndTheGameUpToDown(char sym)
{	
	int counter=0;
		for(int i=0;i<row;i++){
			if(gameCells[i][position[0]-'A'].getEachContent()==sym){
				++counter;
				if(counter>=4){
					for(int k=0;k<4;++k){
						gameCells[i][position[0]-'A'].setEachCellContent(tolower(sym));
						--i;
					}
					return(counter);	
				}	
			}	
			else
				counter=0;					
		}			
	return counter;
}	
	
int ConnectFour::EndTheGameHorizontal(char sym)
{
	int counter=0;
	int i=0;
		for(i=0;i<row;++i)
			if(gameCells[i][position[0]-'A'].getEachContent()==sym)
				break;
		for(int k=0;k<column;++k){
			if(gameCells[i][k].getEachContent()==sym){
				++counter;
				if(counter>=4){
					for(int z=0;z<4;++z){
						gameCells[i][k].setEachCellContent(tolower(sym));
							--k;
					}
					return counter;		
				}
			}
			else
				counter=0;
			}
	return counter;
}						
						

int ConnectFour::EndGameRightDiagonal(char sym)
{
	for(int i=0;i<row;i++){
		for(int j=0;j<column;++j){
			if(i+3<row&&j-3>=0&&gameCells[i][j].getEachContent()==sym&&gameCells[i+1][j-1].getEachContent()==sym&&
			gameCells[i+2][j-2].getEachContent()==sym&&gameCells[i+3][j-3].getEachContent()==sym){
				j=j-3;
				i=i+3;
				for(int k=0;k<4;++k){
					gameCells[i][j].setEachCellContent(tolower(sym));
					++j,--i;
					}
					return 4;
				}	
			}
		
		}
		return 0;
}
				
		
int ConnectFour::EndGameLeftDiagonal(char sym) 
{

	for(int i=0;i<row;++i){
		for(int j=0;j<column;++j){
			if(i+3<row&&j+3<column&&gameCells[i][j].getEachContent()==sym&&gameCells[i+1][j+1].getEachContent()==sym&&gameCells[i+2][j+2].getEachContent()==sym
			&&gameCells[i+3][j+3].getEachContent()==sym){
				j=j+3;
				i=i+3;	
				for(int k=0;k<4;++k){
					gameCells[i][j].setEachCellContent(tolower(sym));
					--j,--i;
				}
					return 4;
			}	

		}	
	}
	return 0;
}
int ConnectFour::ComputerLtoR(char sym ,int *loc)
{
	int counter=0;
	*loc=0;
	for(int i=0;i<row;++i){
		for(int j=0;j<column;++j){
			if(gameCells[i][j].getEachContent()==sym){
				++counter;
				if(counter==3&&gameCells[i][j+1].getEachContent()=='.'&&j+1<column){
					++j; cout<<counter;
					*loc=j;
					 if(sym=='O'){
					 	for(int k=0;k<4;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							--j;
						}
					}	
					return counter;
				}
				else if(counter==3&&j-3>=0&&gameCells[i][j-3].getEachContent()=='.'){
					j=j-3;
					*loc=j;
					if(sym=='O'){
					 	for(int k=0;k<4;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							++j;
						}
					}	 
					return counter;
				}
				else if(counter==2&&j+1<column&&sym=='O'&&i+1<row&&gameCells[i+1][j+1].getEachContent()!='.'){
					j=j+1;
					*loc=j; 
					return counter;
				}
				else if(counter==1&&j+1<column&&sym=='O'){
					j=j+1;
					*loc=j; 
					return counter;
				}
			}
			else counter=0;	
		}
	}		
	return -8;								
}
int ConnectFour::ComputerUtoD(char sym, int *loc)
{
	int counter=0;
	*loc=0;
	for(int j=0;j<column;++j){
		for(int i=0;i<row;++i){
			if(i-2>=0&&gameCells[i][j].getEachContent()==sym&&gameCells[i-1][j].getEachContent()==sym&&gameCells[i-2][j].getEachContent()==sym){
				if(i-3>=0&&gameCells[i-3][j].getEachContent()=='.'){
					*loc=j;
					if(sym=='O'){
						for(int k=0;k<3;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							--i;
						}
					}
					return 3;
				}
			}

		}
	}
	for(int j=0;j<column;++j){
		for(int i=0;i<row;++i){
			if(i-2>=0&&gameCells[i][j].getEachContent()==sym&&gameCells[i-1][j].getEachContent()==sym&&gameCells[i-2][j].getEachContent()=='.'){
				*loc=j; 
				return 2;
			}
		}
	}		
	return -7;						
}
				
int ConnectFour::ComputerRD(char sym, int* num)
{
	*num=0;
	for(int i=row-1;i>=0;--i){
		for(int j=0;j<column;++j){
			if(i-2>=0&&j+2<column&&gameCells[i][j].getEachContent()==sym&&gameCells[i-1][j+1].getEachContent()==sym&&
			gameCells[i-2][j+2].getEachContent()==sym){
				if(j+3<column&&gameCells[0][j-3].getEachContent()=='.'){
					*num=3;
					j=j-3;
					if(sym=='O'){
						for(int k=0;k<4;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							--j,++i;
						}
					}	
					return j+3;
					
				}		
				else if(j-1>=0&&gameCells[0][j-1].getEachContent()=='.'){
					*num=3;
					j=j-1;
					if(sym=='O'){
						for(int k=0;k<4;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							++j,--i;
						}
					}	
					return j-1;
				}	
			}
			if(i+1<row&&j-1>=0&&gameCells[i][j].getEachContent()==sym&&gameCells[i-1][j+1].getEachContent()==sym){
				if(gameCells[0][j+2].getEachContent()=='.'&&j+2<column&&sym=='O'){
					*num=2;
					return j+2;
					
				}		
				else if(j-1>=0&&gameCells[0][j-1].getEachContent()=='.'&&sym=='O'){
					*num=2;
					return j-1;
					
				}	
			}	
		}	
	
	}
	return 0;
}	
int ConnectFour::ComputerLD(char sym,int *num)
{
	*num=0;
	for(int i=0;i<row;++i){
		for(int j=0;j<column;++j){
			if(i+2<row&&j+2<column&&gameCells[i][j].getEachContent()==sym&&gameCells[i+1][j+1].getEachContent()==sym&&gameCells[i+2][j+2].getEachContent()==sym){		

				if(j+3<column&&i+1<row&&gameCells[i+1][j+3].getEachContent()=='.'){
					*num=3;
					j=j+3;
					if(sym=='O'){
						for(int k=0;k<4;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							--j,--i;
						}
					}	 
					return j+3;
					
				}		
				else if(j-1>=0&&gameCells[0][j-1].getEachContent()=='.'){
					*num=3;
					j=j-1;
					if(sym=='O'){
						for(int k=0;k<4;++k){
							gameCells[i][j].setEachCellContent(tolower(sym));
							++j,++i;
						}
					}	 	
					return j-1;
					
				}	
			}
			if(i+1<row&&j+1<column&&gameCells[i][j].getEachContent()==sym&&gameCells[i+1][j+1].getEachContent()==sym){		
				if(gameCells[0][j+2].getEachContent()=='.'&&j+2<column&&sym=='O'){
					*num=2;
					return j+2;
					
				}		
				else if(j-1>=0&&gameCells[0][j-1].getEachContent()=='.'&&sym=='O'){
					*num=2;
					return j-1;
					
				}	
			}
		}		
	}
	return 0;	
}

bool ConnectFour::play() 
{
	int number;
	symbol='O';
	int i;
	if(ComputerLtoR(symbol, &number)==3){
		return true;
	}	
	symbol='O';
	if(ComputerUtoD(symbol, &number)==3){
		putTheLocation(number);
		for(int k=0;k<4;++k){
			for(i=0;i<row;++i){
				if(gameCells[i][number].getEachContent()!='.')
					break;
			}		
			gameCells[i][number].setEachCellContent(tolower(symbol));
		}	 
		return true;
	}	
	symbol='O';
	ComputerRD(symbol, &number);		
	if(number==3){
		return true;
	}	
	ComputerLD(symbol ,&number);		
	if(number==3){
		return true;
	}	
	symbol='X';
	
	if(ComputerLtoR(symbol, &number)==3){
		symbol='O';
		putTheLocation(number);
		return false;
	}	
	if(ComputerUtoD(symbol ,&number)==3){
		symbol='O'; 
		putTheLocation(number);	
		return false;
	}	
	ComputerRD(symbol, &number);		
	if(number==3){
		symbol='O';
		putTheLocation(ComputerRD(symbol, &number)); 
		return false;
	}	
	ComputerLD(symbol ,&number);
				
	if(number==3){
		symbol='O';
		putTheLocation(ComputerLD(symbol, &number));
		return false;
	}	
			
	symbol='O';
	if(ComputerLtoR(symbol, &number)==2){
		putTheLocation(number);
		return false;
	}	
	if(ComputerUtoD(symbol ,&number)==2){
		putTheLocation(number);	
		return false;
	}	
	ComputerRD(symbol,&number);		
	if(number==2){
		putTheLocation(ComputerRD(symbol, &number));
		return false;
	}	
	ComputerLD(symbol, &number);		
	if(number==2){
		putTheLocation(ComputerLD(symbol, &number));
		return false;
	}	
	for(int i=0;i<row;++i){
		for(int j=0;j<column;++j){
			if(gameCells[i][j].getEachContent()=='O'&&gameCells[i][j+1].getEachContent()=='.'&&j+1<column){
				putTheLocation(j+1);
					return false;
			}
			else if(gameCells[i][j].getEachContent()=='O'&&gameCells[i][j-1].getEachContent()=='.'&&j-1>=0){
				putTheLocation(j-1);
					return false;
			}
		}
	}		
	for(int i=0;i<column;++i){
		for(int j=0;j<row;++j){
			if(gameCells[i][j].getEachContent()=='O'&&gameCells[0][j].getEachContent()=='.'){
				putTheLocation(j);
					return false;
			}
		}
	}		
	for(int i=row-1;i>=0;--i){
		for(int j=0;j<column;++j){
			if(gameCells[i][j].getEachContent()=='.'){
				putTheLocation(j); 
					return false;
			}
		}
	}		
	return false;					
}

int ConnectFour::putTheLocation(int col_loc)//bilgisayarın yaptığı hamleyi board a yazmak için
{
	for(int i=row-1;i>=0;--i){
	 	if(gameCells[i][col_loc].getEachContent()=='.'){
	 		gameCells[i][col_loc].setEachCellContent(symbol);
	 		return 0;
	 	}	
	 }		
}	 		
	
int ConnectFour::returnLivingCell()
{
	return(LivingCell);
}
bool ConnectFour::MP()
{	
	bool check=false;
	cin.ignore(256,'\n');
	initGame();
	displayGame();
	if(pvpORpvc=='P'&&LivingCell!=row*column&&check==false){
		symbol='X';
		takePosition();
		check=play(position);
		++LivingCell;
		returnLivingCell();
		displayGame();
		if(pvpORpvc=='P'&&LivingCell!=row*column&&check==false){//bu koşul kullanıcı load yapması durumunda değişmesi için
			symbol='O';			
			takePosition();
			check=play(position);//return değerini kontrol eder eğer true ise bitirir
			++LivingCell;
			returnLivingCell();
			displayGame();
		}
	}
	if(pvpORpvc=='C'&&LivingCell!=row*column&&check==false){//bilgisayarla oynamak isteyen kullanıcılar için
		symbol='X';
		takePosition();
		check=play(position);
		++LivingCell;
		returnLivingCell();
		displayGame();
		if(LivingCell!=row*column&&check==false){	
			symbol='O';
			check=play();
			++LivingCell;
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


