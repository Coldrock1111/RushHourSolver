
#include <iostream>
using namespace std;
#pragma once

class BoardState
{
public:	
	int** boardArray;
	string solutionString;

	BoardState();
	BoardState(int** boardArray);
	BoardState(int** boardArray, string solutionString);

	void SetState(int** boardArray);
	string AvailableMoves();
	BoardState ApplyMove(string move);

};

