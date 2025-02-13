#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

class Iterator {
public:
  virtual void first() = 0;
  virtual void next() = 0;
  virtual bool isDone() const = 0;
  virtual int currentItem() const = 0;
};

class ConcreteIterator : public Iterator {
public:
  ConcreteIterator(int* array, int size) :
      array_(array), size_(size), current_(0) { }

  void first() override { current_ = 0; }

  void next() override { ++current_; }

  bool isDone() const override { return current_ >= size_; }

  int currentItem() const override { return array_[current_]; }

private:
  int* array_;
  int size_;
  int current_;
};

class Aggregate {
public:
  virtual Iterator* createIterator() = 0;
};

class ConcreteAggregate : public Aggregate {
public:
  ConcreteAggregate(int* array, int size) : array_(array), size_(size) { }

  Iterator* createIterator() override {
    return new ConcreteIterator(array_, size_);
  }

private:
  int* array_;
  int size_;
};

#endif