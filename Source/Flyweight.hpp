#ifndef FLYWEIGHT_H
#define FLYWEIGHT_H

#include <iostream>
#include <memory>
#include <map>

class Flyweight
{
public:
  virtual ~Flyweight() = default;
  virtual void operation() const = 0;
};

class ConcreteFlyweight : public Flyweight
{
private:
  std::string intrinsicState;

public:
  ConcreteFlyweight(const std::string& intrinsicState) :
    intrinsicState(intrinsicState)
  {}
  void operation() const override
  {
    std::cout << "ConcreteFlyweight with intrinsic state: " << intrinsicState
              << std::endl;
  }
};

class FlyweightFactory
{
private:
  std::map<std::string, std::shared_ptr<Flyweight>> flyweights;

public:
  std::shared_ptr<Flyweight> getFlyweight(const std::string& key)
  {
    if (flyweights.find(key) == flyweights.end())
    {
      flyweights[key] = std::make_shared<ConcreteFlyweight>(key);
    }
    return flyweights[key];
  }
};

#endif