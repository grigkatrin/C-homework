#include "human.h"


human_strategy_t::human_strategy_t(std::string name) :
        name(std::move(name)) {}

void human_strategy_t::on_win() {
    std::cout << name << " - You win!" << std::endl;
}

void human_strategy_t::on_lose() {
    std::cout << name << " - You lose!" << std::endl;
}

void human_strategy_t::on_tie() {
    std::cout << "Tie!" << std::endl;
}

step_t human_strategy_t::make_step(const field_t &fld) {
    std::cout << "Field:" << std::endl;
    int i = 1;
    std::cout << "  1 2 3 4 5 6 7 8" << std::endl;
    for (const auto &line : fld.fld) {
        std::cout << i << ' ';
        i++;
        for (char c : line) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    std::cout << "Turn of " << name << std::endl;
    std::cout << "Type coordinates of a checker: " << std::endl;
    int x_from, y_from;
    std::cin >> x_from >> y_from;
    std::cout << "Type coordinates of the move: " << std::endl;
    int x_to, y_to;
    std::cin >> x_to >> y_to;
    return {x_from, y_from, x_to, y_to};
}

step_t human_strategy_t::next_step(const field_t &fld, std::pair<size_t, size_t> current_checker) {
    std::cout << "Field:" << std::endl;
    int i = 1;
    std::cout << "  1 2 3 4 5 6 7 8" << std::endl;
    for (const auto &line : fld.fld) {
        std::cout << i << ' ';
        i++;
        for (char c : line) {
            std::cout << c << ' ';
        }
        std::cout << std::endl;
    }
    int x_from = current_checker.first;
    int y_from = current_checker.second;
    std::cout << "Type coordinates of the next move: " << std::endl;
    int x_to, y_to;
    std::cin >> x_to >> y_to;
    return {x_from, y_from, x_to, y_to};
}

bool human_strategy_t::possible_attack(const field_t &fld, size_t player_num,
                                       std::set<std::pair<size_t, size_t>> &attack_checker) {
    attack_checker.clear();
    bool changed = false;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            if (player_num == 0) {
                if (fld.fld[i][j] == 'w' || fld.fld[i][j] == 'W') {
                    changed = attacked_checkers(fld, attack_checker, std::pair<size_t, size_t>(j, i));
                }
            } else {
                if (fld.fld[i][j] == 'b' || fld.fld[i][j] == 'B') {
                    changed = attacked_checkers(fld, attack_checker, std::pair<size_t, size_t>(j, i));
                }
            }
        }
    }

    return changed;
}

void human_strategy_t::on_incorrect_step(const step_t &step) const {
    std::cout << "Incorrect step:" << std::endl;
    std::cout << "From x: " << step.x_from << "; y: " << step.y_from << std::endl;
    std::cout << "To x: " << step.x_to << "; y: " << step.y_to << std::endl;
}
