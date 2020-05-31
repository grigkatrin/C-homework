#include <iostream>
#include <set>
#include "game.h"

game_t::game_t(const player_t &first, const player_t &second) :
        field() {
    players.push_back(first);
    players.push_back(second);
}

apply_step_t
game_t::apply_step(const step_t &step, size_t player_num, std::set<std::pair<size_t, size_t> > &attack_checkers) {
    char &from_cell = field.fld[step.y_from - 1][step.x_from - 1];
    char &to_cell = field.fld[step.y_to - 1][step.x_to - 1];
    bool is_attack = players[player_num]->possible_attack(field, player_num, attack_checkers);
    size_t next_player = (player_num + 1) % 2;

    if ((to_cell != '*') || (from_cell == '.') || (from_cell == '*')) {
        return {false, player_num};
    }

    if (player_num == 0) {
        if (from_cell == 'w' && (step.y_to - step.y_from) == 1 && abs(step.x_to - step.x_from) == 1 && !is_attack) {
            std::swap(to_cell, from_cell);
            return {true, next_player};
        }
        if (is_attack && attack_checkers.count(std::pair<size_t, size_t>(step.x_from - 1, step.y_from - 1))){
            bool next_attack;
            step_t next_step = step;

            do {
                bool is_correct_step = false;
                while (!is_correct_step) {
                    if (abs(next_step.y_from - next_step.y_to) == 2 && abs(next_step.x_from - next_step.x_to) == 2 &&
                        field.fld[next_step.y_to - 1][next_step.x_to - 1] == '*') {
                        std::cout << 't' << std::endl;
                        size_t min_y = std::min(next_step.y_to, next_step.y_from);
                        size_t min_x = std::min(next_step.x_to, next_step.x_from);
                        char &middle_cell = field.fld[min_y][min_x];
                        if (middle_cell == 'b') {
                            middle_cell = '*';
                            std::swap(field.fld[next_step.y_from - 1][next_step.x_from - 1],
                                      field.fld[next_step.y_to - 1][next_step.x_to - 1]);
                            --players[next_player]->checker_amount;
                            is_correct_step = true;
                        }
                    }
                    if (!is_correct_step) {
                        players[player_num]->on_incorrect_step(next_step);
                        next_step = players[player_num]->next_step(field,
                                                                   std::pair<size_t, size_t>(next_step.x_from,
                                                                                             next_step.y_from));
                    }
                }
                next_attack = players[player_num]->attacked_checkers(field, attack_checkers,
                                                                     std::pair<size_t, size_t>(next_step.x_to - 1,
                                                                                               next_step.y_to - 1));
                if (next_attack) {
                    next_step = players[player_num]->next_step(field,
                                                               std::pair<size_t, size_t>(next_step.x_to,
                                                                                         next_step.y_to));
                }
            } while (next_attack);
            return {true, next_player};
        }
    } else {
        if (from_cell == 'b' && (step.y_from - step.y_to) == 1 && abs(step.x_from - step.x_to) == 1 && !is_attack) {
            std::swap(to_cell, from_cell);
            return {true, next_player};
        }
        if (is_attack && attack_checkers.count(std::pair<size_t, size_t>(step.x_from - 1, step.y_from - 1))) {
            bool next_attack;
            step_t next_step = step;
            std::cout << next_step.x_to << ' ' << next_step.y_to << std::endl;

            do {
                bool is_correct_step = false;
                while (!is_correct_step) {
                    if (abs(next_step.y_from - next_step.y_to) == 2 && abs(next_step.x_from - next_step.x_to) == 2 &&
                        field.fld[next_step.y_to - 1][next_step.x_to - 1] == '*') {
                        size_t min_y = std::min(next_step.y_to, next_step.y_from);
                        size_t min_x = std::min(next_step.x_to, next_step.x_from);
                        char &middle_cell = field.fld[min_y][min_x];
                        if (middle_cell == 'w') {
                            middle_cell = '*';
                            std::swap(field.fld[next_step.y_from - 1][next_step.x_from - 1],
                                      field.fld[next_step.y_to - 1][next_step.x_to - 1]);
                            --players[next_player]->checker_amount;
                            is_correct_step = true;
                        }
                    }
                    if (!is_correct_step) {
                        players[player_num]->on_incorrect_step(next_step);
                        next_step = players[player_num]->next_step(field,
                                                                   std::pair<size_t, size_t>(next_step.x_from,
                                                                                             next_step.y_from));
                    }
                }
                next_attack = players[player_num]->attacked_checkers(field, attack_checkers,
                                                                     std::pair<size_t, size_t>(next_step.x_to - 1,
                                                                                               next_step.y_to - 1));
                if (next_attack) {
                    next_step = players[player_num]->next_step(field,
                                                               std::pair<size_t, size_t>(next_step.x_to,
                                                                                         next_step.y_to));
                }
            } while (next_attack);
            return {true, next_player};
            }
    }
    return {false, player_num};
}

game_t::game_outcome_t game_t::is_win() const {

    if (steps_amount > 1000) {
        return TIE;
    }

    if (players[0]->checker_amount == 0 || players[1]->checker_amount == 0) {
        return WIN;

    }
    return IN_PROGRESS;
}

void game_t::play() {
    std::set<std::pair<size_t, size_t>> attack_checkers;
    apply_step_t apply_result(false, 0);
    size_t counter = apply_result.player_num;
    while (is_win() == IN_PROGRESS) {
        ++steps_amount;
        counter = apply_result.player_num;
        bool is_correct = false;
        while (!is_correct) {
            step_t step = players[counter]->make_step(field);
            apply_result = apply_step(step, counter, attack_checkers);
            is_correct = apply_result.is_correct;
            if (!is_correct) {
                players[counter]->on_incorrect_step(step);
            }
        }
    }

    if (is_win() == TIE) {
        for (const auto &p : players) {
            p->on_tie();
        }
        return;
    }

    for (size_t i = 0; i < players.size(); ++i) {
        if (i == counter) {
            players[i]->on_win();
        } else {
            players[i]->on_lose();
        }
    }
}
