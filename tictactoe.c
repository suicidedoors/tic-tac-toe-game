#include <stdio.h> 
#include <stdlib.h>
#include <time.h>

const char Player = 'X';
const char Computer = 'O';
char board[3][3];

void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard() {
    printf("  %c  |  %c  |  %c  \n", board[0][0], board[0][1], board[0][2]);
    printf(" ___ | ___ | ___\n");
    printf("  %c  |  %c  |  %c  \n", board[1][0], board[1][1], board[1][2]);
    printf(" ___ | ___ | ___\n");
    printf("  %c  |  %c  |  %c  \n", board[2][0], board[2][1], board[2][2]);
    printf("\n");
}

void playerMove() {
    int x, y;
    while (1) {
        printf("Select row (1-3): ");
        scanf(" %d", &x);
        printf("Select column (1-3): ");
        scanf(" %d", &y);
        if (x < 1 || x > 3 || y < 1 || y > 3) {
            printf("Invalid input! Please select row and column between 1 and 3.\n");
            continue;
        }
        if (board[x - 1][y - 1] != ' ') {
            printf("That spot is invalid! Please select another spot.\n");
            continue;
        }
        board[x - 1][y - 1] = Player;
        break;
    }
}

void computerMove() {
    int x, y;
    do {
        x = rand() % 3;
        y = rand() % 3;
    } while (board[x][y] != ' ');
    board[x][y] = Computer;
    printf("The computer has placed %c in (%d;%d)\n", Computer, (x + 1), (y + 1));
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
            printf("The player wins\n");
            break;
        case 'O':
            printf("The computer wins\n");
            break;
        case ' ':
            printf("It's a draw! Everybody loses!\n");
            break;
        default:
            printf("how\n");
            break;
    }
}

int main() {
    char winner = ' ';
    srand(time(NULL));
    resetBoard(); 
    printBoard(); 

    while (winner == ' ' && checkEmptySpaces() > 0) {
        playerMove(); 
        printBoard(); 
        winner = checkWinner();
        if (winner != ' ' || checkEmptySpaces() == 0) {
            break;
        }

        computerMove(); 
        printBoard(); 
        winner = checkWinner();
        if (winner != ' ' || checkEmptySpaces() == 0) {
            break;
        }
    }
    declareWinner(winner);
    return 0;
}
