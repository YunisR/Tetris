#include "controller.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <ncurses.h>
#include <string>

Controller::Controller(std::istream &in) : in(in) {}

SpecialMove Controller::readSpecialMove(bool use_keyboard, BlockType &forced_block) {
    std::cout << "Choose a move: (1) blind, (2) heavy, (3) force" << std::endl;
    if (use_keyboard) {
        int ch;
        initscr();
        noecho();
        cbreak();
        nodelay(stdscr, true);
        while (1) {
            ch = getch();
            switch (ch) {
                case '1':
                    endwin();
                    return SpecialMove::Blind;
                case '2':
                    endwin();
                    return SpecialMove::Heavy;
                case '3':
                    endwin();
                    std::cout << "Choose a block to force: " << std::endl;
                    std::cout << "    (1) I" << std::endl;
                    std::cout << "    (2) J" << std::endl;
                    std::cout << "    (3) L" << std::endl;
                    std::cout << "    (4) S" << std::endl;
                    std::cout << "    (5) Z" << std::endl;
                    std::cout << "    (6) T" << std::endl;
                    std::cout << "    (7) O" << std::endl;
                    initscr();
                    noecho();
                    cbreak();
                    nodelay(stdscr, true);
                    while (forced_block == BlockType::NoType) {
                        ch = getch();
                        switch (ch) {
                            case '1':
                                forced_block = BlockType::I;
                                break;
                            case '2':
                                forced_block = BlockType::J;
                                break;
                            case '3':
                                forced_block = BlockType::L;
                                break;
                            case '4':
                                forced_block = BlockType::S;
                                break;
                            case '5':
                                forced_block = BlockType::Z;
                                break;
                            case '6':
                                forced_block = BlockType::T;
                                break;
                            case '7':
                                forced_block = BlockType::O;
                                break;
                        }
                    }
                    endwin();
                    return SpecialMove::Force;
                default: continue;
            }
        }
    }
    int n;
    while (1) {
        in >> n;
        switch (n) {
            case 1: return SpecialMove::Blind;
            case 2: return SpecialMove::Heavy;
            case 3:
                std::cout << "Choose a block to force: I, J, L, S, Z, T, O" << std::endl;
                while (forced_block == BlockType::NoType) {
                    char c;
                    in >> c;
                    switch (c) {
                            case 'I':
                                forced_block = BlockType::I;
                                break;
                            case 'J':
                                forced_block = BlockType::J;
                                break;
                            case 'L':
                                forced_block = BlockType::L;
                                break;
                            case 'S':
                                forced_block = BlockType::S;
                                break;
                            case 'Z':
                                forced_block = BlockType::Z;
                                break;
                            case 'T':
                                forced_block = BlockType::T;
                                break;
                            case 'O':
                                forced_block = BlockType::O;
                                break;
                        }
                }
                return SpecialMove::Force;
            default: continue;
        }
    }
}

Action Controller::readInput(std::string &source, int &num_times, bool use_keyboard) {
    if (use_keyboard) { // TODO make game accept text input while also accepting keyboard input
        int ch;
        initscr();
        noecho();
        cbreak();
        keypad(stdscr, true);
        nodelay(stdscr, true);
        while (1)
        {
            ch = getch();
            switch (ch)
            {
            case KEY_UP:
                endwin();
                return Action::clockwise;
            case KEY_DOWN:
                endwin();
                return Action::down;
            case KEY_RIGHT:
                endwin();
                return Action::right;
            case KEY_LEFT:
                endwin();
                return Action::left;
            case ' ':
                endwin();
                return Action::drop;
            case 'x':
                endwin();
                return Action::endKeyboard;
            default:
                continue;
            }
        }
    }
    
    std::string line;
    getline(in, line);

    if(in.eof())
    {
        return Action::end;
    }
    
    std::stringstream ss(line);

    int n;
    ss >> n;
    if(!ss.fail())
        num_times = n;
    else
        ss = std::stringstream(line);

    std::string action;
    ss >> action;

    std::vector<Action> matches;
    for (size_t i = 0; i < commands.size(); ++i)
    {
        if (commands[i].first.length() >= action.length() && commands[i].first.substr(0, action.length()) == action)
        {
            matches.push_back(commands[i].second);
        }
    }
    if (matches.size() == 1)
    {
        if (matches[0] == Action::sequence || matches[0] == Action::noRandom)
        {
            ss >> source;
        }
        return matches[0];
    }
    return Action::invalid;
}