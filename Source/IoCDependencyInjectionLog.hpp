#ifndef IOCDEPENDENCYINJECTIONLOG_H
#define IOCDEPENDENCYINJECTIONLOG_H

#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <typeinfo>
#include <stdexcept>
#include <functional>

namespace IoCDependencyInjectionLog {

  enum class LifetimeScope { Singleton, Transient };

  class IDatabase {
  public:
    virtual ~IDatabase() = default;
    virtual void connect() = 0;
  };

  class ILogger {
  public:
    virtual ~ILogger() = default;
    virtual void log(const std::string& message) = 0;
  };

  class ILogManager {
  public:
    virtual ~ILogManager() = default;
    virtual void logMessage(const std::string& message) = 0;
  };

  class IoCContainer {
  public:
    ~IoCContainer() { clear(); }

    // Register service without lifetime scope
    template<typename TInterface, typename TImplementation>
    void registerService() {
      static_assert(std::is_base_of<TInterface, TImplementation>::value,
          "TImplementation must inherit from TInterface");
      services[typeid(TInterface).name()] = []() {
        return std::make_shared<TImplementation>();
      };
    }

    // Register service with lifetime scope
    template<typename TInterface, typename TImplementation>
    void registerService(LifetimeScope scope) {
      static_assert(std::is_base_of<TInterface, TImplementation>::value,
          "TImplementation must inherit from TInterface");

      std::cout << "Registering service: " << typeid(TInterface).name()
                << " with implementation: " << typeid(TImplementation).name()
                << " ["
                << (scope == LifetimeScope::Singleton ? "Singleton"
                                                      : "Transient")
                << "]" << std::endl;

      if (scope == LifetimeScope::Singleton) {
        auto instance = std::make_shared<TImplementation>();
        services[typeid(TInterface).name()] = [instance]() { return instance; };
      } else {
        services[typeid(TInterface).name()] = []() {
          return std::make_shared<TImplementation>();
        };
      }
    }

    // Register service with automatic dependency resolution
    /// @tparam TInterface - interface type
    /// @tparam TImplementation - implementation type
    template<typename TInterface, typename TImplementation>
    void registerServiceWithDependencies() {
      static_assert(std::is_base_of<TInterface, TImplementation>::value,
          "TImplementation must inherit from TInterface");
      // Zde je zaregistrována služba TInterface s implementací TImplementation.
      services[typeid(TInterface).name()] = [this]() {
        // Zde je získána instance třídy TImplementation z kontejneru a
        // vrácena jako std::shared_ptr<TInterface>.
        return std::static_pointer_cast<void>(
            createInstance<TImplementation>());
      };
    }

    // Register service with lazy initialization
    template<typename TInterface, typename TImplementation>
    void registerLazyService() {
      services[typeid(TInterface).name()] = [this]() {
        static std::shared_ptr<void> instance;
        if (!instance) {
          instance =
              std::static_pointer_cast<void>(createInstance<TImplementation>());
        }
        return instance;
      };
    }

    // Check if service is registered
    template<typename T>
    bool isRegistered() const {
      return services.find(typeid(T).name()) != services.end();
    }

    void clear() {
      services.clear();
      std::cout << "IoC container cleared" << std::endl;
    }

    /// @tparam T - type of service to resolve
    /// @return shared_ptr<T> - resolved service instance
    template<typename T>
    std::shared_ptr<T> resolve() {
      try {
        // Zde je získána instance třídy T z kontejneru a vrácena jako std::shared_ptr<T>.
        auto it = services.find(typeid(T).name());
        // Pokud instance není nalezena, dojde k vyhození výjimky.
        if (it == services.end()) {
          throw std::runtime_error(
              "Service " + std::string(typeid(T).name()) + " not registered");
        }
        // Zde je získána instance třídy T z kontejneru a vrácena jako std::shared_ptr<T>.
        auto instance = std::static_pointer_cast<T>(it->second());
        // Pokud instance není vytvořena, dojde k vyhození výjimky.
        if (!instance) {
          throw std::runtime_error(
              "Failed to create instance of " + std::string(typeid(T).name()));
        }
        // V opačném případě je instance vrácena.
        return instance;
      } catch (const std::exception& e) {
        std::cerr << "Error resolving service: " << e.what() << std::endl;
        throw;
      }
    }

