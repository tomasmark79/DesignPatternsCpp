#ifndef DECORATOR_H
#define DECORATOR_H

#include <iostream>
#include <memory>

// Abstract class that defines the Operation interface.
class Component {
public:
  virtual ~Component() = default;
  virtual void Operation() const = 0;
};

// Implements the Component interface and provides a basic implementation of the
// Operation method.
class ConcreteComponent : public Component {
public:
  void Operation() const override {
    std::cout << "ConcreteComponent Operation" << std::endl;
  }
};

// Abstract class that implements the Component interface and contains a pointer
// to a component.
class Decorator : public Component {
protected:
  std::shared_ptr<Component> component;

public:
  Decorator(std::shared_ptr<Component> comp) : component(comp) { }
  void Operation() const override { component->Operation(); }
};

// Extend the functionality of the component by adding their own operations.
class ConcreteDecoratorA : public Decorator {
public:
  ConcreteDecoratorA(std::shared_ptr<Component> comp) : Decorator(comp) { }
  void Operation() const override {
    Decorator::Operation();
    std::cout << "ConcreteDecoratorA Operation" << std::endl;
  }
};

// Extend the functionality of the component by adding their own operations.
class ConcreteDecoratorB : public Decorator {
public:
  ConcreteDecoratorB(std::shared_ptr<Component> comp) : Decorator(comp) { }
  void Operation() const override {
    Decorator::Operation();
    std::cout << "ConcreteDecoratorB Operation" << std::endl;
  }
};

#endif