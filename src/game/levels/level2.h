#ifndef LEVEL2_H
#define LEVEL2_H
#include "level.h"
#include <string>

class Level2 : public Level
{

public:
    Level2();
    BlockType getNextBlock() override;
};

#endif