  private:
    /// @brief  Vytvoří instanci třídy T a vstříkne do ní závislosti, které jsou v kontejneru registrovány.
    /// @tparam T - typ třídy, která má být vytvořena
    /// @return std::shared_ptr<T> - instance třídy T
    template<typename T>
    std::shared_ptr<T> createInstance() {
      // Pokud třída T vyžaduje v konstruktoru závislost IDatabase,
      if constexpr (std::is_constructible_v<T, std::shared_ptr<IDatabase>>) {
        // kontejner nejprve resolvuje (získý instanci) tuto závislost pomocí resolve<IDatabase>().
        auto database = resolve<IDatabase>();
        if (!database) {
          throw std::runtime_error("Failed to resolve IDatabase dependency");
        }
        // Poté vytvoří instanci třídy T a předá jí resolvovanou závislost IDatabase.
        return std::make_shared<T>(database);
      } else if constexpr (std::is_default_constructible_v<T>) {
        // Pokud třída T nevyžaduje žádné závislosti, vytvoří se instance bez parametrů.
        return std::make_shared<T>();
      } else {
        // Pokud třída T vyžaduje závislosti, které nejsou v kontejneru registrovány, dojde k vyhození výjimky.
        throw std::runtime_error(
            "Cannot create instance - no matching constructor");
      }
    }  // Tímto způsobem dochází k automatickému vstřikování závislostí do tříd, které je vyžadují.

    template<typename T>
    void validateDependencies() {
      if constexpr (std::is_constructible_v<T, std::shared_ptr<IDatabase>>) {
        if (!isRegistered<IDatabase>()) {
          throw std::runtime_error("Missing dependency: IDatabase");
        }
      }
    }

    std::unordered_map<std::string, std::function<std::shared_ptr<void>()>>
        services;
  };

  // Service collection for fluent registration
  class ServiceCollection {
  public:
    template<typename TInterface, typename TImplementation>
    ServiceCollection& addSingleton() {
      container.registerService<TInterface, TImplementation>(
          LifetimeScope::Singleton);
      return *this;
    }

    template<typename TInterface, typename TImplementation>
    ServiceCollection& addTransient() {
      container.registerService<TInterface, TImplementation>(
          LifetimeScope::Transient);
      return *this;
    }

    template<typename TInterface, typename TImplementation>
    ServiceCollection& addTransientWithDependencies() {
      container.registerServiceWithDependencies<TInterface, TImplementation>();
      return *this;
    }

  private:
    IoCContainer container;
  };

  // Implementations
  class Database : public IDatabase {
  public:
    void connect() override {
      std::cout << "Connected to database" << std::endl;
    }
  };

  class Logger : public ILogger {
  private:
    std::shared_ptr<IDatabase> db;

  public:
    // Zde je závislost IDatabase vstřikována do třídy Logger přes její konstruktor. Tato závislost je poté použita v metodě log.
    explicit Logger(std::shared_ptr<IDatabase> database) : db(database) {
      if (!database) { throw std::invalid_argument("database cannot be null"); }
    }

    void log(const std::string& message) override {
      std::cout << "Logging message: " << message << std::endl;
      db->connect();  // Simulate saving log to database
    }
  };

  class LogManager : public ILogManager {
  private:
    std::shared_ptr<IDatabase> db;

  public:
    // Zde je závislost IDatabase vstřikována do třídy LogManager přes její konstruktor. Tato závislost je poté použita v metodě logMessage.
    explicit LogManager(std::shared_ptr<IDatabase> database) : db(database) {
      if (!database) { throw std::invalid_argument("database cannot be null"); }
    }

    void logMessage(const std::string& message) override {
      std::cout << "LogManager processing message: " << message << std::endl;
      db->connect();  // Simulate saving log to database
    }
  };

  // RAII scope for IoC container
  class IoCScope {
  private:
    IoCContainer& container;

  public:
    explicit IoCScope(IoCContainer& c) : container(c) {
      // Register services
      container.registerService<IDatabase, Database>(LifetimeScope::Singleton);
      container.registerServiceWithDependencies<ILogger, Logger>();
      container.registerServiceWithDependencies<ILogManager, LogManager>();
    }
    ~IoCScope() { container.clear(); }
  };
}  // namespace IoCDependencyInjectionLog
#endif  // IOCDEPENDENCYINJECTIONLOG_H