#include <stdio.h>
#include <stdlib.h>

char board[9];

void resetBoard(void) {
    for (int i = 0; i < 9; i++) board[i] = '1' + i;
}

void printBoard(void) {
    printf("\n");
    for (int r = 0; r < 3; r++) {
        printf(" %c | %c | %c \n", board[r * 3], board[r * 3 + 1], board[r * 3 + 2]);
        if (r < 2) printf("---+---+---\n");
    }
    printf("\n");
}

// Returns 1 if the given player has three in a row
int hasWon(char p) {
    int lines[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8},   // rows
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8},   // columns
        {0, 4, 8}, {2, 4, 6}               // diagonals
    };
    for (int i = 0; i < 8; i++) {
        if (board[lines[i][0]] == p &&
            board[lines[i][1]] == p &&
            board[lines[i][2]] == p)
            return 1;
    }
    return 0;
}

int isFull(void) {
    for (int i = 0; i < 9; i++)
        if (board[i] != 'X' && board[i] != 'O') return 0;
    return 1;
}

int main(void) {
    char again = 'y';

    while (again == 'y' || again == 'Y') {
        resetBoard();
        char player = 'X';
        int gameOver = 0;

        while (!gameOver) {
            printBoard();
            int move;
            printf("Player %c, choose a square (1-9): ", player);

            if (scanf("%d", &move) != 1) {
                while (getchar() != '\n');   // clear bad input
                printf("Please enter a number.\n");
                continue;
            }
            if (move < 1 || move > 9 || board[move - 1] == 'X' || board[move - 1] == 'O') {
                printf("Invalid move, try again.\n");
                continue;
            }

            board[move - 1] = player;

            if (hasWon(player)) {
                printBoard();
                printf("Player %c wins!\n", player);
                gameOver = 1;
            } else if (isFull()) {
                printBoard();
                printf("It's a draw!\n");
                gameOver = 1;
            } else {
                player = (player == 'X') ? 'O' : 'X';
            }
        }

        printf("Play again? (y/n): ");
        scanf(" %c", &again);
    }

    printf("Thanks for playing!\n");
    return 0;
}
