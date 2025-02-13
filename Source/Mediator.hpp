#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <iostream>

class Mediator {
public:
  virtual void notify(int id) = 0;
};

class ConcreteMediator : public Mediator {
public:
  void notify(int id) override {
    std::cout << "ConcreteMediator: notify " << id << std::endl;
  }
};

class Colleague {
public:
  Colleague(Mediator* mediator) : mediator_(mediator) { }
  void notify(int id) { mediator_->notify(id); }

private:
  Mediator* mediator_;
};

class ConcreteColleagueA : public Colleague {
public:
  ConcreteColleagueA(Mediator* mediator) : Colleague(mediator) { }
};

class ConcreteColleagueB : public Colleague {
public:
  ConcreteColleagueB(Mediator* mediator) : Colleague(mediator) { }
};

#endif