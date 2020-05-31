#pragma once

#include <algorithm>

struct step_t {
    step_t(int x_from, int y_from, int x_to, int y_to) :
            x_from{x_from},
            y_from{y_from},
            x_to{x_to},
            y_to{y_to}{}

    int x_from, y_from, x_to, y_to;
};

struct apply_step_t {
    apply_step_t(bool is_correct, size_t player_num):
            is_correct{is_correct},
            player_num{player_num}{}

    bool is_correct;
    size_t player_num;
};

struct field_t {
    field_t() {
//        for (int i = 0; i < 8; i++) {
//            for (int j = 0; j < 8; j++) {
//                if ((i < 3) && ((i + j) % 2 == 1)) {
//                    fld[i][j] = 'w';
//                } else if ((i >= 5) && ((i + j) % 2 == 1)) {
//                    fld[i][j] = 'b';
//                } else if ((i + j) % 2 == 1) {
//                    fld[i][j] = '*';
//                } else {
//                    fld[i][j] = '.';
//                }
//            }
//        }

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if ((row + col) % 2 == 0) {
                    fld[row][col] = '.';
                    continue;
                } else {
                    fld[row][col] = '*';
                }
            }
        }
        fld[2][1]='w';
        fld[4][1]='b';
        fld[4][3]='b';
    }

    char fld[8][8];
};
