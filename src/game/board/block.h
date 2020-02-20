#ifndef BLOCK_H
#define BLOCK_H
#include <utility>
#include "blocktype.h"
#include <vector>

class InvalidBlockCreationException
{
};

const int BOARD_HEIGHT = 18;
const int BOARD_WIDTH = 11;

class Block
{
    int row, col;
    std::vector<std::pair<int, int>> cell_offsets;
    std::vector<std::vector<bool>> occupied;
    bool is_placed;
    BlockType type;
    int level_on_create;

    bool isValid(int r, int c);

public:
    Block(BlockType type, int level);
    void setOccupied(const std::vector<std::vector<bool>> &occ);
    std::vector<std::pair<int, int>> getCells();
    BlockType getBlockType();
    bool isPlaced();

    void rotateCW(int n);
    void rotateCCW(int n);
    void moveLeft(int n);
    void moveRight(int n);
    void moveDown(int n);
    void moveDownLineClear(int lines_cleared);
    void drop();
    int deleteCell(std::pair<int, int> cell); // returns points gained for deleting cell
};

#endif
