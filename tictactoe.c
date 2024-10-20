#include <stdio.h> 
#include <stdlib.h>

#define SIZE 3


const char Player1 = 'X';
const char Player2 = 'O';

const int Winning_Combinations[8][3][2] = {
    {{0, 0}, {0, 1}, {0, 2}},
    {{1, 0}, {1, 1}, {1, 2}},
    {{2, 0}, {2, 1}, {2, 2}},

    {{0, 0}, {1, 0}, {2, 0}},
    {{0, 1}, {1, 1}, {2, 1}},
    {{0, 2}, {1, 2}, {2, 2}},

    {{0, 0}, {1, 1}, {2, 2}},
    {{0, 2}, {1, 1}, {2, 0}}
    };
    
int turns;


typedef struct {
    char squares[SIZE][SIZE];
    char winner;
} small_board;

typedef struct {
    small_board boards[SIZE][SIZE];
    char game_winner;
} big_board;

typedef struct {
    int col;
    int row;
} last_move;

last_move lm;
big_board bb;

void resetBoard() {
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            for (int k = 0; k < SIZE; k++){
                for (int l = 0; l < SIZE; l++)
                {
                    bb.boards[i][j].squares[k][l] = ' ';
                    turns++;
                }
            }
        }
    }
    bb.game_winner = ' ';
}


void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int k = 0; k < SIZE; k++) {
            printf(" %c %c %c | %c %c %c | %c %c %c \n", 
                bb.boards[i][0].squares[k][0],
                bb.boards[i][0].squares[k][1],
                bb.boards[i][0].squares[k][2],

                bb.boards[i][1].squares[k][0],
                bb.boards[i][1].squares[k][1],
                bb.boards[i][1].squares[k][2],

                bb.boards[i][2].squares[k][0],
                bb.boards[i][2].squares[k][1],
                bb.boards[i][2].squares[k][2]);
        }
        if (i < 2) {
            printf("_______|_______|_______\n");
        }
        if (i == 1 || i == 0) {
            printf("       |       |       \n");
        }
    }
}

void playerMove(char board[SIZE][SIZE]) {
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
        x--;
        y--;
        if (board[x][y] != ' ') {
            puts("That spot is already taken! Please select another spot.");
            continue;
        }

        board[x][y] = (turns %2 == 0) ? Player1 : Player2;
        lm.col = y;
        lm.row = x;

        break;
    }
}



char (*pickBoard())[SIZE]{
    if (lm.row == ' ' || bb.boards[lm.row][lm.col].winner != ' '){
        int board_row, board_col;
        puts("You can choose any board for your next move.");
        printf("Pick next board Row (1-3): ");
        scanf("%d", &board_row);
        printf("Pick next board Column: ");
        scanf("%d", &board_col);
        lm.row = board_row - 1;
        lm.col = board_col - 1;
    }
    return bb.boards[lm.row][lm.col].squares;
}


void checkWinner(){
    
}


int main() {
    char game_board[SIZE][SIZE];        //board where the next move will take place

    resetBoard();
    while (bb.game_winner == ' ') {
        printBoard();
        char (*game_board)[SIZE] = pickBoard();
        playerMove(game_board);
        checkWinner();
        turns++;
    }

    printf("Winner: %d", bb.game_winner);
    return 0;
}




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

