#include <iostream>
#include "T2.h"
using namespace std;

int main()
{	
	int playFlag=1;

	while(playFlag)
	{
		// TicTacToe matrix
		TicTacToe T3;

		while((!T3.victoryFlag)&&(T3.emptyElements>0))
		{	// User's Turn
			T3.getUserInput();					 

			if((!T3.victoryFlag)&&(T3.emptyElements>0))
			{	cout << "My Turn :";
				calcMyInput(T3.T);		
				T3.display();
				T3.emptyElements--; // one less empty location
				T3.victoryFlag = checkForVictory(T3.T);
			}
		}

		if(T3.victoryFlag==1)
			cout << "You Win!!" << endl;
		else if(T3.victoryFlag==-1)
			cout << "I win!!" << endl;
		else//no more empty spaces
			cout << "tame draw" << endl << endl;

		cout << "Do you want to play again? press 'y' for yes, any other key for no : ";
		char userInput;
		cin >> userInput;
		if(userInput!='y')
			playFlag=0;
	}
	return 0;
}