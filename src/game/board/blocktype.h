#ifndef BLOCKTYPE_H
#define BLOCKTYPE_H
#include "../action.h"

class InvalidBlockTypeException {};

enum class BlockType {NoType, S, O, Z, I, L, J, T, Dot};

BlockType toBlockType(char source);
BlockType toBlockType(Action source);

#endif
