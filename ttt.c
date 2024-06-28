#include "board.h"

int main(void) {
    srand(time(NULL));

    select_symbol();
    printf("Player : %c \nThe OPP : %c \nX goes first\n", game.Player, game.AI);
    board_init();

    if (game.AI == X) {
        while(1) {
            AIMove();
            PlayerMove();
            gameEndCheck();
        }
    } else {
        while (1) {
            display_board();
            PlayerMove();
            AIMove();
            gameEndCheck();
        }
    }

   
    return EXIT_SUCCESS;
}