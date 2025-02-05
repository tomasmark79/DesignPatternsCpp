#ifndef INFORMATIONEXPERT_H
#define INFORMATIONEXPERT_H

#include <iostream>

// Information Expert Design Pattern

// Responsibility always lies with the class that has the most information

class InformationExpert
{
public:
  InformationExpert()
  {
    std::cout << "InformationExpert::InformationExpert()" << std::endl;
  }
};

#endif