#include "level.h"

int Level::getLevel()
{
    return level_num;
}

bool Level::isHeavy()
{
    return is_heavy;
}

void Level::readBlocks(std::string source)
{
    std::ifstream in(source);
    char c;
    while (in >> c)
        blocks.push_back(toBlockType(c));
}

BlockType Level::getNextBlock()
{
    BlockType ret = blocks[index];
    index = (size_t) index == blocks.size() - 1 ? 0 : index + 1;
    return ret;
}

void Level::setSource(std::string source)
{
    blocks.clear();
    readBlocks(source);
}

void Level::resetLevel()
{
    blocks.clear();
    readBlocks(origin_source);
}