#include <stdio.h> 
#include <stdlib.h>

#define SIZE 3
const char Player1 = 'X';
const char Player2 = 'O';
int turns;

typedef struct {
    char squares[SIZE][SIZE];
    char winner;
} small_board;

typedef struct {
    small_board boards[SIZE][SIZE];
    char game_winner;
} big_board;

big_board bb;

void resetBoard() {
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++){
                for (int l = 0; l < SIZE; l++)
                {
                    //                    bb.boards[i][j].squares[k][l] = ' ');
                    bb.boards[i][j].squares[k][l] = (turns % 2 ? 'X' : 'O');
                    turns++;
                }
            }
        }
    }
    bb.game_winner = ' ';
}

//MIGHT fix this later

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int k = 0; k < SIZE; k++) {
                printf(" %c %c %c | %c %c %c | %c %c %c \n", 
                    bb.boards[i][0].squares[0][k],
                    bb.boards[i][0].squares[1][k],
                    bb.boards[i][0].squares[2][k],

                    bb.boards[i][1].squares[0][k],
                    bb.boards[i][1].squares[1][k],
                    bb.boards[i][1].squares[2][k],

                    bb.boards[i][2].squares[0][k],
                    bb.boards[i][2].squares[1][k],
                    bb.boards[i][2].squares[2][k]);
        }

        if (i < 2) {
            printf("_______|_______|_______\n");
        }
        if (i == 1 || i == 0){
            printf("       |       |       \n");
        }
    }
}


int main() {
    resetBoard();
    printBoard();
    return 0;
}


// void playerMove( board ) {
//     int x, y; 

//     while (1) {
//         printf("Select row (1-3): ");
//         if (scanf("%d", &x) != 1 || x < 1 || x > 3) {
//             puts("Invalid input! Please select a row between 1 and 3.");
//             while (getchar() != '\n');
//             continue;
//         }

//         printf("Select column (1-3): ");
//         if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
//             puts("Invalid input! Please select a column between 1 and 3.");
//             while (getchar() != '\n');
//             continue;
//         }

//         if (board[x - 1][y - 1] != ' ') {
//             puts("That spot is already taken! Please select another spot.");
//             continue;
//         }

//         board[x - 1][y - 1] = (turns %2 == 0) ? Player1 : Player2;
//         break;
//     }
// }

// int checkEmptySpaces() {
//     int empty_spaces = 0;
//     for (int i = 0; i < 3; i++) {
//         for (int j = 0; j < 3; j++) {
//             if (board[i][j] == ' ') {
//                 empty_spaces += 1;  
//             }
//         }
//     }
//     return empty_spaces; 
// }

// char checkWinner() {
//     if (board[0][0] == board[1][1] && board[0][0] == board[2][2] && board[0][0] != ' ') {
//         return board[1][1];
//     }
//     if (board[0][2] == board[1][1] && board[0][2] == board[2][0] && board[0][2] != ' ') { 
//         return board[1][1];
//     }
//     for (int i = 0; i < 3; i++) {
//         if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ') {
//             return board[i][0]; 
//         }
//         if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ') {
//             return board[0][i]; 
//         }
//     }
//     return ' ';
// }

// void declareWinner(char Winner) {
//     switch (Winner) {
//         case 'X':
//             puts("Player 1 wins");
//             break;
//         case 'O':
//             puts("Player 2 wins");
//             break;
//         case ' ':
//             puts("It's a draw! Everybody loses!");
//             break;
//         default:
//             puts("how");
//             break;
//     }
// }

// int main() {
//     char winner = ' ';
//     resetBoard(); 
//     printBoard(); 

//     while (winner == ' ' && checkEmptySpaces() > 0) {
//         playerMove(); 
//         turns++;
//         printBoard(); 
//         winner = checkWinner();
//         if (winner != ' ' || checkEmptySpaces() == 0) {
//             break;
//         }
//     }
//     declareWinner
// void resetBoard() {
//     for (int i = 0; i < SIZE; i++){
//         for (int j = 0; i < SIZE; j++){
//             for (int k = 0; k < SIZE; k++){
//                 for (int l = 0; l < SIZE; l++)
//                 {
//                     big_board.>boards[i][j].cells[k][l] = ' ';
//                 }
//             }
//         }
//     }
//     big_board->game_winner = ' ';
// }

