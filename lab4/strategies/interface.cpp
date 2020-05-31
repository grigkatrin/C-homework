#include "interface.h"

bool
strategy_interface_t::attacked_checkers(const field_t &field, std::set<std::pair<size_t, size_t> > &attack_checkers,
                                        std::pair<size_t, size_t> current_checker) {
    bool changed = false;

    if (field.fld[current_checker.second][current_checker.first] == 'w') {
        int change_step[2] = {-1, 1};
        for (auto &i: change_step) {
            for (auto &j: change_step) {
                if (field.fld[current_checker.second + i][current_checker.first + j] == 'b') {
                    if (field.fld[current_checker.second + i * 2][current_checker.first + j * 2] == '*') {
                        attack_checkers.insert(std::pair<size_t, size_t>(current_checker.first, current_checker.second));
                        changed = true;
                    }
                }
            }
        }
    }

    if (field.fld[current_checker.second][current_checker.first] == 'b') {
        int change_step[2] = {-1, 1};
        for (auto &i: change_step) {
            for (auto &j: change_step) {
                if (field.fld[current_checker.second + i][current_checker.first + j] == 'w') {
                    if (field.fld[current_checker.second + i * 2][current_checker.first + j * 2] == '*') {
                        attack_checkers.insert(std::pair<size_t, size_t>(current_checker.first, current_checker.second));
                        changed = true;
                    }
                }
            }
        }
    }

    std::cout << "Changed " << changed << std::endl;
    return changed;
}
