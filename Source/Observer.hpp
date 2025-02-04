#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
#include <list>

class Observer
{
public:
  virtual void update() = 0;
};

class ConcreteObserverA : public Observer
{
public:
  void update() override
  {
    std::cout << "ConcreteObserverA::update()" << std::endl;
  }
};

class ConcreteObserverB : public Observer
{
public:
  void update() override
  {
    std::cout << "ConcreteObserverB::update()" << std::endl;
  }
};

class Subject
{
public:
  virtual void attach(Observer* observer) = 0;
  virtual void detach(Observer* observer) = 0;
  virtual void notify() = 0;
};

class ConcreteSubject : public Subject
{
public:
  void attach(Observer* observer) override
  {
    m_observers.push_back(observer);
  }

  void detach(Observer* observer) override
  {
    m_observers.remove(observer);
  }

  void notify() override
  {
    for (auto observer : m_observers)
    {
      observer->update();
    }
  }

private:
  std::list<Observer*> m_observers;
};

#endif