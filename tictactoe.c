#include <stdio.h> 
#include <stdlib.h>

const char Player1 = 'X';
const char Player2 = 'O';
char board[3][3];
int turns;

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    for (int i = 0; i < 3; i++) {
        printf("  %c  |  %c  |  %c  \n", board[i][0], board[i][1], board[i][2]);
        if (i < 2) {
            printf(" ___ | ___ | ___\n");
        }
    }
    printf("\n");
}

void playerMove() {
    int x, y;

    while (1) {
        printf("Select row (1-3): ");
        if (scanf("%d", &x) != 1 || x < 1 || x > 3) {
            puts("Invalid input! Please select a row between 1 and 3.");
            while (getchar() != '\n');
            continue;
        }

        printf("Select column (1-3): ");
        if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
            puts("Invalid input! Please select a column between 1 and 3.");
            while (getchar() != '\n');
            continue;
        }

        if (board[x - 1][y - 1] != ' ') {
            puts("That spot is already taken! Please select another spot.");
            continue;
        }

        board[x - 1][y - 1] = (turns %2 == 0) ? Player1 : Player2;
        break;
    }
}

int checkEmptySpaces() {
    int empty_spaces = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == ' ') {
                empty_spaces += 1;  
            }
        }
    }
    return empty_spaces; 
}

char checkWinner() {
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') {
        return board[1][1];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') { 
        return board[1][1];
    }
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
            return board[i][0]; 
        }
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
            return board[0][i]; 
        }
    }
    return ' ';
}

void declareWinner(char Winner) {
    switch (Winner) {
        case 'X':
            puts("Player 1 wins");
            break;
        case 'O':
            puts("Player 2 wins");
            break;
        case ' ':
            puts("It's a draw! Everybody loses!");
            break;
        default:
            puts("how");
            break;
    }
}

int main() {
    char winner = ' ';
    resetBoard(); 
    printBoard(); 

    while (winner == ' ' && checkEmptySpaces() > 0) {
        playerMove(); 
        turns++;
        printBoard(); 
        winner = checkWinner();
        if (winner != ' ' || checkEmptySpaces() == 0) {
            break;
        }
    }
    declareWinner(winner);
    return 0;
}
