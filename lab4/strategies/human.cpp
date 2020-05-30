#include "human.h"

#include <iostream>

void human_strategy_t::on_win() {
    std::cout << "You win!" << std::endl;
}

void human_strategy_t::on_lose() {
    std::cout << "You lose!" << std::endl;
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
    std::cout << "Type coordinates of a checker: " << std::endl;
    int x_from, y_from;
    std::cin >> x_from >> y_from;
    std::cout << "Type coordinates of the move: " << std::endl;
    int x_to, y_to;
    std::cin >> x_to >> y_to;
    return {x_from, y_from, x_to, y_to};
}

void human_strategy_t::on_incorrect_step(const step_t &step) const {
    std::cout << "Incorrect step:" << std::endl;
    std::cout << "From x: " << step.x_from << "; y: " << step.y_from << std::endl;
    std::cout << "To x: " << step.x_to << "; y: " << step.y_to << std::endl;
}
