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

struct field_t {
    field_t() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if ((i < 3) && ((i + j) % 2 == 1)) {
                    fld[i][j] = 'w';
                } else if ((i >= 5) && ((i + j) % 2 == 1)) {
                    fld[i][j] = 'b';
                } else if ((i + j) % 2 == 1) {
                    fld[i][j] = '*';
                } else {
                    fld[i][j] = '.';
                }
            }
        }
    }

    char fld[8][8];
};
