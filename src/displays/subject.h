#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include <memory>
#include "../info.h"
#include "observer.h"

class Subject
{
  Info info;
  protected:
    std::vector<Observer *> observers;

  public:
    virtual void attach(Observer *o);
    void notifyObservers();
    virtual Info getInfo() const = 0;
};

#endif
