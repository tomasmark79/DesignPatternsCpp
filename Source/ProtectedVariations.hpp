#ifndef PROTECTEDVARIATIONS_H
#define PROTECTEDVARIATIONS_H

#include <iostream>

// Protected Variations Design Pattern
// is a design pattern that allows for the creation of a stable interface
// that can be used to interact with a system, while allowing the
// implementation of the system to change without affecting the interface.
// This design pattern is useful when the implementation of a system is
// likely to change, but the interface to the system should remain stable.

class ProtectedVariations
{
public:
  ProtectedVariations()
  {
    std::cout << "ProtectedVariations::ProtectedVariations()" << std::endl;
  }
};

#endif