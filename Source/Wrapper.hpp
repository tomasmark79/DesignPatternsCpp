#ifndef WRAPPER_H
#define WRAPPER_H

#include <iostream>

class Wrapper
{
public:
    Wrapper() {
        std::cout << "Wrapper instantiated" << std::endl;
    };

private:

};

class Adaptee
{
public:
    Adaptee() {
        std::cout << "Adaptee instantiated" << std::endl;
    };
private:

};


#endif