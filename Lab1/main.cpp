#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>

double function(double x) {
    return sqrt(x);
}

int main() {
//    freopen("g3.out", "w", stdout);
    std::ofstream out;
    out.open("/Users/grig.katrin/CLionProjects/C-homework/Lab1/Grafs/g2.out");

    int m, n;
    double x0, x1;
    //std::cin >> m >> n >> x0 >> x1;

    m = 100;
    n = 40;
    x0 = 1;
    x1 = 20;

    double min_f = function(x0);
    double max_f = function(x0);

    double step_m = (x1 - x0) / m;
    for (int i = 0; i < m; i++) {
        double current = function(x0 + step_m * i);

        min_f = fmin(min_f, current);
        max_f = fmax(max_f, current);
    }

    int nul_pos;
    double step_n;

    if (max_f * min_f < 0) {
        step_n = (max_f - min_f) / n;
        nul_pos = round(max_f / step_n);
    }
    if (max_f == 0) {
        nul_pos = 0;
        step_n = (max_f - min_f) / n;
    }
    if (min_f == 0) {
        nul_pos = n;
        step_n = (max_f - min_f) / n;
    }
    if (min_f > 0 && max_f > 0) {
        step_n = max_f / n;
        nul_pos = n;
    }
    if (min_f < 0 && max_f < 0) {
        step_n = abs(min_f / n);
        nul_pos = 0;
    }

    char grid[n + 1][m];

    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < m; j++) {
            double current_f = function(x0 + step_m * j);
            if (i == nul_pos) {
                grid[i][j] = '-';
            }
            if (i > nul_pos) {
                if (((current_f < max_f - step_n * i) && (max_f >= 0)) ||
                    ((current_f < 0 - step_n * i) && (max_f < 0))) {
                    grid[i][j] = '#';
                } else {
                    grid[i][j] = ' ';
                }
            }
            if (i < nul_pos) {
                if (((current_f < max_f - step_n * i) && (max_f >= 0)) ||
                    ((current_f < 0 - step_n * i) && (max_f < 0))) {
                    grid[i][j] = ' ';
                } else {
                    grid[i][j] = '#';
                }
            }
        }
    }

    if (out.is_open())
    {
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j < m; j++) {
                out << grid[i][j];
            }
            out << std::endl;
        }
    }

    return 0;
}
