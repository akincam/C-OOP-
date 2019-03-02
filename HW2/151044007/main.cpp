/*
İlk önce kullanıcıdan load yapıp yapmamak istediğini sorar.
Eğer yanlış dosya adı girerse hata verip oyuna devam eder. Değilse oyunu yükler ve devam eder.
askLocation fonksiyonu bir string alır eğer save ya da load ya da bir lokasyan yazmıyorsa yeniden sorar.
save yapılmak istendiğinde yanlış dosya uzantısı vs olursa oyuna devam eder.
Kullanıcı ilk kısımda load yapmazsa oyunu oynar ve bitirir.
eğer isterse oyunun ortasında lokasyon sorarken load ya da save yapabilir.
oyuna ilk başlarken load yapmak istediğini sorar yanlış dosya ismi girilirse yeni oyun açılır.
*/




#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int COLUMN= 20;
int numberOfString(string filename);
//return length of string
//if the length is 1, the game is played, if it is bigger then it will be load or save

int searchTheGameBoard(int row1,char gameArea[][COLUMN],int columnLoc);
//checks whether there is a space in the selected column
//if there is a space in the selected column returns 1
//if there isn't a space in the selected column returns 2

int loadTheGame(char gameA[][COLUMN], int &row1,char userS[2],int &gameSeq,string& filesName, char &playingMode);
//parameter taken as reference row1 and gameSeq
//loads old saved game from file

void saveTheGame(char gameA[][COLUMN],const int& row,int gameSeq,string filesName, char playingMode);
//saves the playing game

int rowNumber();
//Returns the row of the gameArea according to the user's input
//if the user's input illegal ask again

string askTheLocation(int row ,int userSequence);
string askTheLocation(int ,int=0);
//Returns the column location according to the user's input value
//row is taken from function of int rowNumber()
//if user's input isnt save or load ask input again

void printTheGame(char gameA[][COLUMN],int row);
// Nothing returns. Only Prints the gameArea when users make move

int EndTheGameUpToDown(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline);
//Check whether the game ends from the up to down
//Returns the number of symbols(either x or o) from up to down


int EndTheGameLeftToRight(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline);
//Checks whether the game ends from left to right
//Returns the number of symbols(either x or o) from up to down

int EndTheGameRightDiagonal(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline);
//Checks whether the game ends from left down diagonal right up diagonal
//Returns the number of symbols(either x or o) from up to down

int EndTheGameLeftDiagonal(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline);
//Checks whether the game ends from right down diagonal left up diagonal
//Returns the number of symbols(either x or o) from up to down

