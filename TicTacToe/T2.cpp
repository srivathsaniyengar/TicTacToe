#include <iostream>
using namespace std;

void dispT3(int T3[][3])
{
	cout << endl << endl;

	for(int i=0;i<3;i++)
	{ 
		// Convert 1=>X, -1=>O, 0=>' ' 		
		char dispT[3];
		for(int j=0;j<3;j++)
		{
			switch(T3[i][j])
			{
				case 0:
					dispT[j] = ' ';
					break;

				case 1:
					dispT[j] = 'X';
					break;

				case 2:
					dispT[j] = 'O';
					break;

				default:
					//error
					cout << "Error";
			}		
		}

		cout << "  " << dispT[0] << '|' << dispT[1]  << '|' << dispT[2] << endl << endl;
	}
}


void getUserInput(int T3[][3])
{
	int rowNumber, colNumber;
	
	while(1) // keep asking for input until you get correct input
	{	cout << "Enter row number followed by column number (0 based): " << endl;
		cin >> rowNumber >> colNumber;

		// Make sure the co-ordinates entered are valid
		if((rowNumber<3)&&(colNumber<3)&&(T3[rowNumber][colNumber]==0))
			break;
		else
			cout<<"Incorrect values" << endl;
	}

	// Enter User input
	T3[rowNumber][colNumber] = 1;
}

int checkForVictory(int T3[][3])
{
	int victoryFlag = 0;
	// 8 possible victory scenarios
	// row-wise
	for(int i=0;i<3;i++)
	{
	 victoryFlag = victoryFlag||((T3[i][0]+T3[i][1]+T3[i][2])==3);
	}

	// column-wise
	for(int i=0;i<3;i++)
	{
	 victoryFlag = victoryFlag||((T3[0][i]+T3[1][i]+T3[2][i])==3);
	}

	// diagonal
	 victoryFlag = victoryFlag||((T3[0][0]+T3[1][1]+T3[2][2])==3);
	 victoryFlag = victoryFlag||((T3[0][2]+T3[1][1]+T3[2][0])==3);


return victoryFlag;
}


int main()
{
	// TicTacToe matrix
	int T3[3][3] = {0};

	// Display empty
	dispT3(T3);

	int victoryFlag=0;

	while(!victoryFlag)
	{	// Ask for user input
		getUserInput(T3);
		dispT3(T3);
	}

	return 0;
}