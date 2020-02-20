#ifndef INFO_H
#define INFO_H
#include "game/board/colour.h"
#include "game/board/blocktype.h"

struct Info {
    int id;

    // Cell info
    int row, col;
    Colour colour;
    
    // Board info
    bool blind;
    BlockType next_block;

    // Player info
    int hi_score, score, level;
    bool is_turn;

    Info() {}
    Info(int id, int row, int col, Colour colour): // Cell constructor
        id(id), row(row), col(col), colour(colour) {}
    Info(int id, bool blind, BlockType next_block): // Board constructor
        id(id), blind(blind), next_block(next_block) {}
    Info(int id, int hi_score, int score, int level, bool is_turn): // Player constructor
        id(id), hi_score(hi_score), score(score), level(level), is_turn(is_turn) {}
};

#endif
