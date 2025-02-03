#ifndef FACADE_H
#define FACADE_H

#include <iostream>

class Subsystem1
{
public:
  void operation1()
  {
    std::cout << "Subsystem1::operation1" << std::endl;
  }

  void operation2()
  {
    std::cout << "Subsystem1::operation2" << std::endl;
  }
};

class Subsystem2
{
public:
  void operation1()
  {
    std::cout << "Subsystem2::operation1" << std::endl;
  }

  void operation2()
  {
    std::cout << "Subsystem2::operation2" << std::endl;
  }
};

class Facade
{
public:
  Facade()
  {
    subsystem1 = new Subsystem1();
    subsystem2 = new Subsystem2();
  }

  ~Facade()
  {
    delete subsystem1;
    delete subsystem2;
  }

  void operation()
  {
    subsystem1->operation1();
    subsystem1->operation2();
    subsystem2->operation1();
    subsystem2->operation2();
  }

protected:
  Subsystem1* subsystem1;
  Subsystem2* subsystem2;
};

#endif