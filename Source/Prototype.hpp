#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>

class Prototype
{
public:
  Prototype() {
    std::cout << "Prototype instantiated" << std::endl;
  };
  virtual ~Prototype() {};
  virtual Prototype* clone() = 0;
  virtual void print() = 0;
};

class ConcretePrototype1 : public Prototype
{
public:
  ConcretePrototype1() {
    std::cout << "ConcretePrototype1 created" << std::endl;
  };
  ConcretePrototype1(const ConcretePrototype1& prototype) {};
  virtual ~ConcretePrototype1() {};
  virtual Prototype* clone()
  {
    std::cout << "ConcretePrototype1 cloned" << std::endl;
    return new ConcretePrototype1(*this);
  };
  
  virtual void print() override {
    std::cout << "ConcretePrototype1 printed" << std::endl;
  };
};

class ConcretePrototype2 : public Prototype
{
public:
  ConcretePrototype2() {
    std::cout << "ConcretePrototype2 created" << std::endl;
  };
  ConcretePrototype2(const ConcretePrototype2& prototype) {};
  virtual ~ConcretePrototype2() {};
  virtual Prototype* clone()
  {
    std::cout << "ConcretePrototype2 cloned" << std::endl;
    return new ConcretePrototype2(*this);
  };

  virtual void print() override {
    std::cout << "ConcretePrototype2 printed" << std::endl;
  };
};

#endif