#pragma once

#include <iostream>
#include <memory>
#include <vector>

// Description:
// Object Pool is a creational design pattern that
// uses a set of initialized objects kept ready to use – a "pool" –
// rather than allocating and destroying them on demand.
// A client of the pool will request an object from the pool and
// perform operations on the returned object. When the client has
// finished, it returns the object to the pool rather than destroying it.
// This allows the object to be reused.

// Usage:
// 1. When you need to work with a large number of objects that are
// expensive to instantiate and each object is only needed for a short
// period of time.
// 2. When you have a limited number of resources available.
// 3. When you need to limit the number of instances of a class that can
// exist.
// 4. When you need to reuse the same objects.
// 5. When you need to limit the number of concurrent threads that can
// access a resource.

class ObjectPool
{
public:
  ObjectPool()
  {
    std::cout << "ObjectPool instantiated" << std::endl;
  }
  virtual ~ObjectPool() = default;
  virtual void operation() = 0;

  virtual std::unique_ptr<ObjectPool> acquireObject() = 0;
  virtual void releaseObject(std::unique_ptr<ObjectPool> obj) = 0;
};

class ConcreteObjectPool : public ObjectPool
{
public:
  ConcreteObjectPool()
  {
    std::cout << "ConcreteObjectPool instantiated" << std::endl;
  }
  virtual ~ConcreteObjectPool() = default;

  void operation() override
  {
    std::cout << "ConcreteObjectPool operation" << std::endl;
  }

  std::unique_ptr<ObjectPool> acquireObject() override
  {
    if (!pool.empty())
    {
      auto obj = std::move(pool.back());
      pool.pop_back();
      return obj;
    }
    return std::make_unique<ConcreteObjectPool>();
  }

  void releaseObject(std::unique_ptr<ObjectPool> obj) override
  {
    pool.push_back(std::move(obj));
  }

private:
  std::vector<std::unique_ptr<ObjectPool>> pool;
};