int userVsUser(char gameA[][COLUMN],char usersSymbol[2],int row1,int playingSeq,char playmod);
//If the user will play user vs user
int computerVsUser(char gameA[][COLUMN],char usersSymbol[2],int row1,int playingSeq,char playmod);
//If the user will play computer vs user
int main(){
	int row=0;
	int i,j;
	char users[2]; users[0]='X',users[1]='O';
	char gameChoice=0;
	int playingSeq=0;
	string filesName;
	char playingMode;
	decltype(playingMode) loadOrPlay;
		cout<<"Press 1 to load game or press any input to play new game-->";
		cin>>loadOrPlay;
	char gameArea[COLUMN][COLUMN];
	for(i=0;i<row;++i)//put dots game Area's locations
		for(j=0;j<row;++j)
			gameArea[i][j]='.';					
	for(i=0;i<COLUMN;++i)//to put Null out of the game area according to user's input row
		for(j=0;j<COLUMN;++j){
			if(gameArea[i][j]!='.')
				gameArea[i][j]='\0';	
	}
	cin.ignore(256,'\n');
	if(loadOrPlay=='1'){
		cout<<"Enter the file name to open saved game-->";
		getline(cin,filesName);
		cout<<endl;
		loadTheGame(gameArea,row,users,playingSeq, filesName, gameChoice);		
		if((gameChoice=='C'||gameChoice=='c')&&loadTheGame(gameArea,row,users,playingSeq, filesName, gameChoice)==0)
				computerVsUser(gameArea,users,row,playingSeq,gameChoice);
		if(gameChoice=='P'||gameChoice=='p'&&loadTheGame(gameArea,row,users,playingSeq, filesName, gameChoice)==0)
			userVsUser(gameArea,users,row,playingSeq,gameChoice);
		else{//eğer gecersiz dosya ismi girilirse direkt olarak yeni oyun başlar
			cout<<endl<<"Game is loading..."<<endl;
			row=rowNumber();	
			char gameArea[COLUMN][COLUMN];
			for(i=0;i<row;++i)//put dots game Area's locations
				for(j=0;j<row;++j)
					gameArea[i][j]='.';					
			for(i=0;i<COLUMN;++i)//to put Null out of the game area according to user's input row
				for(j=0;j<COLUMN;++j){
					if(gameArea[i][j]!='.')
						gameArea[i][j]='\0';	
			}

			cout<<endl<<"Press 'P' for MULTİPLAYER or Press 'C' for COMPUTER vs USER->>>";	
			cin>>gameChoice;
			while(gameChoice!='p'&&gameChoice!='c'&&gameChoice!='P'&&gameChoice!='C'){//to determine how to  play	
				cerr<<endl<<"Please Press 'P' for MULTİPLAYER or Press 'C' for COMPUTER vs USER->>>";	
				cin>>gameChoice;
			}
			if(gameChoice=='P'||gameChoice=='p'){		
				cout<<endl<<endl<<"   ****************************"<<endl<<endl;		
				cout<<"   * User1 is 'X' User2 is 'O' *"<<endl;
				cout<<endl<<"   ****************************"<<endl<<endl;	
			}	
			else{
				cout<<endl<<endl<<"   ****************************"<<endl<<endl;		
				cout<<"   * User1 is 'X' Computer is 'O' *"<<endl;
				cout<<endl<<"   ****************************"<<endl<<endl;	
			}
			cin.ignore(256,'\n');			
			printTheGame(gameArea,row);	
			if(gameChoice=='C'||gameChoice=='c')
				computerVsUser(gameArea,users,row,playingSeq,gameChoice);
			if(gameChoice=='P'||gameChoice=='p')
				userVsUser(gameArea,users,row,playingSeq,gameChoice);
				}	
				return 0;		
		}	
	else{	
	row=rowNumber();	
	char gameArea[COLUMN][COLUMN];
	for(i=0;i<row;++i)//put dots game Area's locations
		for(j=0;j<row;++j)
			gameArea[i][j]='.';					
	for(i=0;i<COLUMN;++i)//to put Null out of the game area according to user's input row
		for(j=0;j<COLUMN;++j){
			if(gameArea[i][j]!='.')
				gameArea[i][j]='\0';	
	}

	cout<<endl<<"Press 'P' for MULTİPLAYER or Press 'C' for COMPUTER vs USER->>>";	
	cin>>gameChoice;
	while(gameChoice!='p'&&gameChoice!='c'&&gameChoice!='P'&&gameChoice!='C'){//to determine how to  play	
		cerr<<endl<<"Please Press 'P' for MULTİPLAYER or Press 'C' for COMPUTER vs USER->>>";	
		cin>>gameChoice;
	}
	if(gameChoice=='P'||gameChoice=='p'){		
		cout<<endl<<endl<<"   ****************************"<<endl<<endl;		
		cout<<"   * User1 is 'X' User2 is 'O' *"<<endl;
		cout<<endl<<"   ****************************"<<endl<<endl;	
	}	
	else{
		cout<<endl<<endl<<"   ****************************"<<endl<<endl;		
		cout<<"   * User1 is 'X' Computer is 'O' *"<<endl;
		cout<<endl<<"   ****************************"<<endl<<endl;	
	}
	cin.ignore(256,'\n');			
	printTheGame(gameArea,row);	
	if(gameChoice=='C'||gameChoice=='c')
		computerVsUser(gameArea,users,row,playingSeq,gameChoice);
	if(gameChoice=='P'||gameChoice=='p')
		userVsUser(gameArea,users,row,playingSeq,gameChoice);
	return 0;
	}		
}
int searchTheGameBoard(int row1,char gameArea[][COLUMN],int columnLoc){
	int i;
	for(i=0;i<row1;++i){//checks whether there is a space in the selected column
		if(gameArea[i][columnLoc]=='.')//if there is a space return 1 else 2
			return 1;
		else
			return 2;
	}
	return 0;		
}
void saveTheGame(char gameA[][COLUMN],const int& row,char userS[2],int gameSeq,string filesName, char playingMode){
 	ofstream saveGame;
 	saveGame.open(filesName.c_str());//to take file name from user
 	if(saveGame.fail()){//if file name isnt appropriate exit the game
 		cerr<<"Output file couldnt open"<<endl;
 	}
 	else{
 		saveGame<<row<<endl
 			<<gameSeq<<endl
 			<<playingMode<<endl;
 		for(int i=0;i<row;i++){
 			for(int j=0;j<row;++j)
 				saveGame<<gameA[i][j];	
 			saveGame<<endl;
 		}			
 	}		
 	saveGame.close();						
} 	
int loadTheGame(char gameA[][COLUMN],int &row1,char userS[2],int &gameSeq,string& filesName, char &playingMode){
	ifstream loadGame;
	loadGame.open(filesName.c_str());//to take file name from user
	if(loadGame.fail()){//if file name isnt appropriate exit the game
		cerr<<"Output file couldnt open"<<endl;
		return 1;
 	}
 	else{
 		loadGame>>row1
 			>>gameSeq
 			>>playingMode;
 		for(int i=0;i<row1;i++){
 			for(int j=0;j<row1;++j)
 				loadGame>>gameA[i][j];		
 		}
 		for(int i=row1;i<COLUMN;++i)//to put Null out of the game area according to user's input row
			for(int j=row1;j<COLUMN;++j){
				gameA[i][j]='\0';			
		}
		 printTheGame(gameA,row1);
 		loadGame.close();
 		return 0;	
 	}
}
int rowNumber(){
	int row=0;
	bool control=true;	
	do{	
	cout<<endl<<"Please enter a double number between 4 and 20-->";
		cin>>row;
		if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			control=false;
			cerr<<endl<<"Wrong type";	
		}
		else
			control=true;
	}while(row<4||row%2!=0||row>20||control==false);	
	return row;
}

