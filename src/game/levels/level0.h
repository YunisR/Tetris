#ifndef LEVEL0_H
#define LEVEL0_H

#include "level.h"

class Level0 : public Level
{
    int index;
    bool is_use_sequence;

public:
    Level0(std::string source);
    BlockType getNextBlock() override;
    void setSource(std::string source) override;
};

#endif
