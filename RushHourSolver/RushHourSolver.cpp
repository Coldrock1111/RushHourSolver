#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <string.h>
#include <fstream>
#include "BoardState.h"

//I added comments just for you mark :)

using namespace std;

bool CompareArrays(int[6][6], int[6][6]);

int main() 
{
    int initialBoard[6][6] =
    {
        {3, 1, 2, 2, 1, 0},
        {3, 1, 1, 0, 1, 3},
        {3, 0, 1, 2, 2, 3},
        {4, 4, 4, 1, 0, 3},
        {0, 0, 1, 1, 2, 2},
        {2, 2, 1, 2, 2, 0}
    };

    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("Text.txt");
    /*
    for (int x = 0; x < 6; x++) 
    {
        for (int y = 0; y < 6; y++) 
        {
            inputFile >> initialBoard[y][x];
        }
    }
    */
    inputFile.close();

    bool solutionFound = false;
    int allBoardsIndex = 0;
    int availableBoardsIndex = 1;
    string currentMoves;
    string solutionString;
    string move;

    //store all board objects in an effectively infinite array in the heap
    BoardState * allBoards = new BoardState[100000];
    allBoards[0].SetState(initialBoard);



    while (!solutionFound) 
    {
        //store the list of all possible moves from the current board state
        currentMoves = allBoards[allBoardsIndex].AvailableMoves();
        for (int i = 0; i < currentMoves.length(); i+=3) 
        {
            //extract a single move from the list
            move = "";
            move += currentMoves[i];
            move += currentMoves[i + 1];
            move += currentMoves[i + 2];
            //apply the extracted move and store in the next available location
            allBoards[availableBoardsIndex] = allBoards[allBoardsIndex].ApplyMove(move);
            //check if solution has been found
            for (int j = 5; j > 1; j--)
            {
                if (allBoards[availableBoardsIndex].boardArray[2][j] == 2)
                {
                    solutionFound = true;
                    solutionString = allBoards[availableBoardsIndex].solutionString;
                    break;
                }
                else if (allBoards[availableBoardsIndex].boardArray[2][j] != 0) break;
            }
            if (solutionFound) break;
            //check if new board is a copy. if so, mark as open space
            for (int j = 0; j < availableBoardsIndex; j++) 
            {
                if (CompareArrays(allBoards[j].boardArray, allBoards[availableBoardsIndex].boardArray))
                {
                    availableBoardsIndex--;
                }
            }
            availableBoardsIndex++;
        }
        //move to next board
        allBoardsIndex++;
    }
    cout << solutionString << endl;
    system("PAUSE");
}
//no clue why its so difficult to compare arrays
bool CompareArrays(int first[6][6], int second[6][6])
{
    for (int i = 0; i < 6; i++) 
    {
        for (int j = 0; j < 6; j++) 
        {
            if (first[i][j] != second[i][j])
                return false;
        }
    }
    return true;
}