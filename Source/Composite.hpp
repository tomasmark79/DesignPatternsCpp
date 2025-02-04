#ifndef COMPOSITE_H
#define COMPOSITE_H

#include <iostream>
#include <list>
#include <string>

class ComponentComposite
{
public:
  virtual void add(ComponentComposite* component [[maybe_unused]]) {}
  virtual void remove(ComponentComposite* component [[maybe_unused]]) {}
  virtual void operation() = 0;
  virtual ~ComponentComposite() {}
};

class Composite : public ComponentComposite
{
public:
  Composite(std::string name) : name_(name) {}
  void add(ComponentComposite* component) override
  {
    children_.push_back(component);
  }
  void remove(ComponentComposite* component) override
  {
    children_.remove(component);
  }
  void operation() override
  {
    std::cout << "Composite " << name_ << " operation" << std::endl;
    for (auto child : children_)
    {
      child->operation();
    }
  }

private:
  std::string name_;
  std::list<ComponentComposite*> children_;
};

class Leaf : public ComponentComposite
{
public:
  Leaf(std::string name) : name_(name) {}
  void operation() override
  {
    std::cout << "Leaf " << name_ << " operation" << std::endl;
  }

private:
  std::string name_;
};

#endif