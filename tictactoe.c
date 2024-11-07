#include <stdio.h>
#include <stdlib.h>

#define SIZE 3
#define RED "\033[31m"
#define YELLOW "\033[38;5;227m"
#define ORANGE "\033[38;5;208m"
#define RESET "\033[0m"

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
int ultimate;

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

void resetBoard(void); 
void printBoard(void); 
void printTurn(void); 
void playerMove(char board[SIZE][SIZE]); 
char (*pickBoard(void))[SIZE]; 
void checkSmallBoardWinner(small_board *sb); 
void checkWinner(void); 

int main() {
    printf("%sSelect gamemode \n  1 - Normal Tic Tac Toe\n  2 - Ultimate Tic Tac Toe %s \n", YELLOW, RESET);
    scanf("%d", &ultimate);
    ultimate--;
    if (ultimate == 1){
        printf("%sNow playing Ultimate Tic Tac Toe%s\n", ORANGE, RESET);
    } else if (ultimate == 0){
        printf("%sNow playing Normal Tic Tac Toe%s\n", ORANGE, RESET);
    } else {
        puts("Game over");
        return 0;
    }

    resetBoard();
    while (bb.game_winner == ' ') {
        printBoard();
        char (*game_board)[SIZE];
        if (ultimate){
            game_board = pickBoard();
        } else {
            game_board = (char (*)[SIZE]) bb.boards;
        }
        printTurn();
        playerMove(game_board);
        checkWinner();
    }

    printf("Player %c wins the game!\n", bb.game_winner);
    return 0;
}

void resetBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                for (int l = 0; l < SIZE; l++) {
                    bb.boards[i][j].squares[k][l] = ' ';
                }
            }
            bb.boards[i][j].winner = ' ';
        }
    }
    turns = 0;
    bb.game_winner = ' ';
    lm.row = -1;
}

void printBoard() {
    for (int i = 0; i < SIZE; i++) {
        for (int k = 0; k < SIZE; k++) {
            printf("\t %c %c %c | %c %c %c | %c %c %c \n", 
                ultimate ? bb.boards[i][0].squares[k][0] : bb.boards[i][0].winner,
                ultimate ? bb.boards[i][0].squares[k][1] : bb.boards[i][0].winner,
                ultimate ? bb.boards[i][0].squares[k][2] : bb.boards[i][0].winner,

                ultimate ? bb.boards[i][1].squares[k][0] : bb.boards[i][1].winner,
                ultimate ? bb.boards[i][1].squares[k][1] : bb.boards[i][1].winner,
                ultimate ? bb.boards[i][1].squares[k][2] : bb.boards[i][1].winner,

                ultimate ? bb.boards[i][2].squares[k][0] : bb.boards[i][2].winner,
                ultimate ? bb.boards[i][2].squares[k][1] : bb.boards[i][2].winner,
                ultimate ? bb.boards[i][2].squares[k][2] : bb.boards[i][2].winner);
        }
        if (i < 2) {
            printf("\t_______|_______|_______\n");
        }
        if (i < 2) {
            printf("\t       |       |       \n");
        }
    }
}

void printTurn(){
    char current_turn = (turns % 2 == 0) ? Player1 : Player2;
    printf("%sPlayer %c's turn%s\n", ORANGE, current_turn, RESET);
    if (ultimate){
    printf("%sNow playing on board (%d,%d)%s\n", 
    ORANGE,
    (lm.row + 1),
    (lm.col + 1), 
    RESET);
    }
}

void playerMove(char board[SIZE][SIZE]) {
    int x, y; 

    while (1) {
        printf("Select row (1-3): ");
        if (scanf("%d", &x) != 1 || x < 1 || x > 3) {
            printBoard();
            printTurn(); 
            printf("%sInvalid input! Please select a row between 1 and 3.%s\n", RED, RESET);
            while (getchar() != '\n');
            continue;
        }

        printf("Select column (1-3): ");
        if (scanf("%d", &y) != 1 || y < 1 || y > 3) {
            printBoard();
            printTurn(); 
            printf("%sInvalid input! Please select a column between 1 and 3.%s\n", RED, RESET);
            while (getchar() != '\n');
            continue;
        }
        x--;
        y--;
        if (board[x][y] != ' ') {
            printBoard();
            printTurn(); 
            printf("%sThat spot is already taken! Please select another spot.%s\n", RED, RESET);
            continue;
        }

        if (ultimate){
            board[x][y] = (turns % 2 == 0) ? Player1 : Player2; 
            lm.col = y;
            lm.row = x;
        } else {
            bb.boards[x][y].winner = (turns % 2 == 0) ? Player1 : Player2; 
        }

        turns++;
        break;
    }
}

char (*pickBoard())[SIZE] {
    if (lm.row < 0 || lm.row >= SIZE || bb.boards[lm.row][lm.col].winner != ' ') {
        int board_row, board_col;
    
        printf("%sYou can choose any board for your next move.%s\n", YELLOW,RESET);
        do {
            printf("%sPick Next Board Row (1-3): %s", YELLOW, RESET);
            if (scanf("%d", &board_row) != 1 || board_row < 1 || board_row > 3) {
                printf("%sInvalid input!%s\n", RED, RESET);
                while (getchar() != '\n');
                continue;
            }
            printf("%sPick Next Board Column (1-3): %s", YELLOW, RESET);
            if (scanf("%d", &board_col) != 1 || board_col < 1 || board_col > 3) {
                printf("%sInvalid input!%s\n", RED, RESET);
                while (getchar() != '\n');
                continue;
            }
        } while (board_col < 1 || board_col > 3 || board_row < 1 || board_row > 3 || bb.boards[board_row - 1][board_col - 1].winner != ' '); 

        lm.row = board_row - 1;
        lm.col = board_col - 1;
    }
    return bb.boards[lm.row][lm.col].squares;
}

void checkSmallBoardWinner(small_board *sb) {
    for (int i = 0; i < 8; i++) {
        if (sb->squares[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]] == 
            sb->squares[Winning_Combinations[i][1][0]][Winning_Combinations[i][1][1]] && 
            sb->squares[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]] == 
            sb->squares[Winning_Combinations[i][2][0]][Winning_Combinations[i][2][1]] && 
            sb->squares[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]] != ' ') {
            
            sb->winner = sb->squares[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]];
            return;
        }
    }
}

void checkWinner() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            checkSmallBoardWinner(&bb.boards[i][j]);
        }
    }

    for (int i = 0; i < 8; i++) {
        if (bb.boards[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]].winner == 
            bb.boards[Winning_Combinations[i][1][0]][Winning_Combinations[i][1][1]].winner &&
            bb.boards[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]].winner == 
            bb.boards[Winning_Combinations[i][2][0]][Winning_Combinations[i][2][1]].winner &&
            bb.boards[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]].winner != ' ') {
            
            bb.game_winner = bb.boards[Winning_Combinations[i][0][0]][Winning_Combinations[i][0][1]].winner;
            return;
        }
    }
}