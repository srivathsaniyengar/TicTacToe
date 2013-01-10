#include<iostream>
using namespace std;

int checkForVictory(int T3[][3]);

class TicTacToe{	
	

public:
	int T[3][3], emptyElements, victoryFlag;

	// Constructor
	TicTacToe()
	{	// set all elements in T to 0
		for(int i=0;i<3;i++)
			for(int j=0; j<3;j++)
				T[i][j] = 0;

		// All empty elements
		emptyElements = 9;

		// victoryFlag set to 0
		victoryFlag = 0;
	};

	void display()
	{
		cout << endl << endl;

		for(int i=0;i<3;i++)
		{ 
			// Convert 1=>X, -1=>O, 0=>' ' 		
			char dispT[3];
			for(int j=0;j<3;j++)
			{
				switch(T[i][j])
				{
					case 0:
						dispT[j] = ' ';
						break;

					case 1:
						dispT[j] = 'X';
						break;

					case -1:
						dispT[j] = 'O';
						break;

					default:
						//error
						cout << "Error in display";
				}		
			}

			cout << "  " << dispT[0] << '|' << dispT[1]  << '|' << dispT[2] << endl << endl;
		}
	}


	void getUserInput()
	{
		int rowNumber, colNumber;
		
		while(1) // keep asking for input until you get correct input
		{	cout << "Enter row number followed by column number (0 based): " << endl;
			cin >> rowNumber >> colNumber;

			// Make sure the co-ordinates entered are valid
			if((rowNumber<3)&&(colNumber<3)&&(T[rowNumber][colNumber]==0))
				break;
			else
				cout<<"Incorrect values" << endl;
		}

		// Enter User input
		T[rowNumber][colNumber] = 1;
		emptyElements--; // one less empty element

		// display the matrix
		display();

		// Check for Victory
		victoryFlag = checkForVictory(T);
	}
};

int calcRowSum(int T3[][3], int rowNumber)
{	return(T3[rowNumber][0]+T3[rowNumber][1]+T3[rowNumber][2]);}

int calcColSum(int T3[][3], int colNumber)
{	return(T3[0][colNumber]+T3[1][colNumber]+T3[2][colNumber]);}

int calcDiagSum(int T3[][3], int diagNumber)
{
	int diagSum;
	switch(diagNumber)
	{
		case 1:
				diagSum = T3[0][0]+T3[1][1]+T3[2][2];
				break;
		case 2:
				diagSum = T3[0][2]+T3[1][1]+T3[2][0];
				break;
		default:
			cout << "error in diagSum Call";
	}
	return(diagSum);
}






struct checkSumReturn{
	int victoryFlag, rowNumber,colNumber, diagNumber;
};

checkSumReturn checkForSumValue(int T3[][3], int sumValue)
{
		
	checkSumReturn returnStruct;
	returnStruct.victoryFlag=0; 
	//int victoryFlag=0;
	// victoryFlag=0 => no victory
	// victoryFlag=1 => user victory 
	// victoryFlag=-1 => my victory

	// 8 possible victory scenarios
	// row-wise
	for(int i=0;i<3;i++)
	{	int rowSum=calcRowSum(T3,i);
		if((rowSum==sumValue)||(rowSum==-sumValue))
		{
			if(rowSum==sumValue)
				returnStruct.victoryFlag = 1;
			else //rowSum==-sumValue
				returnStruct.victoryFlag = -1;
			// return row Number
			returnStruct.rowNumber = i;
			returnStruct.colNumber = -1;
			returnStruct.diagNumber = -1;
			return(returnStruct);
		}
	}

	// column-wise
	for(int i=0;i<3;i++)
	{ int colSum = calcColSum(T3,i);
		if((colSum==sumValue)||(colSum==-sumValue))
		{
			if(colSum==sumValue)
				returnStruct.victoryFlag = 1;
			else //colSum==-sumValue
				returnStruct.victoryFlag = -1;
			// return col Number
			returnStruct.rowNumber = -1;
			returnStruct.colNumber = i;
			returnStruct.diagNumber = -1;
			return(returnStruct);
		}
	}

	// diagonals
	{
		 int diag1Sum = calcDiagSum(T3,1);
		 if((diag1Sum==sumValue)||(diag1Sum==-sumValue))
		{
			if(diag1Sum==sumValue)
				returnStruct.victoryFlag = 1;
			else //diag1Sum==-sumValue
				returnStruct.victoryFlag = -1;
			// return -1 for both 
			returnStruct.rowNumber = -1;
			returnStruct.colNumber = -1;
			returnStruct.diagNumber = 1;
			return(returnStruct);
		}
		 
		 int diag2Sum = calcDiagSum(T3,2);
		 if((diag2Sum==sumValue)||(diag2Sum==-sumValue))
		{
			if(diag2Sum==sumValue)
				returnStruct.victoryFlag = 1;
			else //diag1Sum==-sumValue
				returnStruct.victoryFlag = -1;
			// return -1 for both 
			returnStruct.rowNumber = -1;
			returnStruct.colNumber = -1;
			returnStruct.diagNumber = 2;
			return(returnStruct);
		}
	}

	// no sumValue equivalence. victoryFlag=0
	return(returnStruct);
}

int checkForVictory(int T3[][3])
{	
	// victoryFlag=0 => no victory
	// victoryFlag=1 => user victory 
	// victoryFlag=2 => my victory
	checkSumReturn returnStruct = checkForSumValue(T3,3);
	

	return(returnStruct.victoryFlag);
}


void calcMyInput(int T3[][3])
{
	
	// calculate to check if there is impending victory
	checkSumReturn returnStruct = checkForSumValue(T3,2);
	if(returnStruct.victoryFlag) // impending victory
	{	//block it or win it
		//check if row victory
		if((returnStruct.colNumber==-1)&&(returnStruct.diagNumber==-1))
		{	// find empty element in row
			for(int i=0; i<3;i++)
			{	if(T3[returnStruct.rowNumber][i]==0)
				{	T3[returnStruct.rowNumber][i]=-1;
					return;
				}
			}
		} // end row victory


		//check if col victory
		if((returnStruct.rowNumber==-1)&&(returnStruct.diagNumber==-1))
		{	// find empty element in col
			for(int i=0; i<3;i++)
			{	if(T3[i][returnStruct.colNumber]==0)
				{	T3[i][returnStruct.colNumber]=-1;
					return;
				}
			}
		} // end col victory

		//check if diag victory
		if((returnStruct.colNumber==-1)&&(returnStruct.rowNumber==-1))
		{	
			if(returnStruct.diagNumber==1)// forward diagonal
			{	// find empty element in diagonal
				for(int i=0; i<3;i++)
				{	if(T3[i][i]==0)
					{	T3[i][i]=-1;
						return;
					}
				}
			}
			else // reverse diagonal
			{	// find empty element in diagonal
				for(int i=0; i<3;i++)
				{	if(T3[i][2-i]==0)
					{	T3[i][2-i]=-1;
						return;
					}
				}
			}			
		} // end diag victory

	} // if impending victory
	else // no impending victory
	{	
		// occupy center element if empty
		if(T3[1][1]==0)
		{	T3[1][1]=-1;
			return;
		}
		else
		{
			// find the first empty element
			for(int i=0; i<3; i++)
				for(int j=0; j<3; j++)
				{	if(T3[i][j]==0)
					{	T3[i][j]=-1;
						return;
					}
				}// end for
		}// end if/else inside no impending victory
	}// end if/else impending victory check
}