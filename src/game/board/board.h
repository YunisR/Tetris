#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include "cell.h"
#include "block.h"
#include "../../displays/subject.h"
#include "../../info.h"
#include "../specialMove.h"

const size_t WIDTH = 11;
const size_t HEIGHT = 18;

class Board : public Subject
{   
    int player_id;
    int level;
    std::vector<std::vector<Cell>> cells;
    std::vector<std::vector<bool>> occupied;
    std::vector<Block> blocks;
    Block active_block;
    BlockType next_block;
    Colour cur_colour;

    int level_heavy;
    int special_heavy;
    int blocks_placed_since_clear;
    bool blind;
    bool sent_move;

    void updateBoard(std::vector<std::pair<int, int>> placed_cells, bool on, Colour c);
    int clearRow(int n); // returns the number of points when a row is cleared

public:
    Board(BlockType active_block_type, BlockType next_block_type, int level_num, int player_id);
    void resetBoard();
    void clear();
    void rotateCW(int n);
    void rotateCCW(int n);
    void moveLeft(int n);
    void moveRight(int n);
    void moveDown(int n); // returns if the down move failed
    void drop();
    void applyHeavy(int n);
    void setNextBlock(BlockType block);
    bool hasPlacedBlock();
    void replaceActiveBlock(BlockType block);
    void placeActiveBlock();
    void updateActiveBlock();
    int clearRows(int current_level);  // returns the number of points when a row is cleared
    bool isRowFilled(int row);
    bool sentMove() const;
    void makeBlind();
    void setLevel(int level);
    void makeHeavy();
    void checkLevelEffects();
    void attach(Observer *o) override;
    Info getInfo() const override;
};

#endif
