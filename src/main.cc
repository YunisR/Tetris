#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "game/game.h"

int main(int argc, char *argv[])
{
    bool text_only = false;
    bool use_keyboard = false;
    int seed = 1;
    std::string p1_source = "sourceFiles/sequence1.txt";
    std::string p2_source = "sourceFiles/sequence2.txt";
    int level = 0;

    for (int i = 1; i < argc; ++i)
    {
        std::string cmd = argv[i];
        if (cmd == "-text")
        {
            text_only = true;
        }
        else if (cmd == "-seed")
        {
            std::stringstream ss(argv[i + 1]);
            ss >> seed;
            ++i;
        }
        else if (cmd == "-scriptfile1")
        {
            p1_source = argv[i + 1];
            ++i;
        }
        else if (cmd == "-scriptfile2")
        {
            p2_source = argv[i + 1];
            ++i;
        }
        else if (cmd == "-startlevel")
        {
            std::stringstream ss(argv[i + 1]);
            ss >> level;
            ++i;
        }
        else if (cmd == "-usekeyboard")
        {
            use_keyboard = true;
        }
    }
    Game g{text_only, seed, p1_source, p2_source, level, use_keyboard};
    g.start();
    return 0;
}
