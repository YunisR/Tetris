#ifndef LEVEL4_H
#define LEVEL4_H
#include "level.h"
#include <string>

class Level4 : public Level
{
    bool is_use_sequence;

public:
    Level4();
    BlockType getNextBlock() override;
    void resetLevel() override;
    void setSource(std::string source) override;
};

#endif
