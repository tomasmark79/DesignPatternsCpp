#ifndef BUILDER_H
#define BUILDER_H

// Description:
// Builder pattern is a creational design pattern that lets you
// construct complex objects step by step.
// The pattern allows you to produce different types and representations
// of an object using the same construction code.
//
//    ┌───────────────────────┐                                    
//    │ConcreteBuilder        │   ┌───────────────────────────────┐
//    ├───────────────────────┤   │Director                       │
//    │- product: Product*    │   ├───────────────────────────────┤
//    │+ buildPartA()         │   │- builder: Builder*            │
//    │+ buildPartB()         │   │+ setBuilder(builder: Builder*)│
//    │+ buildPartC()         │   │+ construct()                  │
//    │+ getProduct(): Product│   └───────────────────────────────┘
//    └───────────────────────┘                                    
//                 |                                               
//                 |                                               
// ┌──────────────────────────────┐                                
// │Product                       │   ┌───────────────────────┐    
// ├──────────────────────────────┤   │Builder                │    
// │- partA: std::string          │   ├───────────────────────┤    
// │- partB: std::string          │   │+ buildPartA()         │    
// │- partC: std::string          │   │+ buildPartB()         │    
// │+ setPartA(partA: std::string)│   │+ buildPartC()         │    
// │+ setPartB(partB: std::string)│   │+ getProduct(): Product│    
// │+ setPartC(partC: std::string)│   └───────────────────────┘    
// │+ show()                      │                                
// └──────────────────────────────┘                                 
// Tomáš Mark (c) 2025

#include <iostream>
#include <string>

// Product class is the final object that will be created by the builder
class Product
{
public:
  void setPartA(const std::string& partA)
  {
    m_partA = partA;
  }

  void setPartB(const std::string& partB)
  {
    m_partB = partB;
  }

  void setPartC(const std::string& partC)
  {
    m_partC = partC;
  }

  void show() const
  {
    std::cout << "Product Parts: " << m_partA << ", " << m_partB << ", " << m_partC
              << std::endl;
  }

private:
  std::string m_partA;
  std::string m_partB;
  std::string m_partC;
};

// Builder class is the abstract class that will be implemented by the concrete
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
  virtual Product getProduct() = 0;
};

// ConcreteBuilder class is the concrete class that will implement the Builder
class ConcreteBuilder : public Builder
{
public:
  ConcreteBuilder() : m_product(new Product())
  {
    std::cout << "ConcreteBuilder instantiated" << std::endl;
  }

  ~ConcreteBuilder() {
    delete m_product;
  }

  void buildPart1() override
  {
    m_product->setPartA("Part A");
  }

  void buildPart2() override
  {
    m_product->setPartB("Part B");
  }

  void buildPart3() override
  {
    m_product->setPartC("Part C");
  }

  Product getProduct() override
  {
    return *m_product;
  }

  private:
    Product* m_product;
};

// Director class is the class that will direct the builder to build the product
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