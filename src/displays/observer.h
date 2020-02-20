#ifndef _OBSERVER_H
#define _OBSERVER_H

class Subject;
class Cell;
class Player;
class Board;

class Observer
{
public:
    virtual void notify(Subject &whoFrom) = 0;
};

#endif
