#include "board.h"

void player_move(WINDOW* win) {
    int ch;
    while ((ch = getch()) != 'q') {
        if (ch == 'd' || ch == KEY_RIGHT) {
            x = x + 4;
            if (x > 25) x = 25;
            wmove(win, y, x);
            wrefresh(win);
        } else if (ch == 'a' || ch == KEY_LEFT) {
            x = x - 4;
            if (x < 17) x = 17;
            wmove(win, y, x);
            wrefresh(win);
        } else if (ch == 'w' || ch == KEY_UP) {
            y = y - 2;
            if (y < 8) y = 8;
            wmove(win, y, x);
            wrefresh(win);
        } else if (ch == 's' || ch == KEY_DOWN) {
            y = y + 2;
            if (y > 12) y = 12;
            wmove(win, y, x);
            wrefresh(win);
        } else if (ch == '\n' || ch == '\r') {
            int col = (x - 17) / 4;
            int row = (y - 8) / 2;
            arr[row][col] = game.Player;
            gameEndCheck();
            AIMove(win);
            gameEndCheck();
            display_board(win);
            wmove(win, y, x);
            wrefresh(win);  
        }
    }
}

int main(void) {
    srand(time(NULL));
    start_select_symbol();
    WINDOW *win = AllInit();

    if (game.AI == X) {
        AIMove(win);
    }

    player_move(win);

    endwin();
    return EXIT_SUCCESS;
}