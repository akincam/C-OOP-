



#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "cell.h"
#include "connectfourabstract.h"
#include "connectfourplus.h"
#include "connectfourdiag.h"
#include "connectfourplusundo.h"
using namespace std;
using namespace ConnectFour;

int main(){


	char sm;//single ya da multi oyuna karar vermek için
	do{
		cout<<"PLUS /P/ DİAG /D/ UNDO /U/---->";
		cin>>sm;
		cout<<endl;
		if(cin.fail()){
			cin.clear();
			cin.ignore(999,'\n');
			cerr<<"Try again"<<endl;
		}
	}while(sm!='P'&&sm!='D'&&sm!='U');

	if(sm=='P'){
		ConnectFourPlus game;
		game.playGame();
	}	
		
	
	else if(sm=='D'){
		ConnectFourDiag game;
		game.playGame();
	}
	
	else if(sm=='U'){
		ConnectFourPlusUndo game;
		game.playGame();
	}

	return 0;
}
