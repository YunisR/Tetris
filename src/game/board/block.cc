#include "block.h"
#include <cmath>

Block::Block(BlockType type, int level)
    : row{14}, col{1}, is_placed{false}, type{type}, level_on_create{level}
{
    switch (type)
    {
    case (BlockType::I):
        cell_offsets.push_back(std::make_pair(0, -1));
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(0, 1));
        cell_offsets.push_back(std::make_pair(0, 2));
        break;
    case (BlockType::J):
        cell_offsets.push_back(std::make_pair(1, -1));
        cell_offsets.push_back(std::make_pair(0, -1));
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(0, 1));
        break;
    case (BlockType::L):
        cell_offsets.push_back(std::make_pair(0, -1));
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(0, 1));
        cell_offsets.push_back(std::make_pair(1, 1));
        break;
    case (BlockType::O):
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(1, 0));
        cell_offsets.push_back(std::make_pair(0, -1));
        cell_offsets.push_back(std::make_pair(1, -1));
        break;
    case (BlockType::S):
        cell_offsets.push_back(std::make_pair(0, -1));
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(1, 0));
        cell_offsets.push_back(std::make_pair(1, 1));
        break;
    case (BlockType::T):
        cell_offsets.push_back(std::make_pair(0, -1));
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(1, 0));
        cell_offsets.push_back(std::make_pair(0, 1));
        break;
    case (BlockType::Z):
        cell_offsets.push_back(std::make_pair(1, -1));
        cell_offsets.push_back(std::make_pair(1, 0));
        cell_offsets.push_back(std::make_pair(0, 0));
        cell_offsets.push_back(std::make_pair(0, 1));
        break;
    case (BlockType::Dot):
        col = 5;
        cell_offsets.push_back(std::make_pair(0, 0));
        break;
    case (BlockType::NoType):
        throw "Tried to create board with no type";
    }
}

void Block::setOccupied(const std::vector<std::vector<bool>> &occ)
{
    occupied.clear();
    occupied = occ;

    for (auto cell : getCells())
    {
        if (!isValid(cell.first, cell.second))
            throw InvalidBlockCreationException();
    }
}

std::vector<std::pair<int, int>> Block::getCells()
{
    std::vector<std::pair<int, int>> absolute_cells;
    for (std::size_t i = 0; i < cell_offsets.size(); ++i)
    {
        std::pair<int, int> cell = std::make_pair(row + cell_offsets[i].first, col + cell_offsets[i].second);
        absolute_cells.push_back(cell);
    }
    return absolute_cells;
}

BlockType Block::getBlockType()
{
    return type;
}

bool Block::isPlaced()
{
    return is_placed;
}

bool Block::isValid(int r, int c)
{
    return r >= 0 && r < BOARD_HEIGHT && c >= 0 && c < BOARD_WIDTH && !occupied[r][c];
}

void Block::rotateCW(int n)
{
    if (type == BlockType::O || type == BlockType::NoType)
    {
        return;
    }
    std::vector<std::pair<int, int>> new_offsets;
    for (auto cell : cell_offsets)
    {
        std::pair<int, int> nc = std::make_pair(-cell.second, cell.first);
        if (!isValid(nc.first + row, nc.second + col))
        {
            return;
        }
        new_offsets.push_back(nc);
    }
    cell_offsets.clear();
    cell_offsets = new_offsets;
}

void Block::rotateCCW(int n)
{
    if (type == BlockType::O || type == BlockType::NoType)
    {
        return;
    }
    std::vector<std::pair<int, int>> new_offsets;
    for (auto cell : cell_offsets)
    {
        std::pair<int, int> nc = std::make_pair(cell.second, -cell.first);
        if (!isValid(nc.first + row, nc.second + col))
        {
            return;
        }
        new_offsets.push_back(nc);
    }
    cell_offsets.clear();
    cell_offsets = new_offsets;
}

void Block::moveLeft(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (auto cell : getCells())
        {
            if (!isValid(cell.first, cell.second - 1))
                return;
        }
        --col;
    }
}

void Block::moveRight(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (auto cell : getCells())
        {
            if (!isValid(cell.first, cell.second + 1))
                return;
        }
        ++col;
    }
}

void Block::moveDown(int n)
{
    for (int i = 0; i < n; ++i)
    {
        for (auto cell : getCells())
        {
            if (!isValid(cell.first - 1, cell.second))
            {
                is_placed = true;
                return;
            }
        }
        --row;
    }
}

void Block::moveDownLineClear(int lines_cleared)
{
    for (auto &cell : cell_offsets)
    {
        if (row + cell.first < lines_cleared)
            continue;
        cell.first--;
    }
}

void Block::drop()
{
    while (!is_placed)
    {
        moveDown(1);
    }
}

int Block::deleteCell(std::pair<int, int> cell)
{
    std::pair<int, int> offset_cell = std::make_pair(cell.first - row, cell.second - col);
    for (std::size_t i = 0; i < cell_offsets.size(); ++i)
    {
        if (offset_cell == cell_offsets[i])
        {
            cell_offsets.erase(cell_offsets.begin() + i);
            return (cell_offsets.empty()) ? pow((level_on_create + 1), 2) : 0;
        }
    }
    return 0;
}
