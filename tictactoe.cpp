#include <iostream>

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

class SmallBoard {
public:
    char squares[SIZE][SIZE];
    char winner;

    SmallBoard() {
        reset();
    }

    void reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                squares[i][j] = ' ';
            }
        }
        winner = ' ';
    }

    char checkWinner() {
        for (int i = 0; i < 8; i++) {
            int x1 = Winning_Combinations[i][0][0], y1 = Winning_Combinations[i][0][1];
            int x2 = Winning_Combinations[i][1][0], y2 = Winning_Combinations[i][1][1];
            int x3 = Winning_Combinations[i][2][0], y3 = Winning_Combinations[i][2][1];

            if (squares[x1][y1] == squares[x2][y2] && squares[x1][y1] == squares[x3][y3] && squares[x1][y1] != ' ') {
                winner = squares[x1][y1];
                return winner;
            }
        }
        return winner;
    }
};

class BigBoard {
public:
    SmallBoard boards[SIZE][SIZE];
    char game_winner;

    BigBoard() {
        reset();
    }

    void reset() {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                boards[i][j].reset();
            }
        }
        game_winner = ' ';
    }

    char checkGameWinner() {
        for (int i = 0; i < 8; i++) {
            int x1 = Winning_Combinations[i][0][0], y1 = Winning_Combinations[i][0][1];
            int x2 = Winning_Combinations[i][1][0], y2 = Winning_Combinations[i][1][1];
            int x3 = Winning_Combinations[i][2][0], y3 = Winning_Combinations[i][2][1];

            if (boards[x1][y1].winner == boards[x2][y2].winner && boards[x1][y1].winner == boards[x3][y3].winner && boards[x1][y1].winner != ' ') {
                game_winner = boards[x1][y1].winner;
                return game_winner;
            }
        }
        return game_winner;
    }
    

    void print() {
        for (int i = 0; i < SIZE; i++) {
            for (int k = 0; k < SIZE; k++) {
                std::cout << "\t " << boards[i][0].squares[k][0] << " " << boards[i][0].squares[k][1] << " " << boards[i][0].squares[k][2]
                    << " | " << boards[i][1].squares[k][0] << " " << boards[i][1].squares[k][1] << " " << boards[i][1].squares[k][2]
                    << " | " << boards[i][2].squares[k][0] << " " << boards[i][2].squares[k][1] << " " << boards[i][2].squares[k][2] << std::endl;
            }
            if (i < 2) std::cout << "\t_______|_______|_______\n";
        }
    }
};


int main() {
    int game_mode;
    std::cout << YELLOW << "Select gamemode \n  1 - Normal Tic Tac Toe\n  2 - Ultimate Tic Tac Toe" << RESET << std::endl;
    std::cin >> game_mode;

    SmallBoard sb;
    BigBoard bb;

    bb.print();

    return 0;
}
