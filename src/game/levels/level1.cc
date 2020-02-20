#include "level1.h"

Level1::Level1()
{
    level_num = 1;
    is_heavy = false;
}

BlockType Level1::getNextBlock()
{
    int n = rand() % 12;
    if (n == 0)
        return BlockType::S;
    else if (n == 1)
        return BlockType::Z;
    else if (n == 2 || n == 3)
        return BlockType::I;
    else if (n == 4 || n == 5)
        return BlockType::J;
    else if (n == 6 || n == 7)
        return BlockType::L;
    else if (n == 8 || n == 9)
        return BlockType::O;
    else
        return BlockType::T;
}
