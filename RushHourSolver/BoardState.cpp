#include <iostream>
#include "BoardState.h"
#include <string>
using namespace std;

//standard constructor
BoardState::BoardState() 
{
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			boardArray[y][x] = 0;
		}
	}
}
//constructor for a given board (used for initial board)
BoardState::BoardState(int boardArray[6][6])
{
	for (int x = 0; x < 6; x++) 
	{
		for (int y = 0; y < 6; y++) 
		{
			this->boardArray[y][x] = boardArray[y][x];
		}
	}
}
//constructor given board and solution path. Used when propogating next move
BoardState::BoardState(int boardArray[6][6], string solutionString)
{
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			this->boardArray[y][x] = boardArray[y][x];
		}
	}
	this->solutionString = solutionString;
}
//sets the board state
void BoardState::SetState(int boardArray[6][6])
{
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			this->boardArray[y][x] = boardArray[y][x];
		}
	}
}
//returns all available moves from the board state
string BoardState::AvailableMoves() 
{
	string moves = "";

	//loop through and check for all empty spaces
	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			if (boardArray[y][x] == 0) 
			{
				//edge case handling
				if (x > 1) 
				{
					//if horizontal and to the right, move left is available
					if ((boardArray[y][x - 1]) % 2 == 0 && boardArray[y][x - 1] != 0)
					{
						moves += to_string(y);
						moves += to_string(x - 1);
						moves += 'r';
					}
				}
				if (x < 4)
				{
					if ((boardArray[y][x + 1]) % 2 == 0 && boardArray[y][x + 1] != 0)
					{
						moves += to_string(y);
						moves += to_string(x + 1);
						moves += 'l';
					}
				}
				if (y > 1)
				{
					if ((boardArray[y-1][x]) % 2 == 1 && boardArray[y - 1][x] != 0)
					{
						moves += to_string(y - 1);
						moves += to_string(x);
						moves += 'd';
					}
				}
				if (y < 4)
				{
					if ((boardArray[y+1][x]) % 2 == 1 && boardArray[y + 1][x] != 0)
					{
						moves += to_string(y + 1);
						moves += to_string(x);
						moves += 'u';
					}
				}
			}

		}
	}
	return moves;
}
//returns a new BoardState from a move
BoardState BoardState::ApplyMove(string move) 
{
	//a given move contains an x and y coordinate and direction
	int x = move[1] - 48;
	int y = move[0] - 48;
	int length;
	int output[6][6];

	for (int x = 0; x < 6; x++)
	{
		for (int y = 0; y < 6; y++)
		{
			output[y][x] = boardArray[y][x];
		}
	}

	//check direction
	switch (move[2])
	{
	case 'r':
		//find length( 1/2 -> 2, 3/4 -> 3)
		length = (boardArray[y][x] + 3) / 2;
		for (int i = 0; i < length; i++) 
		{
			//replace the coordinates shifted 1 unit right with desired value
			output[y][x - i + 1] = boardArray[y][x];
		}
		//replace the 'back' coordinate to empty
		output[y][x - length + 1] = 0;
		break;

	case 'l':
		length = (boardArray[y][x] + 3) / 2;
		for (int i = 0; i < length; i++)
		{
			output[y][x + i - 1] = boardArray[y][x];
		}
		output[y][x + length - 1] = 0;
		break;

	case 'u':
		length = (boardArray[y][x] + 3) / 2;
		for (int i = 0; i < length; i++)
		{
			output[y + i - 1][x] = boardArray[y][x];
		}
		output[y + length - 1][x] = 0;
		break;

	case 'd':
		length = (boardArray[y][x] + 3) / 2;
		for (int i = 0; i < length; i++)
		{
			output[y - i + 1][x] = boardArray[y][x];
		}
		output[y - length + 1][x] = 0;
		break;

	default:
		break;
	}
	//store the new board array and updated solution into an object to be returned
	BoardState returnObj(output, solutionString + move);
	return returnObj;

}