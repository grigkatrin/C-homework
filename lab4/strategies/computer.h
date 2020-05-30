#pragma once

#include <string>

#include "../game/structures.h"
#include "computer_interface.h"

class computer_strategy_t_1 : public computer_interface_t {
public:
    explicit computer_strategy_t_1(std::string name);

    step_t make_step(const field_t &field) override;

    void print_stat() const override;

private:
    std::string name;
};

class computer_strategy_t_2 : public computer_interface_t {
public:
    explicit computer_strategy_t_2(std::string name);

    step_t make_step(const field_t &field) override;

    void print_stat() const override;

private:
    std::string name;
};
