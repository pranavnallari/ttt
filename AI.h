// this is a simple AI that can play intelligent moves based on the state
// but as you play multiple games, you can see that it becomes very predictable.

#include "board.h"

#define EMPTY ' '
#define SIZE 3

bool canWinNextMove(char playerSymbol, int *winRow, int *winCol) {
    for (int row = 0; row < SIZE; row++) {
        if (arr[row][0] == playerSymbol && arr[row][1] == playerSymbol && arr[row][2] == EMPTY) {
            *winRow = row;
            *winCol = 2;
            return true;
        } else if (arr[row][0] == playerSymbol && arr[row][2] == playerSymbol && arr[row][1] == EMPTY) {
            *winRow = row;
            *winCol = 1;
            return true;
        } else if (arr[row][1] == playerSymbol && arr[row][2] == playerSymbol && arr[row][0] == EMPTY) {
            *winRow = row;
            *winCol = 0;
            return true;
        }
    }

    for (int col = 0; col < SIZE; col++) {
        if (arr[0][col] == playerSymbol && arr[1][col] == playerSymbol && arr[2][col] == EMPTY) {
            *winRow = 2;
            *winCol = col;
            return true;
        } else if (arr[0][col] == playerSymbol && arr[2][col] == playerSymbol && arr[1][col] == EMPTY) {
            *winRow = 1;
            *winCol = col;
            return true;
        } else if (arr[1][col] == playerSymbol && arr[2][col] == playerSymbol && arr[0][col] == EMPTY) {
            *winRow = 0;
            *winCol = col;
            return true;
        }
    }

    if (arr[0][0] == playerSymbol && arr[1][1] == playerSymbol && arr[2][2] == EMPTY) {
        *winRow = 2;
        *winCol = 2;
        return true;
    } else if (arr[0][0] == playerSymbol && arr[2][2] == playerSymbol && arr[1][1] == EMPTY) {
        *winRow = 1;
        *winCol = 1;
        return true;
    } else if (arr[1][1] == playerSymbol && arr[2][2] == playerSymbol && arr[0][0] == EMPTY) {
        *winRow = 0;
        *winCol = 0;
        return true;
    }

    if (arr[0][2] == playerSymbol && arr[1][1] == playerSymbol && arr[2][0] == EMPTY) {
        *winRow = 2;
        *winCol = 0;
        return true;
    } else if (arr[0][2] == playerSymbol && arr[2][0] == playerSymbol && arr[1][1] == EMPTY) {
        *winRow = 1;
        *winCol = 1;
        return true;
    } else if (arr[1][1] == playerSymbol && arr[2][0] == playerSymbol && arr[0][2] == EMPTY) {
        *winRow = 0;
        *winCol = 2;
        return true;
    }
    return false;
}

int heuristic[3][3] = {
    {3, 2, 3},
    {2, 4, 2},      // heuristic scores for every square
    {3, 2, 3}
};

void AI() {
    /*
        1. Winning Move :- First Priority is to check if there is a winning move.
        2. Blocking Move :- If there is no Winning move then Priority is to stop opponent from winning.
        3. Default :- Pick the move with the highest heuristics if there is no winning move.
    */
    int playerWinRow, playerWinCol;
    if (canWinNextMove(game.AI, &playerWinRow, &playerWinCol)) { // check for winning move
        arr[playerWinRow][playerWinCol] = game.AI;
        return;
    }
    int oppWinRow, oppWinCol;
    if (canWinNextMove(game.Player, &oppWinRow, &oppWinCol)) { // check for blocking move
        arr[oppWinRow][oppWinCol] = game.AI;
        return;
    }
    int max = 0;
    int move_row = -1;
    int move_col = -1;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (max < heuristic[i][j] && arr[i][j] == EMPTY) {
                max = heuristic[i][j];
                move_row = i;
                move_col = j;
            }
        }
    }
    if (move_col >= 0 && move_row >= 0) {
        arr[move_row][move_col] = game.AI;
        return;
    } 
}