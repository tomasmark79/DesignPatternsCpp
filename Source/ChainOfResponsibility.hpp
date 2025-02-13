#ifndef CHAINOFRESPONSIBILITY_H
#define CHAINOFRESPONSIBILITY_H

#include <iostream>

class ChainOfResponsibility {
public:
  virtual void setNext(ChainOfResponsibility* next) = 0;
  virtual void handle(int request) = 0;
};

class ConcreteChainA : public ChainOfResponsibility {
public:
  void setNext(ChainOfResponsibility* next) override { next_ = next; }

  void handle(int request) override {
    if (request < 0) {
      std::cout << "ConcreteChainA handles request " << request << std::endl;
    } else {
      next_->handle(request);
    }
  }

private:
  ChainOfResponsibility* next_;
};

class ConcreteChainB :
    public ChainOfResponsibility

{
public:
  void setNext(ChainOfResponsibility* next) override { next_ = next; }

  void handle(int request) override {
    if (request == 0) {
      std::cout << "ConcreteChainB handles request " << request << std::endl;
    } else {
      next_->handle(request);
    }
  }

private:
  ChainOfResponsibility* next_;
};

class ConcreteChainC : public ChainOfResponsibility {
public:
  void setNext(ChainOfResponsibility* next) override { next_ = next; }

  void handle(int request) override {
    if (request > 0) {
      std::cout << "ConcreteChainC handles request " << request << std::endl;
    } else {
      next_->handle(request);
    }
  }

private:
  ChainOfResponsibility* next_;
};

#endif