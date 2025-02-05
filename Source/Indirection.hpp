#ifndef INDIRECTION_H
#define INDIRECTION_H

#include <iostream>

// Indirection Design Pattern

// Usage:
// The Indirection design pattern is a design pattern that is used to provide a
// level of indirection between the client code and the implementation of a
// class.

class Indirection
{
public:
  Indirection()
  {
    std::cout << "Indirection::Indirection()" << std::endl;
  }
};

#endif