#ifndef BUILDER_H
#define BUILDER_H

#include <iostream>

class Builder
{
public:
  Builder()
  {
    std::cout << "Builder instantiated" << std::endl;
  }
  virtual ~Builder() = default;

  virtual void buildPart1() = 0;
  virtual void buildPart2() = 0;
  virtual void buildPart3() = 0;
};

class ConcreteBuilder : public Builder
{
public:
  ConcreteBuilder() = default;
  ~ConcreteBuilder() = default;

  void buildPart1() override
  {
    std::cout << "Building part 1" << std::endl;
  }

  void buildPart2() override
  {
    std::cout << "Building part 2" << std::endl;
  }

  void buildPart3() override
  {
    std::cout << "Building part 3" << std::endl;
  }
};

class Director
{
public:
  Director() = default;
  ~Director() = default;

  void setBuilder(Builder* builder)
  {
    m_builder = builder;
  }

  void construct()
  {
    m_builder->buildPart1();
    m_builder->buildPart2();
    m_builder->buildPart3();
  }

private:
  Builder* m_builder;
};

#endif