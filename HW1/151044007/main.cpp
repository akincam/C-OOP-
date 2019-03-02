#include <iostream>
using namespace std;

const int COLUMN= 20;

int rowNumber();
//Returns the row of the gameArea according to the user's input

int askTheLocation(int row,int userSequence);
//Returns the column location according to the user's input value
//row is taken from function of int rowNumber() 

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
int computerVsUser(char gameA[][COLUMN],char usersSymbol[2],int row1);
//Provides playing game user-computer

int computerUser(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline);
//contains computer's moves to win the game or to prevent win the user


int main(){
	int row=0;
	int i=0,j=0;
	int userSeq=0;//to check the users queue
	int b=0; //change the symbols according to userSeq
	int cntrl=0; //to check whether a column is free or full
	int usersRow=0; //keep the row of user's choice
	int userChooseLoc=-1;
	char users[2]; users[0]='X',users[1]='O';
	int column=0;
	int result=0;
	char gameChoice=0;
	row=rowNumber();
		
	char gameArea[COLUMN][COLUMN];
	
	int allDotNums=row*row;//all dot numbers in the game area
	for(i=0;i<row;++i)//put dots game Area's locations
		for(j=0;j<row;++j)
			gameArea[i][j]='.';
			
	for(i=0;i<COLUMN;++i)//to put Null out of the game area according to user's input row
		for(j=0;j<COLUMN;++j){
			if(gameArea[i][j]!='.')
				gameArea[i][j]='\0';	
		}
		
	while(gameChoice!='p'&&gameChoice!='c'&&gameChoice!='P'&&gameChoice!='C'){//to determine how to play	
		cout<<endl<<"Press 'P' for MULTİPLAYER or Press 'C' for COMPUTER vs USER->>>";	
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
	printTheGame(gameArea,row);
	if(gameChoice=='c'||gameChoice=='C')
		computerVsUser(gameArea,users, row);
	while(1&&gameChoice=='P'||gameChoice=='p'){//the while loop ends either a user win or the gameboard is full
		if(userSeq==0){//if user Sequence is x userSeq=0 and for the user's symbol b=0 
			userChooseLoc=askTheLocation(row,userSeq);
			for(i=0;i<row;++i){//this loop controls  wheter is free area in the choosen location
					if(gameArea[i][userChooseLoc]=='.'){
						cntrl=1;
						allDotNums -=1;	
						break;
					}		
				else
					cntrl=0;
				}			
			while(cntrl==0){
				cout<<endl<<"This column is full choose another column"<<endl<<endl<<endl;
				userChooseLoc=askTheLocation(row,userSeq);
				for(i=0;i<row;++i){//this loop controls  wheter is free area in the choosen location
					if(gameArea[i][userChooseLoc]=='.'){
						cntrl=1;
						allDotNums -=1;	
						break;
					}		
				else
					cntrl=0;
				}
			}			
			b=0; //use symbol X for user1
			++userSeq; 
		}	
		else{//if user Sequence is o userSeq=1 and for the user's symbol b=1
			userChooseLoc=askTheLocation(row,userSeq);
			for(i=0;i<row;++i){
					if(gameArea[i][userChooseLoc]=='.'){
						cntrl=1;
						allDotNums -=1;	
						break;
					}		
				else
					cntrl=0;
				}			
			while(cntrl==0){
				cout<<endl<<"This column is full choose another column"<<endl<<endl<<endl;
				userChooseLoc=askTheLocation(row,userSeq);
				for(i=0;i<row;++i){
					if(gameArea[i][userChooseLoc]=='.'){
						cntrl=1;
						allDotNums -=1;	
						break;
					}		
				else
					cntrl=0;
				}
			}			
				--userSeq;
				b=1;
			}			
		
		if(allDotNums==0){//if area is full
			for(i=row-1;i>=0;--i){
 				if(gameArea[i][userChooseLoc]=='.'){
 					gameArea[i][userChooseLoc]=users[b];
					
 					break;
 				}	
 			}
 			column=userChooseLoc;//a user's last choice's symbol of location(column). to use other function
 			printTheGame(gameArea,row);	
 			 usersRow=i; //a user's last choice's symbol of location(row). to use other function		
	 		result=EndTheGameUpToDown(gameArea,row,column,users,b,usersRow);
	 		
	 		if(result>=4){//checks whether the game is end
	 			printTheGame(gameArea,row);
	 			return 0;
	 		}	
			result=EndTheGameLeftToRight(gameArea,row,column,users,b,usersRow);
			 		
	 		if(result>=4){//checks whether the game is end
	 			printTheGame(gameArea,row);
	 			return 0;
	 		}
	 		result=EndTheGameRightDiagonal(gameArea,row,column,users,b,usersRow);
	 		if(result>=4){//checks whether the game is end
	 			printTheGame(gameArea,row);
	 			return 0;
	 		}
	 		result=EndTheGameLeftDiagonal(gameArea,row,column,users,b,usersRow);
	 		if(result>=4){//checks whether the game is end
	 			printTheGame(gameArea,row);
	 			return 0;
	 		}
			cout<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;
			return -1;
		}
		column=userChooseLoc;//a user's last choice's symbol of location(column). to use other function

		for(i=row-1;i>=0;--i){//this loop put symbols in the empty space in the choose column(user's column)
 			if(gameArea[i][userChooseLoc]=='.'){
 				gameArea[i][userChooseLoc]=users[b];
 				userChooseLoc=-1;	
 				break;
 			}	
 		}
 		printTheGame(gameArea,row);		
 		usersRow=i; //a user's last choice's symbol of location(row). to use other function		
 		result=EndTheGameUpToDown(gameArea,row,column,users,b,usersRow);
 		
 		if(result>=4){//checks whether the game is end
 			printTheGame(gameArea,row);
 			return 0;
 		}	
		result=EndTheGameLeftToRight(gameArea,row,column,users,b,usersRow);
		 		
 		if(result>=4){//checks whether the game is end
 			printTheGame(gameArea,row);
 			return 0;
 		}
 		result=EndTheGameRightDiagonal(gameArea,row,column,users,b,usersRow);
 		if(result>=4){//checks whether the game is end
 			printTheGame(gameArea,row);
 			return 0;
 		}
 		result=EndTheGameLeftDiagonal(gameArea,row,column,users,b,usersRow);
 		if(result>=4){//checks whether the game is end
 			printTheGame(gameArea,row);
 			return 0;
 		}
 		if(b==1)
 			b=0;
 		else
 			b=1;
 		result=0;
 		column=0;
 	}	
	return 0;	
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
		}
		else
			control=true;
	}while(row<4||row%2!=0||row>20||control==false);	
	
	return row;
}
int askTheLocation(int row ,int userSequence){
	char locationOfLetter=-1;
	int locationOfNum=0;	
	char letters[20]={'A', 'B', 'C', 'D', 'E' ,'F', 'G' ,'H', 'I', 'J' ,'K', 'L', 'M' ,'N', 'O','P', 'Q', 'R', 'S','T'};
	while(locationOfLetter-'a'<0||locationOfLetter-'a'>row-1){
		cout<<"User"<<userSequence+1<<" Choose a location from A to "<<letters[row-1]<<"  -->>";
		cin>>locationOfLetter;
		if(locationOfLetter>='A'&&locationOfLetter<='Z')
			locationOfLetter =locationOfLetter+32;
		cout<<endl;
	}
	
	locationOfNum=locationOfLetter-'a';
	return locationOfNum;		
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
int computerUser(char gameA[][COLUMN],int row1,int usersloc,char usersSymbol[2],int gameSeq,int usersline){

	int checkLeftToRight=EndTheGameLeftToRight(gameA,row1,usersloc,usersSymbol,0,usersline);
	int checkUptoDown=EndTheGameUpToDown(gameA,row1,usersloc,  usersSymbol,0, usersline);
	int checkRightDia=EndTheGameRightDiagonal(gameA,row1,usersloc,usersSymbol,0,usersline);
	int checkLeftDia=EndTheGameLeftDiagonal(gameA,row1,usersloc,usersSymbol,0,usersline);
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
			if(gameA[i][j]=='.'||gameA[i][j]=='O')
				return j+1;

		}
	}		
	return 8;

}
int computerVsUser(char gameA[][COLUMN],char usersSymbol[2],int row1){
	int column=-58;	
	int i=0,j=0;
	int cntrl=0;
	int allDotNums=row1*row1;
	int columnNumKeep=0;
	int usersRow=-58;
	int result=0;
	int playingSequence=0;
	int b=0;
	while(1){
		if(playingSequence==0){
			column=askTheLocation(row1,0);
			b=0;
			playingSequence +=1;
		}
		else{
			column=computerUser(gameA,row1,columnNumKeep,usersSymbol,b,usersRow);
			b=1;
			playingSequence -=1;
		}	
		for(i=0;i<row1;++i){
			if(gameA[i][column]=='.'){
				cntrl=1;
				allDotNums -=1;	
				break;
			}		
			else
				cntrl=0;
		}	
		if(cntrl==0){//if cntrl is 0 this means that column is full
			cout<<endl<<"This column is full choose another column"<<endl;
			column=askTheLocation(row1,0);							
			for(i=0;i<row1;++i){
				if(gameA[i][column]=='.'){
					cntrl=1;
					allDotNums -=1;		
					break;
				}		
				else
					cntrl=0;
			}		
		}
		if(allDotNums==0){//if area is full
			for(i=row1-1;i>=0;--i){
 				if(gameA[i][column]=='.'){
 					gameA[i][column]=usersSymbol[b];
				
 					break;
 				}	
 			}
 			usersRow=i;
 			columnNumKeep=column;
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
				cout<<endl<<"The gameBoard is full"<<endl<<"the end..."<<endl;
				return -1;
			}
		columnNumKeep=column;//a user's last choice's symbol of location(column). to use other function
		for(i=row1-1;i>=0;--i){//put the symbols epmty location in the choosen column
 			if(gameA[i][column]=='.'){
 				gameA[i][column]=usersSymbol[b];
 				column=-1;
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





