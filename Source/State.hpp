#ifndef STATE_H
#define STATE_H

#include <iostream>

class State
{
public:
  virtual ~State() {}
  virtual void handle() = 0;
};

class ConcreteStateA : public State
{
public:
  void handle() override
  {
    std::cout << "ConcreteStateA handles request." << std::endl;
  }
};

class ConcreteStateB : public State
{
public:
  void handle() override
  {
    std::cout << "ConcreteStateB handles request." << std::endl;
  }
};

class ContextState
{
public:
  ContextState(State* state) : state(state) {}
  ~ContextState()
  {
    delete state;
  }
  void setState(State* state)
  {
    delete this->state;
    this->state = state;
  }
  void request()
  {
    state->handle();
  }

private:
  State* state;
};

#endif