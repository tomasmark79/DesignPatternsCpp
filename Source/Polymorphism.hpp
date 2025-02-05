#ifndef POLYMORPHISM_H
#define POLYMORPHISM_H

#include <iostream>
#include <string>

// Polymorphism Design Pattern
// is a design pattern that allows objects to be treated as
// instances of their parent class. This allows for the creation of a single
// interface that can be used to interact with multiple objects. Polymorphism is
// a key concept in object-oriented programming, as it allows for the creation
// of flexible and reusable code.

// **1. Compile-time (static) polymorphism**
// Function Overloading Example
void print(int x)
{
  std::cout << "Integer: " << x << std::endl;
}

void print(double x)
{
  std::cout << "Floating-point: " << x << std::endl;
}

void print(std::string x)
{
  std::cout << "String: " << x << std::endl;
}

// **2. Run-time (dynamic) polymorphism**
// Using inheritance and virtual functions
class Animal
{
public:
  virtual void sound()
  { // Virtual function
    std::cout << "The animal makes a sound" << std::endl;
  }
};

class Dog : public Animal
{
public:
  void sound() override
  { // Overriding method
    std::cout << "Woof woof!" << std::endl;
  }
};

class Cat : public Animal
{
public:
  void sound() override
  {
    std::cout << "Meow!" << std::endl;
  }
};

#endif