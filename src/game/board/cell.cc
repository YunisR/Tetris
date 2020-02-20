#include "cell.h"

Cell::Cell(int x, int y, Colour colour, int player_id) : x_pos{x}, y_pos{y}, colour{colour}, player_id(player_id) {}

Colour Cell::getColour()
{
    return colour;
}

void Cell::setColour(Colour colour)
{
    this->colour = colour;
    notifyObservers();
}

Info Cell::getInfo() const
{
    return Info(player_id, x_pos, y_pos, colour);
}
