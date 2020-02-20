#ifndef LEVEL_H
#define LEVEL_H
#include <vector>
#include <string>
#include <fstream>
#include "../board/blocktype.h"

class Level
{
protected:
    int level_num;
    bool is_heavy;

    int index;
    std::vector<BlockType> blocks;
    std::string origin_source;

    void readBlocks(std::string);

public:
    virtual ~Level() = default;
    virtual int getLevel();
    virtual bool isHeavy();
    virtual BlockType getNextBlock();
    virtual void setSource(std::string source);
    virtual void resetLevel();
};

#endif
