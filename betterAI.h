#include "board.h"

#define EMPTY ' '
#define SIZE 3
#define MAX_DEPTH 9

int evaluate(); 
bool isMovesLeft(); 
int minimax(int depth, bool isMax, int alpha, int beta); 
void AI();  

int evaluate() {
    int score = 0;
    char winChar;
    if (checkForWin(&winChar)) {
        score = (winChar == game.Player) ? -10 : 10;
    }
    return score;
}

bool isMovesLeft() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == EMPTY) return true;
        }
    }
    return false;
}

int minimax(int depth, bool isMax, int alpha, int beta) {
    int score = evaluate();

    if (score == 10) return score - depth; 
    if (score == -10) return score + depth;
    if (!isMovesLeft()) return 0; 

    if (isMax) {
        int best = INT_MIN;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (arr[i][j] == EMPTY) {
                    arr[i][j] = game.AI; 
                    int val = minimax(depth + 1, false, alpha, beta);
                    arr[i][j] = EMPTY; 
                    
                    best = (val > best) ? val : best; 
                    alpha = (alpha > best) ? alpha : best;

                    if (beta <= alpha) break;  // Prune
                }
            }
        }
        return best;
    } else {
        int worst = INT_MAX;

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (arr[i][j] == EMPTY) {
                    arr[i][j] = game.Player;
                    int val = minimax(depth + 1, true, alpha, beta);
                    arr[i][j] = EMPTY;

                    worst = (val < worst) ? val : worst;
                    beta = (beta < worst) ? beta : worst;

                    if (beta <= alpha) break;  // Prune
                }
            }
        }
        return worst;
    }
}

void AI() {
    int bestVal = INT_MIN;
    int bestX = -1;
    int bestY = -1;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (arr[i][j] == EMPTY) {
                arr[i][j] = game.AI; 
                int currMoveVal = minimax(0, false, INT_MIN, INT_MAX); 
                arr[i][j] = EMPTY;

                if (currMoveVal > bestVal) {
                    bestVal = currMoveVal;
                    bestX = i;
                    bestY = j;
                }
            }
        }
    }

    if (bestX != -1 && bestY != -1) {
        arr[bestX][bestY] = game.AI;
    }
}
