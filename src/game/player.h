#ifndef PLAYER_H
#define PLAYER_H
#include "levels/level.h"
#include "board/board.h"
#include "../displays/subject.h"
#include "../info.h"

class Player : public Subject
{
    int hi_score;
    int score;
    int id;
    std::string source;

    bool is_turn;

    std::unique_ptr<Level> level;
    std::unique_ptr<Board> board;
    bool sent_move;

    void updateScore(int score_increase);

    public:
        Player(int id, std::string source, int level_num, int hi_score);
        void clearBoard();
        void rotateCW(int n);
        void rotateCCW(int n);
        void moveLeft(int n);
        void moveRight(int n);
        void moveDown(int n);
        void drop(int n);
        void increaseLevel(int n);
        void decreaseLevel(int n);
        void setSource(std::string source);
        void resetLevel();
        bool hasPlacedBlock();
        void setNextBlock(BlockType block);
        void swapTurn();
        int getLevel();
        int getHiScore();
        bool sentMove() const;
        void sendMove(SpecialMove move, BlockType forced_block);
        void attach(Observer *o) override;
        Info getInfo() const override;
};

#endif
