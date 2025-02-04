#ifndef BRIDGE_H
#define BRIDGE_H

#include <iostream>

class Bridge
{
public:
  virtual ~Bridge() {}
  virtual void operation() = 0;
};

class Implementor
{
public:
  virtual ~Implementor() {}
  virtual void operation() = 0;
};

class ConcreteImplementorA : public Implementor
{
public:
  void operation() override
  {
    std::cout << "ConcreteImplementorA operation" << std::endl;
  }
};

class ConcreteImplementorB : public Implementor
{
public:
  void operation() override
  {
    std::cout << "ConcreteImplementorB operation" << std::endl;
  }
};

class RefinedAbstraction : public Bridge
{
public:
  RefinedAbstraction(Implementor* implementor) : implementor_(implementor) {}
  ~RefinedAbstraction()
  {
    delete implementor_;
  }
  void operation() override
  {
    std::cout << "RefinedAbstraction operation" << std::endl;
    implementor_->operation();
  }

private:
  Implementor* implementor_;
};

#endif