#ifndef GAME_H
#define GAME_H
#include <memory>
#include "player.h"
#include "controller.h"
#include <cstdlib>

#include "../displays/observer.h"
#include "../displays/textDisplay.h"
#include "../displays/graphicDisplay.h"

class Game
{
    bool text_only = false;
    std::string p1_source;
    std::string p2_source;
    int level = 0;
    bool use_keyboard = false;
    int seed;

    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    bool p1_turn;
    Controller controller;
    std::unique_ptr<TextDisplay> td;
    std::unique_ptr<GraphicsDisplay> gd;

    // for testing
    bool is_over;

public:
    Game(bool text_only, int seed, std::string p1_source, std::string p2_source, int level, bool use_keyboard);
    void start(int p1_hi_score = 0, int p2_hi_score = 0);
    void restart();
};

#endif
