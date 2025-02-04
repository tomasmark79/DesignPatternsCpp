#ifndef MEMENTO_H
#define MEMENTO_H

class Memento
{
public:
  Memento(int state) : state_(state) {}
  int getState() const
  {
    return state_;
  }

private:
  int state_;
};

class Originator
{
public:
  Originator() : state_(0) {}
  void setState(int state)
  {
    state_ = state;
  }
  int getState() const
  {
    return state_;
  }
  Memento createMemento()
  {
    return Memento(state_);
  }
  void setMemento(const Memento& memento)
  {
    state_ = memento.getState();
  }

private:
  int state_;
};

class Caretaker
{
public:
  Caretaker(Originator* originator) : originator_(originator), memento_(0) {}
  void saveState()
  {
    memento_ = originator_->createMemento();
  }
  void restoreState()
  {
    originator_->setMemento(memento_);
  }

private:
  Originator* originator_;
  Memento memento_;
};

#endif