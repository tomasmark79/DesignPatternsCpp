
#include <GofLib/GofLib.hpp>
#include <goflib/version.h>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>

int main()
{
  std::unique_ptr<GofLib> lib = std::make_unique<GofLib>(); // cpp14 +


  return 0;
}
