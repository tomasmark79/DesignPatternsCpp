#include "FactoryMethod.hpp"

#include <iostream>

Computer* ComputerFactory::createComputer(
    std::string computer, std::string model) {
  std::cout << "FactoryMethod instantiated" << std::endl;
  return new Computer(computer, model);
};