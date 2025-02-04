#ifndef TEMPLATEMETHOD_H
#define TEMPLATEMETHOD_H

#include <iostream>

class TemplateMethod
{
public:
  virtual ~TemplateMethod() = default;

  void templateMethod()
  {
    primitiveOperation1();
    primitiveOperation2();
    std::cout << "Template Method" << std::endl;
  }

protected:
  virtual void primitiveOperation1() = 0;
  virtual void primitiveOperation2() = 0;
};

class ConcreteTemplateMethodA : public TemplateMethod
{
protected:
  void primitiveOperation1() override
  {
    std::cout << "ConcreteTemplateMethodA::primitiveOperation1" << std::endl;
  }

  void primitiveOperation2() override
  {
    std::cout << "ConcreteTemplateMethodA::primitiveOperation2" << std::endl;
  }
};

class ConcreteTemplateMethodB : public TemplateMethod
{
protected:
  void primitiveOperation1() override
  {
    std::cout << "ConcreteTemplateMethodB::primitiveOperation1" << std::endl;
  }

  void primitiveOperation2() override
  {
    std::cout << "ConcreteTemplateMethodB::primitiveOperation2" << std::endl;
  }
};

#endif