string askTheLocation(int row ,int userSequence){
 	char letters[20]={'A', 'B', 'C', 'D', 'E' ,'F', 'G' ,'H', 'I', 'J' ,'K', 'L', 'M' ,'N', 'O','P', 'Q', 'R', 'S','T'};
	string locationOfLetter;
	int i=0;

	locationOfLetter[0]='a';
	cout<<"User"<<userSequence+1<<" Choose a location from A to "<<letters[row-1]<<"  -->>";
	while(1){
		getline(cin,locationOfLetter);
		for(i=0;locationOfLetter[i]!='\0';++i);
		if(i==1){//if string lenght is 1 this means that user's input is a location
			if(locationOfLetter[0]>='a'&&locationOfLetter[0]<='z')
				locationOfLetter[0] =locationOfLetter[0]-32;
			if((locationOfLetter[0]-'A'<0||locationOfLetter[0]-'A'>row-1)){//if input isnt appropriate asks inputagain
				cerr<<"Wrong Location!! Please ";
				cerr<<"User"<<userSequence+1<<" Choose a location from A to "<<letters[row-1]<<"  -->>";
			}	
			else
				return locationOfLetter;
		}				
		if(i!=1){	
			for(int i=0;i<4;++i){
				if(locationOfLetter[i]>='a'&&locationOfLetter[i]<='z')
						locationOfLetter[i] =locationOfLetter[i]-32;
			}
			//control input is save or load if isnt asks again
			if((locationOfLetter[0]=='S'&&locationOfLetter[1]=='A'&&locationOfLetter[2]=='V'&&locationOfLetter[3]=='E'&&locationOfLetter[4]==' ')||
			(locationOfLetter[0]=='L'&&locationOfLetter[1]=='O'&&locationOfLetter[2]=='A'&&locationOfLetter[3]=='D'&&locationOfLetter[4]==' ')){			
				return locationOfLetter;
			}
			else{
				cerr<<"Wrong Location!! Please ";
				cerr<<"User"<<userSequence+1<<" Choose a location from A to "<<letters[row-1]<<"  -->>";
				locationOfLetter[1]='\0';
			}	
		}
		
	}
	return locationOfLetter;
}
void printTheGame(char gameBoard[][COLUMN],int row){
	char letters[20]={'A', 'B', 'C', 'D', 'E' ,'F', 'G' ,'H', 'I', 'J' ,'K', 'L', 'M' ,'N', 'O','P','Q' ,'R', 'S', 'T'};
	int i,j;
	for(i=0;i<row;++i)
		cout<<letters[i];
	cout<<endl;			
	for(i=0;i<row;++i){
		for(j=0;j<row;++j)
			cout<<gameBoard[i][j];
		cout<<endl;	
	}
	cout<<endl;
}
/*
	right top<-*  *  *->right top
				* * *
				 ***
	  left<-****  *  ****->right
				 ***
				* * *
  left down <- *  *  * ->right down
*/
int EndTheGameUpToDown(char gameA[][COLUMN],int row1,int usersloc, char usersSymbol[2],int gameSeq,int usersline){
	int numOfSymbol=0;
	int i,j;
	char symbol;
	i=usersline;
 	for(i=usersline;i<row1;i++){//controls the up to down of the symbol
 		if(gameA[i][usersloc]==usersSymbol[gameSeq])
 		numOfSymbol+=1;
 	else
 		break;
 	}
 	if(numOfSymbol>=4){
 		symbol=usersSymbol[gameSeq]+32;//When the game ends users symbol be tolower to show the gameboard clearly
 		for(j=0;j<=3;++j){//keep the last location before game and tolower this four symbols.
 			gameA[i-1][usersloc]=symbol;
 			i--;
 		}
 		cout<<endl<<"*****User " <<usersSymbol[gameSeq]<< " Win The Game*****"<<endl<<endl;
 	}	
	return numOfSymbol;
}
//count the same symbol to given location(looks locations left and right side) return same symbol numbers
int EndTheGameLeftToRight(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline){
	int numOfSymbol=0;
	int i,j;
	int columnkeep=0;
	char symbol;
	j=usersloc;
	i=usersline;
 	for(j=usersloc;j<row1;j++){//controls the right of the symbol
 		if(gameA[i][j]==usersSymbol[gameSeq]){
 			numOfSymbol+=1;
 			columnkeep=j;
 		}		
 	else
 		break;
 	}
 		if(numOfSymbol>=4){
			symbol=usersSymbol[gameSeq]+32;//tolower
			for(j=0;j<=3;++j){
 				gameA[i][columnkeep]=symbol;
 				columnkeep--;
 			}
 			cout<<endl<<"User " <<usersSymbol[gameSeq]<< " Win The Game"<<endl<<endl;
 			return numOfSymbol;	
 		}
	
 	for(j=usersloc-1;j>=0;j--){
 		if(gameA[i][j]==usersSymbol[gameSeq]){//controls the left of the symbol
 			numOfSymbol+=1;
 			columnkeep=j;
 		}		 	
 		else
 			break;
 	}		
	if(numOfSymbol>=4){
		symbol=usersSymbol[gameSeq]+32;//tolower
		for(j=0;j<=3;++j){//to lower the 4 symbols to show clearly winner's 4 neighbor symbols 
 			gameA[i][columnkeep]=symbol;
 			columnkeep++;
 		}
 		cout<<endl<<"User " <<usersSymbol[gameSeq]<< " Win The Game"<<endl<<endl;
 		}
	return numOfSymbol;		
}
//count the same symbol to given location(looks locations leftdia to rightdia side return same symbol numbers
int EndTheGameRightDiagonal(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline){
	int numOfSymbol=0;
	int i,j;
	char symbol;
	int columnkeep=0 ,rowkeep=0;
	j=usersloc;
	i=usersline;
	for(j=usersloc,i=usersline;j<row1&&i>=0;j++,i--){//controls the right top counts symbols which user plays
 		if(gameA[i][j]==usersSymbol[gameSeq]){
 			numOfSymbol+=1;	
 			columnkeep=j;
 			rowkeep=i;
 		}	
 		else
 			break;
 	}
	for(j=usersloc-1,i=usersline+1;j>=0&&i<row1;j--,i++){//controls the left down counts symbols which user plays
 		if(gameA[i][j]==usersSymbol[gameSeq])
 			numOfSymbol+=1;	
 	else
 		break;
 	}
	if(numOfSymbol>=4){
		symbol=usersSymbol[gameSeq]+32;//tolower
		for(j=0;j<=3;++j){//to lower the 4 symbols to show clearly winner's 4 neighbor symbols 
 			gameA[rowkeep][columnkeep]=symbol;
 			columnkeep--;
 			rowkeep++;
 		}
 		cout<<endl<<"User " <<usersSymbol[gameSeq]<< " Win The Game"<<endl<<endl;
 	}		
	return numOfSymbol;
}		
int EndTheGameLeftDiagonal(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline){
	int numOfSymbol=0;
	int i=0,j=0;
	char symbol;
	int columnkeep=0 ,rowkeep=0;
	j=usersloc;
	i=usersline;
	for(j=usersloc,i=usersline;j>=0&&i>=0;j--,i--){//controls the left top counts symbols which user plays
 		if(gameA[i][j]==usersSymbol[gameSeq]){
 			numOfSymbol+=1;
 			columnkeep=j;
 			rowkeep=i;
 		}		
 		else
 			break;
 	}
	for(j=usersloc+1,i=usersline+1;j<row1&&i<row1;j++,i++){//controls the right down (center of a symbol) counts symbols which user plays
 		if(gameA[i][j]==usersSymbol[gameSeq])
 			numOfSymbol+=1;	
 		else
 			break;
 	}
	if(numOfSymbol>=4){
		symbol=usersSymbol[gameSeq]+32;//tolower
		for(j=0;j<=3;++j){//to lower the 4 symbols to show clearly winner's 4 neighbor symbols 
 			gameA[rowkeep][columnkeep]=symbol;
 			columnkeep++;
 			rowkeep++;
 		}
 		cout<<endl<<"User " <<usersSymbol[gameSeq]<< " Win The Game"<<endl<<endl;
 	}		

	return numOfSymbol;
}

