#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <iostream>
#include <string>
#include <vector>
#include "specialMove.h"
#include "board/blocktype.h"
#include "action.h"

const std::vector<std::pair<std::string, Action>> commands
{
    {"left", Action::left},
    {"right", Action::right},
    {"down", Action::down},
    {"clockwise", Action::clockwise},
    {"counterclockwise", Action::counterClockwise},
    {"drop", Action::drop},
    {"levelup", Action::levelUp},
    {"leveldown", Action::levelDown},
    {"norandom", Action::noRandom},
    {"random", Action::random},
    {"sequence", Action::sequence},
    {"restart", Action::restart},
    {"I", Action::I},
    {"J", Action::J},
    {"L", Action::L},
    {"O", Action::O},
    {"S", Action::S},
    {"Z", Action::Z},
    {"T", Action::T},
    {"end", Action::end},
    {"usekeyboard", Action::useKeyboard}
};

class Controller
{
    std::istream &in;

    public:
        Controller(std::istream &in = std::cin);
        Action readInput(std::string &source, int &num_times, bool use_keyboard);
        SpecialMove readSpecialMove(bool use_keyboard, BlockType &forced_block);
};

#endif
