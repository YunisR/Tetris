#ifndef LEVEL1_H
#define LEVEL1_H
#include <string>
#include "level.h"

class Level1 : public Level
{

public:
    Level1();
    BlockType getNextBlock() override;
};

#endif
