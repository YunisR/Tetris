#ifndef LEVEL3_H
#define LEVEL3_H
#include "level.h"
#include <string>

class Level3 : public Level
{
    bool is_use_sequence;

public:
    Level3();
    BlockType getNextBlock() override;
    void resetLevel() override;
    void setSource(std::string source) override;
};

#endif
