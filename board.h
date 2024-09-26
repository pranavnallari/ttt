#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <unistd.h>
#include <ncurses.h>
#include <sys/ioctl.h>

#define X 'X'
#define O 'O'

int x = 17;
int y = 8;

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

void display_board(WINDOW *win) {
    mvwprintw(win, 7, 15, "-------------\n");
    mvwprintw(win, 8, 15, "| %c | %c | %c |\n", arr[0][0], arr[0][1], arr[0][2]);
    mvwprintw(win, 9, 15, "-------------\n");
    mvwprintw(win, 10, 15, "| %c | %c | %c |\n", arr[1][0], arr[1][1], arr[1][2]);
    mvwprintw(win, 11, 15, "-------------\n");
    mvwprintw(win, 12, 15, "| %c | %c | %c |\n", arr[2][0], arr[2][1], arr[2][2]);
    mvwprintw(win, 13, 15, "-------------\n");
}

bool checkIfEmpty(int i, int j) {
    return arr[i][j] == ' ';
}

void exit_message(const char* message) {
    clear();
    system("clear");
    mvprintw(10, 7, "%s", message);
    refresh();
}

bool checkForWin() {
    // Check rows and columns
    for (int i = 0; i < 3; i++) {
        // Check rows
        if (arr[i][0] == game.AI && arr[i][1] == game.AI && arr[i][2] == game.AI) {
            exit_message("You Lost");
            return true;
        } else if (arr[i][0] == game.Player && arr[i][1] == game.Player && arr[i][2] == game.Player) {
            exit_message("You Won");
            return true;
        }

        // Check columns
        if (arr[0][i] == game.AI && arr[1][i] == game.AI && arr[2][i] == game.AI) {
            exit_message("You Lost\n");
            return true;
        } else if (arr[0][i] == game.Player && arr[1][i] == game.Player && arr[2][i] == game.Player) {
            exit_message("You Won\n");
            return true;
        }
    }

    // Check diagonals
    if (arr[0][0] == game.AI && arr[1][1] == game.AI && arr[2][2] == game.AI){
        exit_message("You Lost\n");
        return true;
    } else if (arr[0][0] == game.Player && arr[1][1] == game.Player && arr[2][2] == game.Player) {
        exit_message("You Won\n");
        return true;
    }
    if (arr[0][2] == game.AI && arr[1][1] == game.AI && arr[2][0] == game.AI) {
        exit_message("You Lost\n");
        return true;
    } else if (arr[0][2] == game.Player && arr[1][1] == game.Player && arr[2][0] == game.Player) {
        exit_message("You Won\n");
        return true;
    }

    return false;
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

void AI_Rand() {
    int i = rand() % 3;
    int j = rand() % 3;
    if (!checkIfEmpty(i, j)) AI_Rand();
    else arr[i][j] = game.AI;
}

void AI();

void AIMove(WINDOW* win) {
    AI();
    display_board(win);
    refresh();
    wrefresh(win);
}

void gameEndCheck() {
    if(checkForWin()) {
        getch();
        endwin();
        exit(0);
    }
    if (checkForDraw()) {
        exit_message("DRAW\n");
        getch();
        endwin();
        exit(0);
    }
}

void print_tab(int count) {
    for (int i = 1; i <= count; i++) printw("\t");
}

void welcome_screen(int col) {
    int count = 6 * (col / 167);
    print_tab(count);
    printw(" _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _ \n");
    print_tab(count);
    printw("|_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_|\n");
    print_tab(count);
    printw("|_|                                             |_|\n");
    print_tab(count);
    printw("|_| _____ _        _____           _____        |_|\n");
    print_tab(count);
    printw("|_||_   _|_|___   |_   ____ ___   |_   ____ ___ |_|\n");
    print_tab(count);
    printw("|_|  | | | |  _|    | || .'|  _|    | || . | -_||_|\n");
    print_tab(count);
    printw("|_|  |_| |_|___|    |_||__,|___|    |_||___|___||_|\n");
    print_tab(count);
    printw("|_| _  _  _  _  _  _  _  _  _  _  _  _  _  _  _ |_|\n");
    print_tab(count);
    printw("|_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_|\n");
    printw("\n\n");
    for (int i = 1; i <= col; i++) {
        printw("-");
    }
    printw("\nInstructions : wasd or arrow keys to move\nPress q to quit any time\n");
}

WINDOW* AllInit() {
    system("clear");
    initscr();
    noecho();
    board_init();

    struct winsize size;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == -1) {
        perror("ioctl");
        exit(1);
    }
    int starty = (LINES - 20) / 2;
    int startx = (COLS - 50) / 2;
    if (startx < 0) startx = 0;
    welcome_screen(size.ws_col);

    WINDOW *win = newwin(20, 50, starty + 5, startx);
    keypad(win, true);
    refresh();

    box(win, ' ', ' ');
    display_board(win);
    wmove(win, y, x);
    wrefresh(win);

    return win;
}

// change here
void start_select_symbol() {
    system("clear");
    initscr();
    noecho();
    cbreak();
    int ymax, xmax;
    getmaxyx(stdscr, ymax, xmax);

    WINDOW *menuwin = newwin(6, xmax - 12, ymax - 8, 5);
    box(menuwin, 0, 0);
    refresh();
    wrefresh(menuwin);
    keypad(menuwin, true);

    int highlight = 0;
    char *choices[] = {"Select Your Symbol", "Select X (goes first)", "Select O"};
    int choice = 0;
    while (1) {
        for (int i = 0; i < 3; i++) {
            if (i == highlight) {
                wattron(menuwin, A_REVERSE);
            }
            mvwprintw(menuwin, i + 1, 1, "%s", choices[i]);
            wattroff(menuwin, A_REVERSE);
        }
        choice = wgetch(menuwin);

        switch (choice) {
            case KEY_UP:
                highlight--;
                if (highlight < 0) highlight = 0;
                break;
            case KEY_DOWN:
                highlight++;
                if (highlight > 2) highlight = 2;
                break;
            default:
                break;
        }
        if (choice == 10 && (highlight == 1 || highlight == 2)) break;
    }
    if (highlight == 1) {
            game.Player = X;
            game.AI = O;
        } else {
            game.Player = O;
            game.AI = X;
        }
    clear();
    endwin();
    system("clear");
}
