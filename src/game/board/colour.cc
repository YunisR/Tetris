#include "colour.h"

Colour toColour(BlockType type)
{
    Colour ret;
    switch(type)
    {
        case BlockType::S: ret = Colour::Green;
            break;
        case BlockType::O: ret = Colour::Yellow;
            break;
        case BlockType::Z: ret = Colour::Red;
            break;
        case BlockType::I: ret = Colour::LightBlue;
            break;
        case BlockType::L: ret = Colour::Orange;
            break;
        case BlockType::J: ret = Colour::DarkBlue;
            break;
        case BlockType::T: ret = Colour::Purple;
            break;
        case BlockType::Dot: ret = Colour::Brown;
            break;
        default: ret = Colour::NoColour;
    }
    return ret;
}
