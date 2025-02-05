
#include <DesignPatternsCppLib/DesignPatternsCppLib.hpp>
#include <designpatternscpplib/version.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main()
{
  std::unique_ptr<DesignPatternsCppLib> lib = std::make_unique<DesignPatternsCppLib>(); // cpp14 +

  return 0;
}
