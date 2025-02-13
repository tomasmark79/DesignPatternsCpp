#ifndef LOWCOUPLING_H
#define LOWCOUPLING_H

#include <iostream>

// Low Coupling Design Pattern
// reduce dependency
// create as few dependencies between objects as possible
// smartly dividing responsibilities

class LowCoupling {
public:
  LowCoupling() { std::cout << "LowCoupling::LowCoupling()" << std::endl; }
};

#endif