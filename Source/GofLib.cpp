#include "GofLib/GofLib.hpp"

// #include <EmojiTools/EmojiTools.hpp> // yet dissabled
#include <iostream>
#include <goflib/version.h>

#include <Singleton.hpp>
#include <FactoryMethod.hpp>

GofLib::GofLib()
{
  std::cout << "--- GofLib v." << GOFLIB_VERSION << " instantiated ---"
            << std::endl;

  // Singleton
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
