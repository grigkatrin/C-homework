#include "computer.h"

#include <cassert>
#include <iostream>
#include <vector>


computer_strategy_t_1::computer_strategy_t_1(std::string name) :
        name(std::move(name)) {}

step_t computer_strategy_t_1::make_step(const field_t &fld) {
    std::vector<std::pair<size_t, size_t>> possible_checkers;
    std::set<std::pair<size_t, size_t>> attack_chekers;

    if (player_num == 0) {
        bool changed = false;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (player_num == 0) {
                    if (fld.fld[i][j] == 'w') {
                        changed = attacked_checkers(fld, attack_chekers, std::pair<size_t, size_t>(j, i));
//                        possible_checkers.push_back(attack_chekers);
                    }
                } else {
                    if (fld.fld[i][j] == 'b') {
                        changed = attacked_checkers(fld, attack_chekers, std::pair<size_t, size_t>(j, i));
//                        possible_checkers.push_back(attack_chekers);
                    }
                }
            }
        }
    }



//  for (int i = 0; i < 3; ++i) {
//    for (int j = 0; j < 3; ++j) {
//      if (fld.fld[i][j] == '.') {
//        empty_coordinates.emplace_back(i, j);
//      }
//    }
//  }
//  assert(!empty_coordinates.empty());
//  std::random_shuffle(empty_coordinates.begin(), empty_coordinates.end());
//  auto elem = empty_coordinates.back();
//  return {elem.first + 1, elem.second + 1};
}

void computer_strategy_t_1::print_stat() const {
    std::cout << "Random model [" << name << "]: " << std::endl;
    computer_interface_t::print_stat();
}
