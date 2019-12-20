//
// Created by Victor on 02.12.2019.
//

#ifndef DAY_02_01_INTCODECOMPUTER_H
#define DAY_02_01_INTCODECOMPUTER_H

#define RAM_SIZE 50000

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
    std::vector<long> output_buf;
    Command load_next_command();
    int ip;
    int base;
    bool i_am_halted;
public:
    IntcodeComputer() {reset();};
    std::vector<long> ram;
    bool step(bool trace, std::function<long(void)> input_required);
    long get_last_output() {
        if (output_buf.empty()) {
            return 0;
        }
        else {
            return *output_buf.rbegin();
        }
    }
    void reset();
    void load_day_13();
    bool is_halted() { return i_am_halted;}
};


#endif //DAY_02_01_INTCODECOMPUTER_H
