#include "graphicDisplay.h"
#include "../game/board/cell.h"
#include "../game/player.h"
#include "../game/board/board.h"

GraphicsDisplay::GraphicsDisplay() : window{width, height}, p1_cells{BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 2)},
    p2_cells{BOARD_HEIGHT, std::vector<int>(BOARD_WIDTH, 2)}
{
    window.drawString(p1_origin.first, 50, "Level: ");
    window.drawString(p1_origin.first, 70, "Hi Score: ");
    window.drawString(p1_origin.first, 90, "Score: ");
    window.drawString(p1_origin.first, p1_origin.second + 50, "Next Block: ");

    window.drawString(p2_origin.first, 50, "Level: ");
    window.drawString(p2_origin.first, 70, "Hi Score: ");
    window.drawString(p2_origin.first, 90, "Score: ");
    window.drawString(p2_origin.first, p2_origin.second + 50, "Next Block: ");
}

int typeToInt(BlockType type)
{
    switch (type)
    {
    case BlockType::L:
        return 3;
    case BlockType::J:
        return 4;
    case BlockType::I:
        return 5;
    case BlockType::S:
        return 6;
    case BlockType::T:
        return 7;
    case BlockType::Z:
        return 8;
    case BlockType::O:
        return 9;
    case BlockType::Dot:
        return 10;
    default:
        return 2;
    }
}

