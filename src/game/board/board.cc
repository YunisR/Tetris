#include "board.h"
#include <cmath>

Board::Board(BlockType active_block_type, BlockType next_block_type, int level_num, int player_id)
    : player_id(player_id), level{level_num}, active_block{active_block_type, level}, next_block{next_block_type},
      level_heavy{level_num >= 3 ? 1 : 0}, special_heavy{0}, blocks_placed_since_clear{0}, blind{false}
{
    // initialize board
    for (size_t i = 0; i < HEIGHT; ++i)
    {
        std::vector<Cell> row;
        std::vector<bool> o_row;
        for (size_t j = 0; j < WIDTH; ++j)
        {
            Cell cell = Cell(i, j, Colour::NoColour, player_id);
            row.push_back(cell);
            o_row.push_back(false);
        }
        cells.push_back(row);
        occupied.push_back(o_row);
    }
    active_block.setOccupied(occupied);
    cur_colour = toColour(active_block.getBlockType());
}

void Board::updateBoard(std::vector<std::pair<int, int>> placed_cells, bool on, Colour c)
{
    for (auto p : placed_cells)
    {
        cells[p.first][p.second].setColour(on ? c : Colour::NoColour);
        occupied[p.first][p.second] = on;
    }
}

void Board::resetBoard()
{
    blocks.clear();
    clear();
}

void Board::clear()
{
    for (size_t i = 0; i < HEIGHT; ++i)
    {
        for (size_t j = 0; j < WIDTH; ++j)
        {
            cells[i][j].setColour(Colour::NoColour);
            occupied[i][j] = false;
        }
    }
}

void Board::rotateCW(int n)
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block.rotateCW(n);
    applyHeavy(level_heavy);
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::rotateCCW(int n)
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block.rotateCCW(n);
    applyHeavy(level_heavy);
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::moveLeft(int n)
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block.moveLeft(n);
    applyHeavy(level_heavy + special_heavy);
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::moveRight(int n)
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block.moveRight(n);
    applyHeavy(level_heavy + special_heavy);
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::moveDown(int n)
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block.moveDown(n);
    applyHeavy(level_heavy);
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::drop()
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block.drop();
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::applyHeavy(int n)
{
    active_block.moveDown(n);
}

void Board::setNextBlock(BlockType block)
{
    next_block = block;
    notifyObservers();
}

bool Board::hasPlacedBlock()
{
    return active_block.isPlaced();
}

void Board::replaceActiveBlock(BlockType block)
{
    updateBoard(active_block.getCells(), false, cur_colour);
    active_block = Block{block, level};
    cur_colour = toColour(active_block.getBlockType());
    active_block.setOccupied(occupied);
    updateBoard(active_block.getCells(), true, cur_colour);
}

void Board::placeActiveBlock()
{
    blind = false;
    sent_move = false;
    blocks.push_back(active_block);
    ++blocks_placed_since_clear;
}

void Board::updateActiveBlock()
{
        active_block = Block{next_block, level};
        active_block.setOccupied(occupied);
        cur_colour = toColour(active_block.getBlockType());
        updateBoard(active_block.getCells(), true, cur_colour);
}

int Board::clearRows(int current_level)
{
    int score = 0;
    int lines_cleared = 0;
    //clears lines one by one
    for (size_t row = 0; row < HEIGHT; ++row)
    {
        if (isRowFilled(row))
        {
            lines_cleared++;
            score += clearRow(row);
            --row;
            blocks_placed_since_clear = 0;
        }
    }
    if (lines_cleared > 0)
        score += pow((current_level + lines_cleared), 2);
    if (lines_cleared >= 2)
    {
        sent_move = true;
    }
    return score;
}

int Board::clearRow(int n)
{
    int score = 0;

    // check placed blocks
    for (auto &block : blocks)
    {
        for (auto cell : block.getCells())
        {
            if (cell.first == n)
            {
                score += block.deleteCell(cell); // will increase score if cell is last cell in block
            }
        }
    }

    // remove empty blocks
    for (size_t i = 0; i < blocks.size(); ++i)
    {
        if (blocks[i].getCells().empty())
        {
            blocks.erase(blocks.begin() + i);
            --i;
        }
    }

    clear();

    //moves all block's cells above row n down by 1
    for (auto &block : blocks)
    {
        block.moveDownLineClear(n);
        updateBoard(block.getCells(), true, toColour(block.getBlockType()));
    }
    return score;
}

bool Board::isRowFilled(int row)
{
    for (size_t i = 0; i < WIDTH; ++i)
    {
        if (!occupied[row][i])
        {
            return false;
        }
    }
    return true;
}

bool Board::sentMove() const
{
    return sent_move;
}

void Board::makeBlind()
{
    blind = true;
    notifyObservers();
}

void Board::setLevel(int level)
{
    this->level = level;
    if (level >= 3)
        level_heavy = 1;
    else
        level_heavy = 0;
}

void Board::makeHeavy()
{
    special_heavy = 2;
}

void Board::checkLevelEffects()
{
    if(level == 4 && (blocks_placed_since_clear % 5) == 0 && blocks_placed_since_clear != 0)
    {
        Block dot = Block{BlockType::Dot, level};
        dot.setOccupied(occupied);
        dot.drop();
        updateBoard(dot.getCells(), true, Colour::Brown);
        blocks.push_back(dot);
    }
}

void Board::attach(Observer *o)
{
    observers.emplace_back(o);
    for (size_t r = 0; r < HEIGHT; ++r)
    {
        for (size_t c = 0; c < WIDTH; ++c)
        {
            for (auto &ob : observers)
            {
                cells[r][c].attach(ob);
                cells[r][c].notifyObservers();
            }
        }
    }
    updateBoard(active_block.getCells(), true, cur_colour);
}

Info Board::getInfo() const
{
    return Info(player_id, blind, next_block);
}
