#ifndef IMMUTABLEOBJECTS_H
#define IMMUTABLEOBJECTS_H

#include <iostream>
#include <string>

class ImmutableObjects {
public:
  ImmutableObjects(const std::string& name, int value) :
      m_name(name), m_value(value) {
    std::cout << "ImmutableObjects instantiated" << std::endl;
  }
  virtual ~ImmutableObjects() = default;

  virtual void operation() const = 0;

  const std::string& getName() const { return m_name; }
  int getValue() const { return m_value; }

private:
  const std::string m_name;
  const int m_value;
};

class ConcreteImmutableObjects : public ImmutableObjects {
public:
  ConcreteImmutableObjects(const std::string& name, int value) :
      ImmutableObjects(name, value) {
    std::cout << "ConcreteImmutableObjects instantiated" << std::endl;
  }
  virtual ~ConcreteImmutableObjects() = default;

  void operation() const override {
    std::cout << "ConcreteImmutableObjects operation" << std::endl;
  }
};

#endif