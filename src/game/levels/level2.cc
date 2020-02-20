#include "level2.h"

Level2::Level2()
{
    level_num = 2;
    is_heavy = false;
}

BlockType Level2::getNextBlock()
{
    int n = rand() % 7;
    if (n == 0)
        return BlockType::S;
    else if (n == 1)
        return BlockType::Z;
    else if (n == 2)
        return BlockType::I;
    else if (n == 3)
        return BlockType::J;
    else if (n == 4)
        return BlockType::L;
    else if (n == 5)
        return BlockType::O;
    else
        return BlockType::T;
}