#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

struct STONE_TYPE {
    int five_in_a_row = 0; //xxxxx
    int live_four = 0; //xxxx
    int dead_four = 0; //xxx_x, oxxxx, xx_xx
    int live_three = 0; //xxx, xx_x
};

int player;
int top_row, top_col, bottom_row, bottom_col;
const int SIZE = 15;
std::array<std::array<int, SIZE>, SIZE> board;
int evaluate_func(STONE_TYPE &stone_type);
STONE_TYPE evaluate_board();

void read_board(std::ifstream& fin) {
    top_row = top_col = 14;
    bottom_row = bottom_col = 0;
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
            if (board[i][j] != 0) {
                if (i < top_row) top_row = i;
                if (j < top_col) top_col = j;
                if (i > bottom_row) bottom_row = i;
                if (j > bottom_col) bottom_col = j;
            }
        }
    }
}

void write_valid_spot(std::ofstream& fout) {
    srand(time(NULL));
    int x, y;
    // Keep updating the output until getting killed.
    while(true) {
        // Choose a random spot.
        int x = (rand() % SIZE);
        int y = (rand() % SIZE);
        if (board[x][y] == EMPTY) {
            fout << x << " " << y << std::endl;
            // Remember to flush the output to ensure the last action is written to file.
            fout.flush();
        }
    }
}

int evaluate_func(STONE_TYPE &stone_type) {
    int value = 0;
    value += stone_type.five_in_a_row * 100000;
    value += stone_type.live_four * 15000;
    value += stone_type.live_three * 10000;
    value += stone_type.dead_four * 1000;
    return value;
}

STONE_TYPE evaluate_board() {
    //count the stone type of the board 
    STONE_TYPE black_stone;
    for (int i=0; i<SIZE; i++) {

    }
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
