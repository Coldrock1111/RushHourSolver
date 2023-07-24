#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <string.h>
#include <fstream>
#include "BoardState.h"

using namespace std;

bool CompareArrays(int[6][6], int[6][6]);

int main() 
{
    int initialBoard[6][6] =
    {
        {0, 0, 4, 4, 4, 0},
        {0, 0, 0, 3, 1, 0},
        {2, 2, 0, 3, 1, 0},
        {0, 0, 0, 3, 1, 0},
        {0, 0, 0, 0, 1, 0},
        {0, 0, 0, 2, 2, 0}
    };

    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("Puzzle.txt");
    outputFile.open("SolutionMoves.txt");
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
            for (int j = 5; j >= 1; j--)
            {
                if (allBoards[availableBoardsIndex].boardArray[2][j] == 2)
                {
                    solutionFound = true;
                    solutionString = allBoards[availableBoardsIndex].solutionString;
                    solutionString += "2";
                    solutionString += to_string(j-1);
                    switch (j) 
                    {
                    case 1:
                        solutionString += "L";
                        break;
                    case 2:
                        solutionString += "l";
                        break;
                    case 3:
                        solutionString += "D";
                        break;
                    case 4:
                        solutionString += "d";
                        break;
                    }
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
    for (int i = 0; i < solutionString.length() - 6; i+=3)
    {
        int checkCoordinates[2] = { solutionString[i] - 48, solutionString[i+1] - 48 };
        int nextCoordinates[2] = { solutionString[i+3] - 48, solutionString[i + 4] - 48 };
        int offset = 0;
        switch (solutionString[i + 2]) 
        {
        case 'l':
            offset++;
        case 'D':
            offset++;
        case 'd':
            offset++;
            if (nextCoordinates[0] == checkCoordinates[0] && nextCoordinates[1] == checkCoordinates[1] + offset) 
            {
                solutionString.erase(i + 3, 3);
                switch (offset) 
                {
                case 1:
                    solutionString[i + 2] = 'D';
                    break;
                case 2:
                    solutionString[i + 2] = 'l';
                    break;
                case 3:
                    solutionString[i + 2] = 'L';
                    break;
                }
                i -= 3;
            }
            break;
        case 'j':
            offset++;
        case 'A':
            offset++;
        case 'a':
            offset++;
            if (nextCoordinates[0] == checkCoordinates[0] && nextCoordinates[1] == checkCoordinates[1] - offset)
            {
                solutionString.erase(i + 3, 3);
                switch (offset)
                {
                case 1:
                    solutionString[i + 2] = 'A';
                    break;
                case 2:
                    solutionString[i + 2] = 'j';
                    break;
                case 3:
                    solutionString[i + 2] = 'J';
                    break;
                }
                i -= 3;
            }
            break;
        case 'i':
            offset++;
        case 'W':
            offset++;
        case 'w':
            offset++;
            if (nextCoordinates[0] == checkCoordinates[0] - offset && nextCoordinates[1] == checkCoordinates[1])
            {
                solutionString.erase(i + 3, 3);
                switch (offset)
                {
                case 1:
                    solutionString[i + 2] = 'W';
                    break;
                case 2:
                    solutionString[i + 2] = 'i';
                    break;
                case 3:
                    solutionString[i + 2] = 'I';
                    break;
                }
                i -= 3;
            }
            break;
        case 'k':
            offset++;
        case 'S':
            offset++;
        case 's':
            offset++;
            if (nextCoordinates[0] == checkCoordinates[0] + offset && nextCoordinates[1] == checkCoordinates[1])
            {
                solutionString.erase(i + 3, 3);
                switch (offset)
                {
                case 1:
                    solutionString[i + 2] = 'S';
                    break;
                case 2:
                    solutionString[i + 2] = 'k';
                    break;
                case 3:
                    solutionString[i + 2] = 'K';
                    break;
                }
                i -= 3;
            }
            break;
        }
    }
    cout << solutionString.length() / 3 << endl;
    for (int i = 0; i < solutionString.length(); i++) 
    {
        outputFile << solutionString[i] << " ";
        outputFile << solutionString[++i] << " ";
        outputFile << solutionString[++i] << endl;
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