int computerUser(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline){

	int checkLeftToRight=EndTheGameLeftToRight(gameA,row1,usersloc,usersSymbol,gameSeq,usersline);
	int checkUptoDown=EndTheGameUpToDown(gameA,row1,usersloc,  usersSymbol,gameSeq, usersline);
	int checkRightDia=EndTheGameRightDiagonal(gameA,row1,usersloc,usersSymbol,gameSeq,usersline);
	int checkLeftDia=EndTheGameLeftDiagonal(gameA,row1,usersloc,usersSymbol,gameSeq,usersline);
	//CONTROLS THE IS END GAME? THERE 4 for BLOCKS	
	
	//to end the game when to be ***
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i][j+1]=='O'&&gameA[i][j+2]=='O'&&gameA[i][j+3]=='.'&&j+3<row1&&gameA[i+1][j+3]!='.')
					return(j+3);			
				if(gameA[i][j]=='O'&&gameA[i][j-1]=='O'&&gameA[i][j-2]=='O'&&gameA[i][j-3]=='.'&&j-3>=0&&gameA[i+1][j-3]!='.')
					return(j-3);
			}		
		}
	
	//to complete(4) from up to down
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j]=='O'&&gameA[i+2][j]=='O'&&gameA[i-1][j]=='.')
					return(j);				
			}		
		}
	
		//to complete(4) symbols left diagonal
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j+1]=='O'&&gameA[i+2][j+2]=='O'){
					if(gameA[i][j-1]!='.'&&j-1>=0&&gameA[i-1][j-1]=='.')
						return(j-1);
					if(gameA[i+3][j+3]=='.'&&i+3<row1&&j+3<row1&&gameA[i+4][j+3]!='.')
						return j+3;	
				}	
			}
		}
		//to complete(4) symbols right diagonal
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j-1]=='O'&&gameA[i+2][j-2]=='O'){
					if(gameA[i+3][j-3]=='.'&&j-3>=0&&gameA[i+4][j-3]!='.')
						return(j-3);
					if(gameA[i-1][j+1]=='.'&&i-1>=0&&j+1<row1&&gameA[i][j+1]!='.')
						return(j+1);	
				}	
			}
		}
		if(checkLeftToRight==3){//this function prevents the game from winning the opponent
			for(int i=0;i<row1;i++){
				for(int j=0;j<row1;++j){
					if(gameA[i][j]=='X'&&gameA[i][j+1]=='X'&&gameA[i][j+2]=='X'&&j+3<row1){
						if(gameA[i][j+3]=='.'&&j+3<row1)
							return(j+3);	
						if(gameA[i][j-1]=='.'&&gameA[i+1][j-1]!='.'&&j-1>=0)
							return(j-1);
					}
				
				}		
			}
		}
		for(int i=0;i<row1;i++){//if X.XX or XX.X to prevent won the user
				for(int j=0;j<row1;++j){
					if(gameA[i][j]=='.'){
						if(gameA[i][j-1]=='X'&&gameA[i][j+1]=='X'&&gameA[i][j+2]=='X')
							return(j);	
						if(gameA[i][j-1]=='X'&&gameA[i][j-2]=='X'&&gameA[i][j+1]=='X')
							return(j);
					}
				
				}		
			}
			
					
		for(int i=0;i<row1;i++){//if dot is between tree left diagonal symbols to prevent won the user
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='.'){
					if(gameA[i-1][j-1]=='X'&&gameA[i+1][j+1]=='X'&&gameA[i+2][j+2]=='X')
						return j;
					if(gameA[i-1][j-1]=='X'&&gameA[i-2][j-2]=='X'&&gameA[i+1][j+1]=='X')
						return j;	
				}	
			}
		}
		for(int i=0;i<row1;i++){//if dot is between tree right diagonal symbols to prevent won the user
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='.'){
					if(gameA[i-1][j+1]=='X'&&gameA[i+1][j-1]=='X'&&gameA[i+2][j-2]=='X')
						return j;
					if(gameA[i-1][j+1]=='X'&&gameA[i-2][j+2]=='X'&&gameA[i+1][j-1]=='X')
						return j;
				}	
			}
		}
		
		
	if(checkUptoDown==3){//this function prevents the game from winning the opponent
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='X'&&gameA[i+1][j]=='X'&&gameA[i+2][j]=='X'&&gameA[i-1][j]=='.')
					return(j);				
			}		
		}
	}
		
	if(checkLeftDia==3){//this function prevents the game from winning the opponent
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='X'&&gameA[i+1][j+1]=='X'&&gameA[i+2][j+2]=='X'){
					if(gameA[i][j-1]!='.'&&i-1>=0&&j-1>=0&&gameA[i-1][j-1]=='.'&&j-1>=0)
						return(j-1);
					if(gameA[i+3][j+3]=='.'&&i+3<row1&&j+3<row1&&gameA[i+4][j+3]!='.'&&j+3<row1)
						return j+3;		
				}	
			}
		}
	}
	if(checkRightDia==3){//this function prevents the game from winning the opponent
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='X'&&gameA[i+1][j-1]=='X'&&gameA[i+2][j-2]=='X'){
					if(gameA[i+3][j-3]=='.'&&i+3<row1&&j-2>=0&&gameA[i+4][j-3]!='.'&&j-3<row1)
						return(j-3);
					if(gameA[i-1][j+1]=='.'&&i-1>=0&&j+1<row1&&gameA[i][j+1]!='.'&&j+1<row1)
						return(j+1);	
				}	
			}
		}
	}
		//ADD A SYMBOL İF SYMBOL NUM ARE TWO(THİS FOUR IF BLOCKS)
		
		for(int i=0;i<row1;i++){//left to right
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i][j+1]=='O'&&gameA[i][j+3]=='.'&&gameA[i][j+2]=='.'&&gameA[i+1][j+2]!='.'&&gameA[i+1][j+2]!='.'&&j+2<row1)
					return(j+2);			
				if(gameA[i][j]=='O'&&gameA[i][j-1]=='O'&&gameA[i][j-2]=='.'&&gameA[i+1][j-2]!='.'&&j-2>=0)
					return(j-2);
			}		
		}

	//if there are two symbols up to down add the symbol
		for(int i=0;i<row1;++i){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j]=='O'&&gameA[i-1][j]=='.'&&gameA[i-2][j]=='.')
					return j;
			}		
		}
	//if there are two symbols of leftdiagonal add the symbol
		for(int i=0;i<row1;i++){
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j+1]=='O'){
					if(gameA[i][j-1]!='.'&&gameA[0][j-1]=='.'&&j-1>=0)
						return(j-1);
					if(gameA[i+2][j+2]=='.'&&gameA[i+3][j+2]!='.'&&j+2<row1)
						return j+2;	
				}	
			}
		}
