#include "betterAI.h"
void player_move(WINDOW* win) {
    keypad(win, true);
    int ch;
    while ((ch = wgetch(win)) != 'q') {
        // Movement handling
        #ifdef DEBUG
        mvwprintw(win, 16, 15, "DEBUG: Key pressed: %d", ch);
        wrefresh(win);
        #endif
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
            // Calculate row and col based on cursor position
            int col = (x - 17) / 4;
            int row = (y - 8) / 2;

            // Debug: Print the row and col to verify correct position
            #ifdef DEBUG
            mvwprintw(win, 14, 15, "DEBUG: Player move at row: %d, col: %d", row, col);
            wrefresh(win);
            #endif

            // Check if the spot is empty
            if (!checkIfEmpty(row, col)) {
                #ifdef DEBUG
                mvwprintw(win, 15, 15, "DEBUG: Position occupied!");
                wrefresh(win);
                #endif
                continue;
            }

            arr[row][col] = game.Player;
            #ifdef DEBUG
            mvwprintw(win, 15, 15, "DEBUG: Player move placed at [%d, %d]", row, col);
            wrefresh(win);
            #endif
            
            display_board(win); 
            wrefresh(win);

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
    keypad(win, true);
    if (game.AI == X) {
        AIMove(win);
        // Move the cursor to the first empty position after AI's move
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (arr[i][j] == ' ') {
                    x = 17 + (j * 4);
                    y = 8 + (i * 2);
                    wmove(win, y, x);
                    wrefresh(win);
                }
            }
        }
    }

    player_move(win);

    endwin();
    return EXIT_SUCCESS;
}
