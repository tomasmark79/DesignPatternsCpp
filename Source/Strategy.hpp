#ifndef STRATEGY_H
#define STRATEGY_H

#include <iostream>

class Strategy {
public:
  virtual void algorithm() = 0;
};

class ConcreteStrategyA : public Strategy {
public:
  void algorithm() override {
    std::cout << "ConcreteStrategyA::algorithm()" << std::endl;
  }
};

class ConcreteStrategyB : public Strategy {
public:
  void algorithm() override {
    std::cout << "ConcreteStrategyB::algorithm()" << std::endl;
  }
};

class Context {
public:
  Context(Strategy* strategy) { this->strategy = strategy; }

  void contextInterface() { strategy->algorithm(); }

private:
  Strategy* strategy;
};

#endif