//if there are two symbols of rightdiagonal add the symbol
		for(int i=0;i<row1;i++){	
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j-1]=='O'){
					if(gameA[i-2][j+2]=='.'&&gameA[i-3][j+3]=='.'&&j+3<row1&&gameA[i-1][j+2]=='.')
						return(j+2);
					if(gameA[i+1][j-2]=='.'&&gameA[i+2][j-2]!='.'&&gameA[i+2][j-3]=='.'&&j+1<row1)
						return(j+1);	
				}	
			}
		}
		for(int i=0;i<row1;++i){	
			for(int j=0;j<row1;++j){
				if(gameA[i][j]=='O'&&gameA[i+1][j+1]!='.'&&j+1<row1&&gameA[i][j+1]=='.'&&gameA[i][j+3]=='.'&&gameA[i][j+2]=='.'&&gameA[i+1][j+1]=='.'&&gameA[i+1][j+3]=='.')
					return j+1;
				if(gameA[i][j]=='O'&&gameA[i-1][j]=='.'&&gameA[i-3][j]=='.')
					return 	j;
				if(gameA[i][j]=='O'&&j+1<row1&&gameA[i][j+1]=='.')
					return j+1;	
			}
		}
	for(int i=0;i<row1;++i){//if above conditions are false this loop will find a empty location to for the game continue
		for(int j=0;j<row1;++j){
			if(gameA[i][j]=='.')
				return j;
		}
	}		
	return 8;

}
int computerVsUser(char gameA[][COLUMN],char usersSymbol[2],int row1,int playingSeq,char playmod){
	int column=-58;	
	int i=0,j=0;
	int cntrl=0;
	int allDotNums=row1*row1;

	int columnNumKeep=0;
	int usersRow=-58;
	int result=0;
	int playingSequence=0;
	int b=0;
	int userChooseLoc=-1;
	string filename;//this string takes input
	string saveOrLoad;//this sitring is used divide sentence and use them
	while(1){
		if(playingSeq==0){//playing sequence is user 1
			filename=askTheLocation(row1 ,playingSeq);//take a input
			if(numberOfString(filename)==1){//if input lenght is 1 
				userChooseLoc=filename[0]-'A';	
			}	
			else if(numberOfString(filename)!=1)//if input lenght isnt 1 check save or load
				for(int z=0;z<4;++z){
					saveOrLoad+=filename[z];
				}
			if(saveOrLoad=="LOAD"){//if input loads
				saveOrLoad.clear();
				for(int z=5;filename[z]!='\0';++z){//keep the file name (save filename.txt->f's locaiton is 5)
					saveOrLoad+=filename[z];
				}
				filename.clear();
				loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
				if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
					userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
					return 0; //to end game
				}		
				if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
					computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
					return 0;// to end game
				}	
			}			
			while(saveOrLoad=="SAVE"){
				saveOrLoad.clear();
				for(int z=5;filename[z]!='\0';++z){
					saveOrLoad+=filename[z];
				}
				saveTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
				filename.clear();
				filename=askTheLocation(row1 ,playingSeq);
				if(saveOrLoad=="LOAD"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];
					}
					loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
					return 0; //to end game
				}		
					if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
					return 0;// to end game
					}	
				}			
				saveOrLoad.clear();
				if(numberOfString(filename)==1){
					userChooseLoc=filename[0]-'A';
					filename.clear();
					break;	
				}	
				else if(numberOfString(filename)!=1)
					for(int z=0;z<4;++z){
						saveOrLoad+=filename[z];
				}
			}
			if(searchTheGameBoard(row1,gameA,userChooseLoc)==1){
				allDotNums -=1;
				cntrl=1;
			}
			if(searchTheGameBoard(row1,gameA,userChooseLoc)==2)
				cntrl=0;
			while(cntrl==0){
				cerr<<endl<<"This column is full choose another column"<<endl<<endl<<endl;
				filename=askTheLocation(row1 ,playingSeq);
				if(numberOfString(filename)==1){
					userChooseLoc=filename[0]-'A';	
				}	
				else if(numberOfString(filename)!=1)
					for(int z=0;z<4;++z){
						saveOrLoad+=filename[z];
					}
				if(saveOrLoad=="LOAD"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];
					}
					loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0; //to end game
				}		
					if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0;// to end game
				}	
				}			
				while(saveOrLoad=="SAVE"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];
					}
					saveTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					filename.clear();
					filename=askTheLocation(row1 ,playingSeq);
					if(saveOrLoad=="LOAD"){
						saveOrLoad.clear();
						for(int z=5;filename[z]!='\0';++z){
							saveOrLoad+=filename[z];
						}
						loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
						if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0; //to end game
						}		
						if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0;// to end game
						}	
					}			
					saveOrLoad.clear();
					if(numberOfString(filename)==1){
						userChooseLoc=filename[0]-'A';
						filename.clear();
						break;	
					}	
					else if(numberOfString(filename)!=1)
						for(int z=0;z<4;++z){
							saveOrLoad+=filename[z];
						}
				}
				if(searchTheGameBoard(row1,gameA,userChooseLoc)==1){
					allDotNums -=1;
					cntrl=1;
		
				}
				if(searchTheGameBoard(row1,gameA,userChooseLoc)==2)
					cntrl=0;
				}
			b=0; ++playingSeq;
			}
		else{
			userChooseLoc=computerUser(gameA,row1,columnNumKeep,usersSymbol,b,usersRow);
			b=1;
			--playingSeq;
			--allDotNums;
		}	
	
		if(allDotNums==0){//if area is full
			for(i=row1-1;i>=0;--i){
 				if(gameA[i][userChooseLoc]=='.'){
 					gameA[i][userChooseLoc]=usersSymbol[b];
 						break;
 				}	
 			}
			column=userChooseLoc;//a user's last choice's symbol of location(column). to use other function
	 		printTheGame(gameA,row1);	
	 		auto usersRow=i; //a user's last choice's symbol of location(row). to use other function	
		 	result=EndTheGameUpToDown(gameA,row1,column,usersSymbol,b,usersRow); 		
		 	if(result>=4){//checks whether the game is end
		 		printTheGame(gameA,row1);
		 		return 0;
			 }	
			result=EndTheGameLeftToRight(gameA,row1,column,usersSymbol,b,usersRow); 		
			if(result>=4){//checks whether the game is end
				printTheGame(gameA,row1);
			 	return 0;
			}
			result=EndTheGameRightDiagonal(gameA,row1,column,usersSymbol,b,usersRow);
			if(result>=4){//checks whether the game is end
			 	printTheGame(gameA,row1);
			 	return 0;
			}
			result=EndTheGameLeftDiagonal(gameA,row1,column,usersSymbol,b,usersRow);
			if(result>=4){//checks whether the game is end
			 	printTheGame(gameA,row1);
			 	return 0;
			 }
			cerr<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;
			return -1;
		}
		columnNumKeep=userChooseLoc;//a user's last choice's symbol of location(column). to use other function
		for(i=row1-1;i>=0;--i){//put the symbols epmty location in the choosen column
 			if(gameA[i][userChooseLoc]=='.'){
 				gameA[i][userChooseLoc]=usersSymbol[b];
 				userChooseLoc=-1;
 				break;
 			}	
 		}
 		printTheGame(gameA,row1);		
 		usersRow=i; //a user's last choice's symbol of location(row). to use other function		
 		result=EndTheGameUpToDown(gameA,row1,columnNumKeep,usersSymbol,b,usersRow); 		
 		if(result>=4){
 			if(b==1)
 				cout<<endl<<"This means that --Computer winnnnn--"<<endl<<endl;
 			printTheGame(gameA,row1);
 			return 2;
 		}	
		result=EndTheGameLeftToRight(gameA,row1,columnNumKeep,usersSymbol,b,usersRow);
 		if(result>=4){
 			if(b==1)
 				cout<<endl<<"This means that  --Computer winnnnn--"<<endl<<endl;
 			printTheGame(gameA,row1);
 			return 2;
 		}
 		result=EndTheGameRightDiagonal(gameA,row1,columnNumKeep,usersSymbol,b,usersRow);
 		if(result>=4){
 			if(b==1)
 				cout<<endl<<"This means that  --Computer winnnnn--"<<endl<<endl;
 			printTheGame(gameA,row1);
 			return 2;
 		}
 		result=EndTheGameLeftDiagonal(gameA,row1,columnNumKeep,usersSymbol,b,usersRow);
 		if(result>=4){
 			if(b==1)
 				cout<<endl<<"This means that  --Computer winnnnn--"<<endl<<endl;
 			printTheGame(gameA,row1);
 			return 2;
 		}
 		result=0;
 	}	
	return 0;	
}
		
