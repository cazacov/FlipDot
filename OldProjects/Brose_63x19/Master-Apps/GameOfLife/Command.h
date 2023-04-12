#ifndef DAY_09_1_COMMAND_H
#define DAY_09_1_COMMAND_H

#define OPCODE_ADD 1
#define OPCODE_MUL 2
#define OPCODE_IN 3
#define OPCODE_OUT 4
#define OPCODE_JUMP_IF_TRUE 5
#define OPCODE_JUMP_IF_FALSE 6
#define OPCODE_LESS_THAN 7
#define OPCODE_EQUALS 8
#define OPCODE_SETBASE 9
#define OPCODE_HALT 99

enum ResultDestination { RAM, OUT, IP, BASE, NONE };
enum Mode {
    Position = 0,
    Immediate = 1,
    Relative = 2};

struct Command {
    int opcode;
    long parameter_values[2] = {0};
    Mode mode[3] = {Mode::Position};
    int result_addr = {0};
    ResultDestination destination;
    int param_count;
};


#endif //DAY_09_1_COMMAND_H
