//
// Created by Victor on 02.12.2019.
//

#ifndef DAY_02_01_INTCODECOMPUTER_H
#define DAY_02_01_INTCODECOMPUTER_H

#define RAM_SIZE 2450

enum ExecutionResult {
    Halt,
    Output,
    Running
};

#include <vector>
#include <functional>
#include "Command.h"

class IntcodeComputer {
private:
    int32_t last_out;
    Command load_next_command();
    int ip;
    int base;
    bool i_am_halted;
public:
    IntcodeComputer() {reset();};
    std::vector<int32_t> ram;
    bool step(bool trace, std::function<int32_t(void)> input_required);
    int32_t get_last_output() {
      return last_out;
    }
    void reset();
    void load_day_13();
    bool is_halted() { return i_am_halted;}
};


#endif //DAY_02_01_INTCODECOMPUTER_H
