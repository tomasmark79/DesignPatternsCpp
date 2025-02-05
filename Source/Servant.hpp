#ifndef SERVANT_H
#define SERVANT_H

#include <iostream>

// Servant Design Pattern
// is a design pattern that allows for the creation of a separate class
// that is responsible for performing specific tasks on behalf of another
// class. The servant class encapsulates the logic or functionality that
// is shared by multiple classes, allowing the client classes to delegate
// the work to the servant class. This design pattern is useful for
// reducing code duplication and promoting code reuse.

class Servant
{
public:
  void operate(int& value) const
  {
    value += 1;
  }
};

class Client
{
public:
  Client(int value) : m_value(value) {}

  void accept(Servant& servant)
  {
    servant.operate(m_value);
  }

  int getValue() const
  {
    return m_value;
  }

private:
  int m_value;
};

#endif