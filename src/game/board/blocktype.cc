#include "blocktype.h"

BlockType toBlockType(char source)
{
    BlockType ret;
    switch(source)
    {
        case 'S': ret = BlockType::S;
            break;
        case 'O': ret = BlockType::O;
            break;
        case 'Z': ret = BlockType::Z;
            break;
        case 'I': ret = BlockType::I;
            break;
        case 'L': ret = BlockType::L;
            break;
        case 'J': ret = BlockType::J;
            break;
        case 'T': ret = BlockType::T;
            break;
        default: ret = BlockType::NoType;
    }
    return ret;
}

BlockType toBlockType(Action source)
{
    BlockType ret;
    switch(source)
    {
        case Action::S: ret = BlockType::S;
            break;
        case Action::O: ret = BlockType::O;
            break;
        case Action::Z: ret = BlockType::Z;
            break;
        case Action::I: ret = BlockType::I;
            break;
        case Action::L: ret = BlockType::L;
            break;
        case Action::J: ret = BlockType::J;
            break;
        case Action::T: ret = BlockType::T;
            break;
        default:
            throw InvalidBlockTypeException();
            break;
    }
    return ret;
}
