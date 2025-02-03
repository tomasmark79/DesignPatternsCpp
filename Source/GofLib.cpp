#include "GofLib/GofLib.hpp"

// #include <EmojiTools/EmojiTools.hpp> // yet dissabled
#include <iostream>
#include <goflib/version.h>

#include <Builder.hpp>
#include <Prototype.hpp>
#include <Singleton.hpp>
#include <FactoryMethod.hpp>

GofLib::GofLib()
{
  std::cout << "--- GofLib v." << GOFLIB_VERSION << " instantiated ---"
            << std::endl;

  // Builder
  ConcreteBuilder* concreteBuilder = new ConcreteBuilder();
  Director* director = new Director();
  director->setBuilder(concreteBuilder);
  director->construct();
  delete director;
  delete concreteBuilder;
    
  // Prototype
  Prototype* prototype1 = new ConcretePrototype1();
  Prototype* prototype2 = new ConcretePrototype2();
  Prototype* prototype3 = prototype1->clone();
  Prototype* prototype4 = prototype2->clone();
  prototype1->print();
  prototype2->print();
  prototype3->print();
  prototype4->print();
    
  // Singleton - anti-pattern
  Singleton& singleton = Singleton::getInstance();
  singleton.print();

  // Factory Method
  ComputerFactory* computerFactory = new ComputerFactory();
  Computer* computer = computerFactory->createComputer("HP", "FireFly 14");
  std::cout << "Computer: " << computer->computer << " Model: " << computer->model << std::endl;
  delete computerFactory;
  delete computer;
}

GofLib::~GofLib()
{
  std::cout << "--- GofLib uninstantiated ---" << std::endl;
}
