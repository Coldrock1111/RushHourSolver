#include <iostream>
#include <cmath>
#include <cstdlib>
#include <string>
#include <string.h>
#include <fstream>

using namespace std;
int main()
{
    //0=empty, 1=vertical 2 length, 2=horizontal 2 length, 3=vertical 3 length, 4=horizontal 3 length
    
    string initialBoard;

    
    string row1 = "444113";
    string row2 = "122113";
    string row3 = "100223"; //goal here
    string row4 = "220000";
    string row5 = "001122";
    string row6 = "221122";
    initialBoard = row1 + row2 + row3 + row4 + row5 + row6;
    
    
    ifstream inputFile;
    ofstream outputFile;
    inputFile.open("Text.txt");
    //inputFile >> initialBoard;
    inputFile.close();
    
    string activeBoards[12000];
    string activeMoveList[12000];
    string currentBoard;
    string checkBoard;
    string availableMoves = "";
    string pathMoveList;

    int activeBoardsUnused = 1;
    int availableMoveCount; 
    int availableMovesStringIndex;
    int moveFromIndex;
    int moveToDistance;
    int currentBoardIndex = -1;
    char moveValue;
    bool pathFound = false;

    activeBoards[0] = initialBoard;
    while (!pathFound) 
    {
        int x = 0;
        while (activeBoardsUnused < 11999)
        {
            currentBoardIndex++;
            currentBoard = activeBoards[currentBoardIndex];
            availableMoveCount = 0;
            availableMoves = "";
            for (int index = 0; index < 36; index++) 
            {
                if (currentBoard[index] == '0') 
                {
                    if (!(index < 12))
                    {
                        if (currentBoard[index - 6] % 2 == 1) 
                        {
                            for (int i = 0; i <= (((currentBoard[index - 6] - 48) - 1) / 2) + 1; i++)
                            {
                                if (index - (6*i+6)> 9) { availableMoves += to_string(index - (6 * i + 6)); availableMoves += "+6"; }
                                else 
                                { 
                                    availableMoves += "0"; 
                                    availableMoves += to_string(index - (6 * i + 6));
                                    availableMoves += "+6";
                                }
                            }
                            availableMoves += ":";
                            availableMoveCount++;
                        }
                    }
                    if (!(index > 24))
                    {
                        if (currentBoard[index + 6] % 2 == 1)
                        {
                            for (int i = 0; i <= (((currentBoard[index + 6] - 48) - 1) / 2)+1; i++)
                            {
                                if (index + (6 * i+ 6) > 9) { availableMoves += to_string(index + (6 * i + 6)); availableMoves += "-6"; }
                                else 
                                {
                                    availableMoves += "0";
                                    availableMoves += to_string(index + (6 * i + 6));
                                    availableMoves += "-6";
                                }
                            }
                            availableMoves += ":";
                            availableMoveCount++;
                        }
                    }
                    if (!(index % 6 == 0) ) 
                    {
                        if ((currentBoard[index - 1]) % 2 == 0 && currentBoard[index - 1] - 48 != 0)
                        {
                            for (int i = 0; i <= (((currentBoard[index - 1] - 48) / 2)); i++)
                            {
                                if (index - i - 1> 9) { availableMoves += to_string(index - (i + 1)); availableMoves += "+1"; }
                                else 
                                {
                                    availableMoves += "0"; 
                                    availableMoves += to_string(index - (i + 1));
                                    availableMoves += "+1"; 
                                }
                            }
                            availableMoves += ":";
                            availableMoveCount++;
                        }
                    }
                    if (!(index % 6 == 5))
                    {
                        if ((currentBoard[index + 1]) % 2 == 0 && (currentBoard[index + 1] - 48 != 0))
                        {
                            for (int i = 0; i <= (((currentBoard[index + 1]-48) / 2)); i++)
                            {
                                if (index + i + 1> 9) { availableMoves += to_string(index + (i + 1)); availableMoves += "-1"; }
                                else 
                                { 
                                    availableMoves += "0"; 
                                    availableMoves += to_string(index + (i + 1));
                                    availableMoves += "-1"; 
                                }
                            }
                            availableMoves += ":";
                            availableMoveCount++;
                        }
                    }
                }
            }         
            availableMovesStringIndex = 0;
            for (int i = 0; i < availableMoveCount; i++) 
            {
                checkBoard = currentBoard;
                while (availableMoves[availableMovesStringIndex] != ':') 
                {
                    moveFromIndex = (availableMoves[availableMovesStringIndex] - 48) * 10 + (availableMoves[availableMovesStringIndex+1] - 48);
                    if (availableMoves[availableMovesStringIndex+2] == '-') moveToDistance = -1 * (availableMoves[availableMovesStringIndex + 3] - 48);
                    else moveToDistance = (availableMoves[availableMovesStringIndex + 3] - 48);
                    moveValue = checkBoard[moveFromIndex];
                    checkBoard[moveFromIndex] = '0';
                    checkBoard[moveFromIndex + moveToDistance] = moveValue;
                    availableMovesStringIndex += 4;
                }
                for (int j = 0; j < activeBoardsUnused; j++) 
                {
                    if (checkBoard == activeBoards[j]) 
                    {
                        j = activeBoardsUnused;
                    }
                    else if (j == activeBoardsUnused - 1) 
                    {
                        activeBoards[activeBoardsUnused] = checkBoard;
                        activeMoveList[activeBoardsUnused] = activeMoveList[currentBoardIndex] + availableMoves[availableMovesStringIndex - 4] + availableMoves[availableMovesStringIndex - 3] + availableMoves[availableMovesStringIndex - 2] + availableMoves[availableMovesStringIndex - 1];
                        activeBoardsUnused++;
                    }
                }
                availableMovesStringIndex++;
                for (int j = 17; j > 12; j--) 
                {
                    if (checkBoard[j] != '0') 
                    {
                        if (checkBoard[j] == '2') 
                        {
                            pathFound = true;
                            pathMoveList += activeMoveList[activeBoardsUnused - 1];
                            activeBoardsUnused = 12000;
                            i = availableMoveCount;
                        }
                        j = 12;
                    }
                }
            }
        }
        if (!pathFound) 
        {
            activeBoards[0] = activeBoards[11998];
            pathMoveList = activeMoveList[11998];
            activeBoardsUnused = 1;
            currentBoardIndex = -1;
        }
    }

    cout << pathMoveList << endl;
    outputFile.open("output.txt");
    outputFile << pathMoveList;
    outputFile.close();

    for (int i = 0; i < pathMoveList.size(); i+=4) 
    {
        cout << "(" << ((pathMoveList[i] - 48) * 10 + (pathMoveList[i + 1] - 48)) % 6 + 1 << ", " << ((pathMoveList[i] - 48) * 10 + (pathMoveList[i + 1] - 48)) / 6 + 1<< ")";

        if (pathMoveList[i + 2] == '-') 
        {
            if (pathMoveList[i + 3] == '1') 
            {
                cout << " " << "left";
            }
            else if (pathMoveList[i + 3] == '6')
            {
                cout << " " << "up";
            }
        }
        else 
        {
            if (pathMoveList[i + 3] == '1')
            {
                cout << " " << "right";
            }
            else if (pathMoveList[i + 3] == '6')
            {
                cout << " " << "down";
            }
        }
        cout << " : ";
        if (i % 10 == 0) cout << endl;
    }

    cout << endl << pathMoveList.length() / 4 << endl;

    system("PAUSE");
}
