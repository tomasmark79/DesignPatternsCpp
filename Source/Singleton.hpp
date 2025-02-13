#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>

class Singleton {
private:
  Singleton() { std::cout << "Singleton instantiated" << std::endl; };
  ~Singleton(){};

public:
  static Singleton& getInstance() {
    static Singleton instance;
    return instance;
  }

  Singleton(Singleton const&) = delete;
  void operator=(Singleton const&) = delete;

  void print() { std::cout << "Singleton printed" << std::endl; }
};

#endif