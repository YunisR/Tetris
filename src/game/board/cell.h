#ifndef CELL_H
#define CELL_H
#include "colour.h"
#include "../../displays/subject.h"
#include "../../info.h"

class Cell : public Subject
{
    int x_pos;
    int y_pos;
    Colour colour;
    int player_id;

public:
    Cell(int x, int y, Colour colour, int player_id);
    Colour getColour();
    void setColour(Colour colour);
    Info getInfo() const override;
};

#endif
