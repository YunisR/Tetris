#include "level0.h"

Level0::Level0(std::string source) : is_use_sequence{false}
{
    origin_source = source;
    level_num = 0;
    index = 0;
    is_heavy = false;

    readBlocks(source);
}

BlockType Level0::getNextBlock()
{
    BlockType ret = blocks[index];
    index = (size_t) index == blocks.size() - 1 ? 0 : index + 1;

    if (index == 0 && is_use_sequence)
    {
        is_use_sequence = false;
        Level::resetLevel();
    }
    return ret;
}

void Level0::setSource(std::string source)
{
    is_use_sequence = true;
    Level::setSource(source);
}