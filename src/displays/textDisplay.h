#ifndef TEXT_DISPLAY_H
#define TEXT_DISPLAY_H
#include <vector>
#include "observer.h"
#include "../game/board/blocktype.h"
#include "../game/board/board.h"
#include "../game/player.h"
#include "../game/board/cell.h"
#include "../info.h"

class Cell;
class Player;
class Board;

class TextDisplay : public Observer
{
    std::vector<std::vector<char>> first_display;
    std::vector<std::vector<char>> second_display;
    BlockType next_block_p1; //next block for player 1
    BlockType next_block_p2; //next block for player 2
    // BlockType current_block_p1; //current block for player 1
    // BlockType current_block_p2; //current block for player 2
    int score_p1;    //current player 1 score
    int score_p2;    //current player 2 score
    int hi_score_p1; //p1 high score
    int hi_score_p2; //p2 high score
    int level_p1;    //current player 1 level
    int level_p2;    //current player 2 level
    bool blind_p1;
    bool blind_p2;
    char colourToChar(Colour colour);

public:
    TextDisplay();
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &t);
    void notify(Subject &whoNotified) override;
};
#endif
