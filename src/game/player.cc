#include "player.h"
#include "board/blocktype.h"
#include "levels/level0.h"
#include "levels/level1.h"
#include "levels/level2.h"
#include "levels/level3.h"
#include "levels/level4.h"
#include <iostream>

Player::Player(int id, std::string source, int level_num, int hi_score) : hi_score{hi_score}, score{0}, id{id}, source{source}
{
    switch(level_num)
    {
        case 0: level = std::make_unique<Level0>(source);
            break;
        case 1: level = std::make_unique<Level1>();
            break;
        case 2: level = std::make_unique<Level2>();
            break;
        case 3: level = std::make_unique<Level3>();
            break;
        case 4: level = std::make_unique<Level4>();
            break;
    }
    BlockType active_block_type = level->getNextBlock();
    BlockType next_block_type = level->getNextBlock();
    board = std::make_unique<Board>(active_block_type, next_block_type, level_num, id);
}

void Player::updateScore(int score_increase) {
    score += score_increase;
    hi_score = std::max(hi_score, score);
    notifyObservers();
}

void Player::clearBoard() {
    board->resetBoard();
}

void Player::rotateCW(int n) {
    board->rotateCW(n);
}

void Player::rotateCCW(int n) {
    board->rotateCCW(n);
}

void Player::moveLeft(int n) {
    board->moveLeft(n);
}

void Player::moveRight(int n) {
    board->moveRight(n);
}

void Player::moveDown(int n) {
    board->moveDown(n);
}

void Player::drop(int n) {
    for (int i = 0; i < n; ++i) {
        board->drop();
        if (i < n - 1) {
            hasPlacedBlock();
        }
    }
    
}

void Player::increaseLevel(int n) {
    int new_level = std::min(level->getLevel() + n, 4);
    switch(new_level)
    {
        case 1: level.reset(new Level1());
            break;
        case 2: level.reset(new Level2());
            break;
        case 3: level.reset(new Level3());
            break;
        case 4: level.reset(new Level4());
            break;
    }
    board->setLevel(new_level);
    notifyObservers();
}

void Player::decreaseLevel(int n) {
    int new_level = std::max(level->getLevel() - n, 0);
    switch(new_level)
    {
        case 0: level.reset(new Level0(source));
            break;
        case 1: level.reset(new Level1());;
            break;
        case 2: level.reset(new Level2());;
            break;
        case 3: level.reset(new Level3());;
            break;
    }
    board->setLevel(new_level);
    notifyObservers();
}

void Player::setSource(std::string source) {
    level->setSource(source);
}

void Player::resetLevel() {
    level->resetLevel();
}

bool Player::hasPlacedBlock()
{
    if(board->hasPlacedBlock())
    {
        board->placeActiveBlock();
        updateScore(board->clearRows(level->getLevel()));
        sent_move = board->sentMove();
        board->checkLevelEffects();
        board->updateActiveBlock();
        setNextBlock(level->getNextBlock());
        return true;
    }
    return false;
}

void Player::swapTurn() {
    is_turn = !is_turn;
    notifyObservers();
}

void Player::setNextBlock(BlockType block) {
    board->setNextBlock(block);
}

int Player::getLevel()
{
    return level->getLevel();
}

int Player::getHiScore()
{
    return hi_score;
}

bool Player::sentMove() const {
    return sent_move;
}

void Player::sendMove(SpecialMove move, BlockType forced_block) {
    switch (move) {
        case SpecialMove::Blind:
            board->makeBlind();
            break;
        case SpecialMove::Heavy:
            board->makeHeavy();
            break;
        case SpecialMove::Force:
            board->replaceActiveBlock(forced_block);
            break;
        default:
            break;
    }
}

void Player::attach(Observer *o) {
    observers.emplace_back(o);
    for (auto &ob : observers) {
        board->attach(ob);
    }
    board->notifyObservers();
}

Info Player::getInfo() const {
    return Info(id, hi_score, score, level->getLevel(), is_turn);
}
