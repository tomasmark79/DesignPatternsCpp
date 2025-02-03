#ifndef FACTORYMETHOD_H
#define FACTORYMETHOD_H

#include <string>

class Computer
{
public:
  Computer(std::string computer, std::string model) :
    computer(computer),
    model(model){};
  ~Computer(){};

public:
  std::string computer;
  std::string model;
};

class ComputerFactory
{
public:
  ComputerFactory(){};
  ~ComputerFactory(){};
  Computer* createComputer(std::string computer, std::string model);
};

#endif