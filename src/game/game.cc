#include <iostream>
#include "game.h"
#include "board/blocktype.h"

Game::Game(bool text_only, int seed, std::string p1_source, std::string p2_source, int level, bool use_keyboard)
    : text_only(text_only), p1_source(p1_source), p2_source(p2_source),
      level(level), use_keyboard(use_keyboard), seed{seed}, p1_turn{true}, controller(Controller()), is_over(false)
{
    srand(seed);
}

void Game::start(int p1_hi_score, int p2_hi_score)
{

    p1_turn = true;
    player1 = std::make_unique<Player>(1, p1_source, level, p1_hi_score);
    player2 = std::make_unique<Player>(2, p2_source, level, p2_hi_score);

    td = std::make_unique<TextDisplay>();
    if (!text_only)
    {
        gd = std::make_unique<GraphicsDisplay>();
        player1->attach(gd.get());
        player2->attach(gd.get());
    }

    player1->attach(td.get());
    player2->attach(td.get());
    player1->notifyObservers();
    player2->notifyObservers();

    std::string source;
    int n;
    Player *cur_player = player1.get();
    cur_player->swapTurn();

    std::cout << *(td.get()) << std::endl;
    if (!use_keyboard)
    {
        std::cout << "Player 1 Move:" << std::endl;
    }

    try
    {
        while (true)
        {
            n = 1;
            Action move = controller.readInput(source, n, use_keyboard);
            switch (move)
            {
            case Action::left:
                cur_player->moveLeft(n);
                break;
            case Action::right:
                cur_player->moveRight(n);
                break;
            case Action::down:
                cur_player->moveDown(n);
                break;
            case Action::drop:
                cur_player->drop(n);
                break;
            case Action::clockwise:
                cur_player->rotateCW(n);
                break;
            case Action::counterClockwise:
                cur_player->rotateCCW(n);
                break;
            case Action::levelUp:
                cur_player->increaseLevel(n);
                break;
            case Action::levelDown:
                cur_player->decreaseLevel(n);
                break;
            case Action::noRandom:
                cur_player->setSource(source);
                break;
            case Action::random:
                cur_player->resetLevel();
                break;
            case Action::sequence:
                cur_player->setSource(source);
                break;
            case Action::restart:
                restart();
                break;
            case Action::I:
                cur_player->setNextBlock(BlockType::I);
                break;
            case Action::J:
                cur_player->setNextBlock(BlockType::J);
                break;
            case Action::L:
                cur_player->setNextBlock(BlockType::L);
                break;
            case Action::T:
                cur_player->setNextBlock(BlockType::T);
                break;
            case Action::S:
                cur_player->setNextBlock(BlockType::S);
                break;
            case Action::Z:
                cur_player->setNextBlock(BlockType::Z);
                break;
            case Action::O:
                cur_player->setNextBlock(BlockType::O);
                break;
            case Action::end:
                is_over = true;
                break;
            case Action::useKeyboard:
                use_keyboard = true;
                break;
            case Action::endKeyboard:
                use_keyboard = false;
                break;
            default:
                break;
            }

            if (is_over)
                break;

            if (cur_player->hasPlacedBlock())
            {
                cur_player->swapTurn();
                if (p1_turn)
                {
                    if (cur_player->sentMove())
                    {
                        std::cout << *(td.get()) << std::endl;
                        BlockType forced_block = BlockType::NoType;
                        SpecialMove move = controller.readSpecialMove(use_keyboard, forced_block);
                        player2->sendMove(move, forced_block);
                    }
                    cur_player = player2.get();
                }
                else
                {
                    if (cur_player->sentMove())
                    {
                        std::cout << *(td.get()) << std::endl;
                        BlockType forced_block = BlockType::NoType;
                        SpecialMove move = controller.readSpecialMove(use_keyboard, forced_block);
                        player1->sendMove(move, forced_block);
                    }
                    cur_player = player1.get();
                }
                cur_player->swapTurn();
                p1_turn = !p1_turn;
            }
            std::cout << *(td.get()) << std::endl;
            if (!use_keyboard)
            {
                std::cout << "Player " << ((p1_turn) ? 1 : 2) << " Move: " << std::endl;
            }
        }
    }
    catch (InvalidBlockCreationException &e)
    {
        std::cout << "Player " << ((p1_turn) ? 2 : 1) << " Wins!" << std::endl;
        return;
    }
}

void Game::restart()
{ // reset level

    // // reset player score
    // player1->resetScore();
    // player2->resetScore();
    // // clear board
    // player1->clearBoard();
    // player2->clearBoard();
    // int p1_hi_score = player1->getHiScore();
    // int p2_hi_score = player2->getHiScore();
    // srand(seed);
    start(player1->getHiScore(), player2->getHiScore());
}
