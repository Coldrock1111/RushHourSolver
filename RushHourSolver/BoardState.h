
#include <iostream>
using namespace std;
#pragma once

class BoardState
{
public:	
	int boardArray[6][6];
	string solutionString;

	BoardState();
	BoardState(int boardArray[6][6]);
	BoardState(int boardArray[6][6], string solutionString);

	void SetState(int boardArray[6][6]);
	string AvailableMoves();
	BoardState ApplyMove(string move);

};

