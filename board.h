#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>

#define X 'X'
#define O 'O'


/*

Checking Win Conditions

After each move (by player or AI), check if there is a winner or if the game is a draw.

AI Improvement (Optional)

To make the AI smarter, you can implement a basic strategy:

    Winning Move: Check if the AI can win on the next move (two of its symbols in a row).
    Blocking Move: Check if the AI needs to block the player from winning on the next move.
    Fallback to Random Move: If neither a winning move nor a blocking move is possible, make a random move.

*/

/*
move(y, x)
mvprintw(y, x, string, ...)
clear()
refresh()
WINDOW * win = newwin;
wrefresh
box()
wborder()
wprintw()
cbreak()  -> ctrl+c
raw()   -> takes all characters without any sequences
noecho() -> does not reflect what you type on the screen even after you refresh
attron() and attroff()
has_colors()
start_ncurses()
start_color()
init_pair()

*/

char arr[3][3];

struct GameInfo {
    char Player;
    char AI;
} game;

void board_init() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[i][j] = ' ';
        }
    }
}

void select_symbol(){
    char symbol;
    printf("Select Your Symbol\nX : Press X\nO : Press O\n");
    scanf("%c", &symbol);
    if (symbol != X && symbol != O) {
        printf("Invalid Symbol, Try Again ! \n");
        select_symbol();
    } else {
        if (symbol == X) {
            game.Player = X;
            game.AI = O;
        } else {
            game.Player = O;
            game.AI = X;
        }
    }
}

bool checkIfEmpty(int i, int j) {
    return arr[i][j] == ' ';
}

bool checkForWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (arr[i][0] == game.AI && arr[i][1] == game.AI && arr[i][2] == game.AI) {
            printf("You Lost\n");
            return true;
        } else if (arr[i][0] == game.Player && arr[i][1] == game.Player && arr[i][2] == game.Player) {
            printf("You Won\n");
            return true;
        }

        // Check columns
        if (arr[0][i] == game.AI && arr[1][i] == game.AI && arr[2][i] == game.AI) {
            printf("You Lost\n");
            return true;
        } else if (arr[0][i] == game.Player && arr[1][i] == game.Player && arr[2][i] == game.Player) {
            printf("You Won\n");
            return true;
        }
    }

    // Check diagonals
    if (arr[0][0] == game.AI && arr[1][1] == game.AI && arr[2][2] == game.AI){
        printf("You Lost\n");
        return true;
    } else if (arr[0][0] == game.Player && arr[1][1] == game.Player && arr[2][2] == game.Player) {
        printf("You Won\n");
        return true;
    }
    if (arr[0][2] == game.AI && arr[1][1] == game.AI && arr[2][0] == game.AI) {
        printf("You Lost\n");
        return true;
    } else if (arr[0][2] == game.Player && arr[1][1] == game.Player && arr[2][0] == game.Player) {
        printf("You Won\n");
        return true;
    }

    return false;
}

void display_board() {
    printf("-------------\n");
    for (int i = 0; i < 3; i++) {
        printf("| %c | %c | %c |\n", arr[i][0], arr[i][1], arr[i][2]);
        printf("-------------\n");
    }
}

void user_input(int i, int j) {
    if (!checkIfEmpty(i, j)) exit(1);
    else arr[i][j] = game.Player;
}

bool checkForDraw() {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (arr[i][j] == ' ') count++;
        }
    }

    if (count != 0) {
        return false;
    } else {
        return true;
    }
}

void AI() {
    int i = rand() % 3;
    int j = rand() % 3;
    if (!checkIfEmpty(i, j)) AI();
    else arr[i][j] = game.AI;
}

void PlayerMove() { 
    printf("\nEnter the coordinates : ");
    int i,j;
    scanf("%d %d", &i, &j);
    user_input(i, j);
    display_board();
}

void AIMove() {
    AI();
    display_board();
}

void gameEndCheck() {
    if(checkForWin()) {
        exit(0);
    }
    if (checkForDraw()) {
        exit(0);
    }
}

