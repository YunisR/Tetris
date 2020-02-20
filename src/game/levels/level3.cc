#include "level3.h"

Level3::Level3() : is_use_sequence{false}
{
    level_num = 3;
    is_heavy = true;
}

BlockType Level3::getNextBlock()
{
    if (is_use_sequence)
    {
        return Level::getNextBlock();
    }
    else
    {
        int n = rand() % 9;
        if (n == 0 || n == 2)
            return BlockType::S;
        else if (n == 1 || n == 3)
            return BlockType::Z;
        else if (n == 4)
            return BlockType::I;
        else if (n == 5)
            return BlockType::J;
        else if (n == 6)
            return BlockType::L;
        else if (n == 7)
            return BlockType::O;
        else
            return BlockType::T;
    }
}

void Level3::resetLevel()
{
    is_use_sequence = true;
}

void Level3::setSource(std::string source)
{
    is_use_sequence = true;
    Level::setSource(source);
}

