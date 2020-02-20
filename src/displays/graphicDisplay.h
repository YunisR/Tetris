#ifndef GRAPHICS_DISPLAY_H
#define GRAPHICS_DISPLAY_H
#include <utility>
#include "observer.h"
#include <vector>
#include "window.h"

#include "../info.h"

class Cell;
class Player;
class Board;

class GraphicsDisplay : public Observer
{
    const int height = 700; // in pixels
    const int width = 800; // in pixels
    const int cell_size = 30; // in pixels
    const std::pair<int, int> p1_origin = std::make_pair(30, 550);
    const std::pair<int, int> p2_origin = std::make_pair(440, 550);
    
    Xwindow window;

    std::vector<std::vector<int>> p1_cells;
    std::vector<std::vector<int>> p2_cells;
    bool p1_blind, p2_blind;
    bool p1_turn;

    void drawNextBlock(BlockType type, std::pair<int, int> origin);
    void blind(std::pair<int, int>);
    void unblind(int player_id, std::pair<int, int>);
    void updateTurn(int player_id);

public:
    GraphicsDisplay();
    void notify(Subject &whoNotified) override;
};

#endif
