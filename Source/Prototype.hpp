#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <iostream>
#include <memory>

// Description:
// Prototype is a creational design pattern that
// lets you copy existing objects without making
// your code dependent on their classes.

// Usage:
// 1. when your code shouldn’t depend on the concrete classes of objects that
// you need to copy.
// 2. when you want to reduce the number of subclasses that only differ in the
// way they initialize their respective objects.
// 3. Huge amount of objects that can be created from a smaller set of objects.
// 4. When you want to avoid a constructor telescoping anti-pattern.
// 5. When you want to avoid a factory class hierarchy.

class Prototype
{
public:
  Prototype()
  {
    std::cout << "Prototype instantiated" << std::endl;
  }
  virtual ~Prototype() = default;
  virtual std::unique_ptr<Prototype> clone() const = 0;
  virtual void print() const = 0;
};

class ConcretePrototype1 : public Prototype
{
public:
  ConcretePrototype1()
  {
    std::cout << "ConcretePrototype1 instantiated" << std::endl;
  }
  ConcretePrototype1(const ConcretePrototype1& prototype
                     [[maybe_unused]]) = default;
  virtual ~ConcretePrototype1() = default;

  std::unique_ptr<Prototype> clone() const override
  {
    std::cout << "ConcretePrototype1 cloned" << std::endl;
    return std::make_unique<ConcretePrototype1>(*this);
  }

  virtual void print() const override
  {
    std::cout << "ConcretePrototype1 printed" << std::endl;
  }
};

class ConcretePrototype2 : public Prototype
{
public:
  ConcretePrototype2()
  {
    std::cout << "ConcretePrototype2 instantiated" << std::endl;
  }
  ConcretePrototype2(const ConcretePrototype2& prototype
                     [[maybe_unused]]) = default;
  virtual ~ConcretePrototype2() = default;

  std::unique_ptr<Prototype> clone() const override
  {
    std::cout << "ConcretePrototype2 cloned" << std::endl;
    return std::make_unique<ConcretePrototype2>(*this);
  }

  virtual void print() const override
  {
    std::cout << "ConcretePrototype2 printed" << std::endl;
  }
};

// Tomáš Mark (c) 2025
#endif