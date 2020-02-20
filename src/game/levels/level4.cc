#include "level4.h"

Level4::Level4() : is_use_sequence{false}
{
    level_num = 4;
    is_heavy = true;
}

BlockType Level4::getNextBlock()
{
    if (is_use_sequence)
    {
        return Level::getNextBlock();
    }
    else
    {
        int n = rand() % 9;
        if (n == 0 || n == 1)
            return BlockType::S;
        else if (n == 2 || n == 6)
            return BlockType::Z;
        else if (n == 4)
            return BlockType::I;
        else if (n == 5)
            return BlockType::J;
        else if (n == 3)
            return BlockType::L;
        else if (n == 7)
            return BlockType::O;
        else
            return BlockType::T;
    }
}

void Level4::resetLevel()
{
    is_use_sequence = true;
}

void Level4::setSource(std::string source)
{
    is_use_sequence = true;
    Level::setSource(source);
}
