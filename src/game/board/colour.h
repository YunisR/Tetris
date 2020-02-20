#ifndef COLOUR_H
#define COLOUR_H
#include "blocktype.h"

enum class Colour {NoColour, Orange, DarkBlue, LightBlue, Green, Purple, Red, Yellow, Brown};

Colour toColour(BlockType type);
#endif
