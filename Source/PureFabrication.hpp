#ifndef PUREFABRICATION_H
#define PUREFABRICATION_H

#include <iostream>

// Pure Fabrication Design Pattern

// is a design pattern that promotes the creation of classes that do not
// represent real-world objects, but instead are used to perform specific
// tasks or operations. These classes are known as pure fabrications, and
// are used to encapsulate complex logic or functionality that does not
// naturally fit into a real-world object.

// The pure fabrication design pattern is useful for creating classes that
// are responsible for performing specific tasks, such as data validation,
// error handling, or complex calculations. By encapsulating this logic in
// a separate class, the code becomes more modular and easier to maintain.

class PureFabrication
{
public:
    PureFabrication()
    {
        std::cout << "PureFabrication::PureFabrication()" << std::endl;
    }
};

#endif