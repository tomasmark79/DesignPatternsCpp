#ifndef IOCDEPENDENCYINJECTION_H
#define IOCDEPENDENCYINJECTION_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <functional>

enum class LifetimeScope
{
  Singleton,
  Transient
};

class IDatabase
{
public:
  virtual ~IDatabase() = default;
  virtual void connect() = 0;
};

class ICarRepository
{
public:
  virtual ~ICarRepository() = default;
  virtual void show() = 0;
};

class ICarManager
{
public:
  virtual ~ICarManager() = default;
  virtual void show() = 0;
};

class IoCContainer
{
public:
  ~IoCContainer()
  {
    clear();
  }

  // Register service without lifetime scope
  template <typename TInterface, typename TImplementation>
  void registerService()
  {
    static_assert(
      std::is_base_of<TInterface, TImplementation>::value,
      "TImplementation must inherit from TInterface");
    services[typeid(TInterface).name()] = []() {
      return std::make_shared<TImplementation>();
    };
  }

  // Register service with lifetime scope
  template <typename TInterface, typename TImplementation>
  void registerService(LifetimeScope scope)
  {
    static_assert(
      std::is_base_of<TInterface, TImplementation>::value,
      "TImplementation must inherit from TInterface");

    std::cout << "Registering service: " << typeid(TInterface).name()
              << " with implementation: " << typeid(TImplementation).name()
              << " ["
              << (scope == LifetimeScope::Singleton ? "Singleton" : "Transient")
              << "]" << std::endl;

    if (scope == LifetimeScope::Singleton)
    {
      auto instance = std::make_shared<TImplementation>();
      services[typeid(TInterface).name()] = [instance]() { return instance; };
    }
    else
    {
      services[typeid(TInterface).name()] = []() {
        return std::make_shared<TImplementation>();
      };
    }
  }

  // Register service with automatic dependency resolution
  template <typename TInterface, typename TImplementation>
  void registerServiceWithDependencies()
  {
    static_assert(
      std::is_base_of<TInterface, TImplementation>::value,
      "TImplementation must inherit from TInterface");
    services[typeid(TInterface).name()] = [this]() {
      return std::static_pointer_cast<void>(createInstance<TImplementation>());
    };
  }

  // Register service with lazy initialization
  template <typename TInterface, typename TImplementation>
  void registerLazyService()
  {
    services[typeid(TInterface).name()] = [this]() {
      static std::shared_ptr<void> instance;
      if (!instance)
      {
        instance =
          std::static_pointer_cast<void>(createInstance<TImplementation>());
      }
      return instance;
    };
  }

  // Check if service is registered
  template <typename T>
  bool isRegistered() const
  {
    return services.find(typeid(T).name()) != services.end();
  }

  void clear()
  {
    services.clear();
    std::cout << "IoC container cleared" << std::endl;
  }

  // Resolve instance of service
  template <typename T>
  std::shared_ptr<T> resolve()
  {
    try
    {
      auto it = services.find(typeid(T).name());
      if (it == services.end())
      {
        throw std::runtime_error(
          "Service " + std::string(typeid(T).name()) + " not registered");
      }
      auto instance = std::static_pointer_cast<T>(it->second());
      if (!instance)
      {
        throw std::runtime_error(
          "Failed to create instance of " + std::string(typeid(T).name()));
      }
      return instance;
    }
    catch (const std::exception& e)
    {
      std::cerr << "Error resolving service: " << e.what() << std::endl;
      throw;
    }
  }

private:
  template <typename T>
  std::shared_ptr<T> createInstance()
  {
    if constexpr (std::is_constructible_v<T, std::shared_ptr<IDatabase>>)
    {
      auto database = resolve<IDatabase>();
      if (!database)
      {
        throw std::runtime_error("Failed to resolve IDatabase dependency");
      }
      return std::make_shared<T>(database);
    }
    else if constexpr (std::is_default_constructible_v<T>)
    {
      return std::make_shared<T>();
    }
    else
    {
      throw std::runtime_error(
        "Cannot create instance - no matching constructor");
    }
  }

  std::unordered_map<std::string, std::function<std::shared_ptr<void>()>>
    services;
};

// Implementations
class Database : public IDatabase
{
public:
  void connect() override
  {
    std::cout << "Connected to database" << std::endl;
  }
};

class CarRepository : public ICarRepository
{
private:
  std::shared_ptr<IDatabase> db;

public:
  explicit CarRepository(std::shared_ptr<IDatabase> database) : db(database)
  {
    if (!database)
    {
      throw std::invalid_argument("database cannot be null");
    }
  }

  void show() override
  {
    std::cout << "CarRepository initialized" << std::endl;
    db->connect();
  }
};

class CarManager : public ICarManager
{
private:
  std::shared_ptr<IDatabase> db;

public:
  explicit CarManager(std::shared_ptr<IDatabase> database) : db(database)
  {
    if (!database)
    {
      throw std::invalid_argument("database cannot be null");
    }
  }

  void show() override
  {
    std::cout << "CarManager initialized" << std::endl;
    db->connect();
  }
};

#endif // IOCDEPENDENCYINJECTION_H