int numberOfString(string filename){
	int i=0;
	for(i=0;filename[i]!='\0';++i);
	return i;
}	

int userVsUser(char gameA[][COLUMN],char usersSymbol[2],int row1,int playingSeq,char playmod){
	int userChooseLoc=-1;
	int cntrl=0,b=0;
	int i,j;
	int column, result;
	usersSymbol[0]='X';usersSymbol[1]='O';
	int allDotNums=row1*row1;
	string filename;//this string takes input
	string saveOrLoad;//this sitring is used divide sentence and use them
	while(1){//while game end
		if(playingSeq==0){//playing sequence is user 1
			filename=askTheLocation(row1 ,playingSeq);//take a input
			if(numberOfString(filename)==1){//if input lenght is 1 
				userChooseLoc=filename[0]-'A';	
			}	
			else if(numberOfString(filename)!=1)//if input lenght isnt 1 check save or load
				for(int z=0;z<4;++z){
					saveOrLoad+=filename[z];
				}
			if(saveOrLoad=="LOAD"){//if input loads
				saveOrLoad.clear();
				for(int z=5;filename[z]!='\0';++z){//keep the file name (save filename.txt->f's locaiton is 5)
					saveOrLoad+=filename[z];
				}
				filename.clear();
				loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);//load the game
				if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
					userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
					return 0; //to end game
				}		
				if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
					computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
					return 0;// to end game
				}	
			}			
			while(saveOrLoad=="SAVE"){
				saveOrLoad.clear();
				for(int z=5;filename[z]!='\0';++z){//keep the file name (save filename.txt->f's locaiton is 5)
					saveOrLoad+=filename[z];
				}
				saveTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);//save the game
				filename.clear();
				filename=askTheLocation(row1 ,playingSeq);
				if(saveOrLoad=="LOAD"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){//keep the file name (save filename.txt->f's locaiton is 5)
						saveOrLoad+=filename[z];
					}
					loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0; //to end game
					}		
					if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0;// to end game
					}		
				}			
				saveOrLoad.clear();
				if(numberOfString(filename)==1){//if input lenght is 1 to use input
					userChooseLoc=filename[0]-'A';
					filename.clear();
					break;	
				}	
				else if(numberOfString(filename)!=1)
					for(int z=0;z<4;++z){
						saveOrLoad+=filename[z];
				}
			}
			if(searchTheGameBoard(row1,gameA,userChooseLoc)==1){//controls the gameArea and whether looks there is space
				allDotNums -=1;
				cntrl=1;
			}
			if(searchTheGameBoard(row1,gameA,userChooseLoc)==2)
				cntrl=0;
			while(cntrl==0){//cntrl is 0 this column is full try again
				cerr<<endl<<"This column is full choose another column"<<endl<<endl<<endl;
				filename=askTheLocation(row1 ,playingSeq);
				if(numberOfString(filename)==1){
					userChooseLoc=filename[0]-'A';	
				}	
				else if(numberOfString(filename)!=1)
					for(int z=0;z<4;++z){
						saveOrLoad+=filename[z];
					}
				if(saveOrLoad=="LOAD"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];
					}
					loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0; //to end game
					}		
					if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0;// to end game
					}	
				}			
				while(saveOrLoad=="SAVE"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];
					}
					saveTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					filename.clear();
					filename=askTheLocation(row1 ,playingSeq);
					if(saveOrLoad=="LOAD"){
						saveOrLoad.clear();
						for(int z=5;filename[z]!='\0';++z){
							saveOrLoad+=filename[z];
						}
						loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
						if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0; //to end game
						}		
						if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0;// to end game
						}	
					}			
					saveOrLoad.clear();
					if(numberOfString(filename)==1){
						userChooseLoc=filename[0]-'A';
						filename.clear();
						break;	
					}	
					else if(numberOfString(filename)!=1)
						for(int z=0;z<4;++z){
							saveOrLoad+=filename[z];
						}
				}
				if(searchTheGameBoard(row1,gameA,userChooseLoc)==1){
					allDotNums -=1;
					cntrl=1;
		
				}
				if(searchTheGameBoard(row1,gameA,userChooseLoc)==2)
					cntrl=0;
				}
			b=0; ++playingSeq;			
			}
			else{//for user 2 according to playing game
				filename=askTheLocation(row1 ,playingSeq);
				if(numberOfString(filename)==1){
					userChooseLoc=filename[0]-'A';	
				}	
				else if(numberOfString(filename)!=1)
					for(int z=0;z<4;++z){
						saveOrLoad+=filename[z];
					}
				if(saveOrLoad=="LOAD"){//if user write load
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];	
					}
					loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0; //to end game
					}		
					if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
						computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
						return 0;// to end game
					}	
				}					
				while(saveOrLoad=="SAVE"){
					saveOrLoad.clear();
					for(int z=5;filename[z]!='\0';++z){
						saveOrLoad+=filename[z];
					}
					saveTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
					filename.clear();
					filename=askTheLocation(row1 ,playingSeq);
					if(saveOrLoad=="LOAD"){//if user write load
						saveOrLoad.clear();
						for(int z=5;filename[z]!='\0';++z){
							saveOrLoad+=filename[z];
						}
						loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
						if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0; //to end game
						}		
						if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0;// to end game
						}	
					}			
					saveOrLoad.clear();
					if(numberOfString(filename)==1){
						userChooseLoc=filename[0]-'A';
						filename.clear();
						break;	
					}	
					else if(numberOfString(filename)!=1)
						for(int z=0;z<4;++z){
							saveOrLoad+=filename[z];
						}
				}
				if(searchTheGameBoard(row1,gameA,userChooseLoc)==1){
					allDotNums -=1;
					cntrl=1;
				}
				if(searchTheGameBoard(row1,gameA,userChooseLoc)==2)
					cntrl=0;
				while(cntrl==0){//cntrl is 0 this column is full try again
					cerr<<endl<<"This column is full choose another column"<<endl<<endl<<endl;
					filename=askTheLocation(row1 ,playingSeq);
					if(numberOfString(filename)==1){
						userChooseLoc=filename[0]-'A';	
					}	
					else if(numberOfString(filename)!=1)
						for(int z=0;z<4;++z){
							saveOrLoad+=filename[z];
						}
					if(saveOrLoad=="LOAD"){//if user write load
						saveOrLoad.clear();
						for(int z=5;filename[z]!='\0';++z){
							saveOrLoad+=filename[z];
						}
						loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
						if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0; //to end game
						}		
						if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0;// to end game
						}	
					}				
					while(saveOrLoad=="SAVE"){
						saveOrLoad.clear();
						for(int z=5;filename[z]!='\0';++z){
							saveOrLoad+=filename[z];
						}
						saveTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
						filename.clear();
						filename=askTheLocation(row1 ,playingSeq);
						if(saveOrLoad=="LOAD"){//if user write load
							saveOrLoad.clear();
							for(int z=5;filename[z]!='\0';++z){
								saveOrLoad+=filename[z];
							}
						loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod);
						if(playmod=='p'||playmod=='P'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							userVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0; //to end game
						}		
						if(playmod=='c'||playmod=='C'&&loadTheGame(gameA,row1,usersSymbol,playingSeq, saveOrLoad,playmod)==0){
							computerVsUser(gameA,usersSymbol,row1,playingSeq,playmod);
							return 0;// to end game
						}	
						}										
						saveOrLoad.clear();
						if(numberOfString(filename)==1){
							userChooseLoc=filename[0]-'A';
							filename.clear();
							break;	
						}	
						else if(numberOfString(filename)!=1)
							for(int z=0;z<4;++z){
								saveOrLoad+=filename[z];
							}
					}
					if(searchTheGameBoard(row1,gameA,userChooseLoc)==1){//checks space in Area if searchTheGameBoard==2 there(column) is no space
						allDotNums -=1;
						cntrl=1;
					}
					if(searchTheGameBoard(row1,gameA,userChooseLoc)==2)
						cntrl=0;
				}	
				b=1; --playingSeq; 	
			}	
			if(allDotNums==0){//if area is full
			for(i=row1-1;i>=0;--i){
 				if(gameA[i][userChooseLoc]=='.'){
 					gameA[i][userChooseLoc]=usersSymbol[b];
 						break;
 				}	
 			}
			column=userChooseLoc;//a user's last choice's symbol of location(column). to use other function
	 		printTheGame(gameA,row1);	
	 		auto usersRow=i; //a user's last choice's symbol of location(row). to use other function	
		 	result=EndTheGameUpToDown(gameA,row1,column,usersSymbol,b,usersRow); 		
		 	if(result>=4){//checks whether the game is end
		 		printTheGame(gameA,row1);
		 		return 0;
			 }	
			result=EndTheGameLeftToRight(gameA,row1,column,usersSymbol,b,usersRow); 		
			if(result>=4){//checks whether the game is end
				printTheGame(gameA,row1);
			 	return 0;
			}
			result=EndTheGameRightDiagonal(gameA,row1,column,usersSymbol,b,usersRow);
			if(result>=4){//checks whether the game is end
			 	printTheGame(gameA,row1);
			 	return 0;
			}
			result=EndTheGameLeftDiagonal(gameA,row1,column,usersSymbol,b,usersRow);
			if(result>=4){//checks whether the game is end
			 	printTheGame(gameA,row1);
			 	return 0;
			 }
			cerr<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;
			return -1;
			}
			column=userChooseLoc;//a user's last choice's symbol of location(column). to use other function
			for(i=row1-1;i>=0;--i){//this loop put symbols in the empty space in the choose column(user's column)
	 			if(gameA[i][userChooseLoc]=='.'){
	 				gameA[i][userChooseLoc]=usersSymbol[b];	
	 				break;
	 			}	
	 		}
	 		printTheGame(gameA,row1);		
	 		auto usersRow=i; //a user's last choice's symbol of location(row). to use other function		
	 		result=EndTheGameUpToDown(gameA,row1,column,usersSymbol,b,usersRow);
		 	if(result>=4){//checks whether the game is end
		 		printTheGame(gameA,row1);
		 		return 0;
		 	}	
			result=EndTheGameLeftToRight(gameA,row1,column,usersSymbol,b,usersRow);	 		
		 	if(result>=4){//checks whether the game is end
		 		printTheGame(gameA,row1);
		 		return 0;
		 	}
		 	result=EndTheGameRightDiagonal(gameA,row1,column,usersSymbol,b,usersRow);
		 	if(result>=4){//checks whether the game is end
		 		printTheGame(gameA,row1);
		 		return 0;
		 	}
		 	result=EndTheGameLeftDiagonal(gameA,row1,column,usersSymbol,b,usersRow);
		 	if(result>=4){//checks whether the game is end
		 		printTheGame(gameA,row1);
		 		return 0;
		 	}
	 		if(b==1) b=0;
	 		else b=1;
	 		result=0;
	 		column=0;
			}
		return 0;
}	