void GraphicsDisplay::drawNextBlock(BlockType type, std::pair<int, int> origin)
{
    // whiteout old next block
    window.fillRectangle(origin.first, origin.second + cell_size + 30, cell_size * 4, cell_size * 2, 0);
    switch (type)
    {
    case BlockType::I:
        window.fillRectangle(origin.first, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 3 * cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    case BlockType::J:
        window.fillRectangle(origin.first, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    case BlockType::L:
        window.fillRectangle(origin.first, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    case BlockType::S:
        window.fillRectangle(origin.first, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    case BlockType::Z:
        window.fillRectangle(origin.first, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    case BlockType::O:
        window.fillRectangle(origin.first, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    case BlockType::T:
        window.fillRectangle(origin.first + cell_size, origin.second + cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        window.fillRectangle(origin.first + 2 * cell_size, origin.second + 2 * cell_size + 30, cell_size, cell_size, typeToInt(type));
        break;
    default:
        break;
    }
}

void GraphicsDisplay::blind(std::pair<int, int> origin) {
    for (int x = origin.first + 3 * cell_size; x <= origin.first + 9 * cell_size; x += cell_size)
    {
        for (int y = origin.second - 3 * cell_size; y >= origin.second - 12 * cell_size; y -= cell_size)
        {
            window.fillRectangle(x, y, cell_size, cell_size, 1);
        }
    }
}

void GraphicsDisplay::unblind(int player_id, std::pair<int, int> origin) {
    for (int r = 3; r <= 12; ++r)
    {
        for (int c = 3; c <= 9; ++c)
        {
            if (player_id == 1)
            {
                window.fillRectangle(origin.first + c * cell_size, origin.second - r * cell_size, cell_size, cell_size, p1_cells[r][c]);
            } else if (player_id == 2)
            {
                window.fillRectangle(origin.first + c * cell_size, origin.second - r * cell_size, cell_size, cell_size, p2_cells[r][c]);
            }
        }
    }
}

int colourToInt(Colour colour)
{
    switch (colour)
    {
    case Colour::Orange:
        return 3;
    case Colour::DarkBlue:
        return 4;
    case Colour::LightBlue:
        return 5;
    case Colour::Green:
        return 6;
    case Colour::Purple:
        return 7;
    case Colour::Red:
        return 8;
    case Colour::Yellow:
        return 9;
    case Colour::Brown:
        return 10;
    default:
        return 2;
    }
}

void GraphicsDisplay::updateTurn(int player_id) {
    int p1_colour = player_id == 1 ? 1 : 0;
    int p2_colour = player_id == 1 ? 0 : 1;
    const int w = 4; // border width
    // p1 turn border
    window.fillRectangle(p1_origin.first - w, p1_origin.second - (BOARD_HEIGHT - 4) * cell_size, w, (BOARD_HEIGHT - 3) * cell_size, p1_colour);
    window.fillRectangle(p1_origin.first + (BOARD_WIDTH * cell_size), p1_origin.second - (BOARD_HEIGHT - 4) * cell_size, w, (BOARD_HEIGHT - 3) * cell_size, p1_colour);
    window.fillRectangle(p1_origin.first - w, p1_origin.second - (BOARD_HEIGHT - 4) * cell_size - w, (BOARD_WIDTH * cell_size) + 2 * w, w, p1_colour);
    window.fillRectangle(p1_origin.first - w, p1_origin.second + cell_size, (BOARD_WIDTH * cell_size) + 2 * w, w, p1_colour);
    // p2 turn border
    window.fillRectangle(p2_origin.first - w, p2_origin.second - (BOARD_HEIGHT - 4) * cell_size, w, (BOARD_HEIGHT - 3) * cell_size, p2_colour);
    window.fillRectangle(p2_origin.first + (BOARD_WIDTH * cell_size), p2_origin.second - (BOARD_HEIGHT - 4) * cell_size, w, (BOARD_HEIGHT - 3) * cell_size, p2_colour);
    window.fillRectangle(p2_origin.first - w, p2_origin.second - (BOARD_HEIGHT - 4) * cell_size - w, (BOARD_WIDTH * cell_size) + 2 * w, w, p2_colour);
    window.fillRectangle(p2_origin.first - w, p2_origin.second + cell_size, (BOARD_WIDTH * cell_size) + 2 * w, w, p2_colour);

}

void GraphicsDisplay::notify(Subject &whoNotified)
{
    Info info = whoNotified.getInfo();
    if (typeid(whoNotified) == typeid(Player))
    { //if subject is a player
        updateTurn(info.id);
        if (info.id == 1)
        {
            window.fillRectangle(p1_origin.first, 40, 100, 50, 0); // whiteout drawn strings
            window.drawString(p1_origin.first, 50, "Level: " + std::to_string(info.level));
            window.drawString(p1_origin.first, 70, "Hi Score: " + std::to_string(info.hi_score));
            window.drawString(p1_origin.first, 90, "Score: " + std::to_string(info.score));
            p1_turn = info.is_turn;
        }
        else if (info.id == 2)
        {
            window.fillRectangle(p2_origin.first, 40, 100, 50, 0); // whiteout drawn strings
            window.drawString(p2_origin.first, 50, "Level: " + std::to_string(info.level));
            window.drawString(p2_origin.first, 70, "Hi Score: " + std::to_string(info.hi_score));
            window.drawString(p2_origin.first, 90, "Score: " + std::to_string(info.score));
            p1_turn = !info.is_turn;
        }
    }
    if (typeid(whoNotified) == typeid(Board))
    { //if subject is a board
        if (info.id == 1)
        {
            bool was_blind = p1_blind;
            p1_blind = info.blind;
            if (was_blind && !p1_blind)
            {
                unblind(info.id, p1_origin);
            } else if (!was_blind && p1_blind) {
                blind(p1_origin);
            }
            drawNextBlock(info.next_block, p1_origin);
        }
        else if (info.id == 2)
        {
            bool was_blind = p2_blind;
            p2_blind = info.blind;
            if (was_blind && !p2_blind)
            {
                unblind(info.id, p2_origin);
            } else if (!was_blind && p2_blind) {
                blind(p2_origin);
            }
            drawNextBlock(info.next_block, p2_origin);
        }
    }
    if (typeid(whoNotified) == typeid(Cell) && info.row < 15)
    { //if subject is a visible cell
        if (info.id == 1)
        {
            p1_cells[info.row][info.col] = colourToInt(info.colour);
            if (!p1_blind || ((info.row < 3 || info.row > 12) || (info.col < 3 || info.col > 9)))
            {
                window.fillRectangle(
                    p1_origin.first + info.col * cell_size,
                    p1_origin.second - info.row * cell_size,
                    cell_size, cell_size, colourToInt(info.colour));
            }
        }
        if (info.id == 2)
        {
            p2_cells[info.row][info.col] = colourToInt(info.colour);
            if (!p2_blind || ((info.row < 3 || info.row > 12) || (info.col < 3 || info.col > 9)))
            {
                window.fillRectangle(
                    p2_origin.first + info.col * cell_size,
                    p2_origin.second - info.row * cell_size,
                    cell_size, cell_size, colourToInt(info.colour));
            }
        }
    }
}
