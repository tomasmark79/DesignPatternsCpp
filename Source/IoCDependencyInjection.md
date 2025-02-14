# Tutorial: Jak funguje a jak používat C++ soubor s IoC kontejnerem

Tento článek vysvětluje, jak funguje C++ soubor s implementací **Inversion of Control (IoC)** kontejneru pro dependency injection. IoC kontejnery jsou užitečné pro řízení závislostí v aplikacích, což usnadňuje testování a modularitu kódu.

---

## 1. Úvod do Dependency Injection a IoC

**Dependency Injection (DI)** je návrhový vzor, který umožňuje předávat závislosti objektů zvenčí, místo toho, aby si je objekty vytvářely samy. **Inversion of Control (IoC)** je princip, který říká, že řízení toku programu je delegováno na externí framework nebo kontejner.

V tomto kódu je implementován jednoduchý IoC kontejner, který umožňuje registrovat a řešit závislosti mezi třídami.

---

## 2. Struktura kódu

### 2.1 Základní rozhraní (Interfaces)
Kód definuje několik rozhraní, která reprezentují služby (services):

- `IDatabase`: Rozhraní pro práci s databází.
- `ICarRepository`: Rozhraní pro repozitář aut.
- `ICarManager`: Rozhraní pro správu aut.

Každé rozhraní má virtuální destruktor a metody, které musí implementující třídy přepsat.

```cpp
class IDatabase {
public:
  virtual ~IDatabase() = default;
  virtual void connect() = 0;
};

class ICarRepository {
public:
  virtual ~ICarRepository() = default;
  virtual void show() = 0;
};

class ICarManager {
public:
  virtual ~ICarManager() = default;
  virtual void show() = 0;
};
```

### 2.2 IoC kontejner
Hlavní třída `IoCContainer` slouží k registraci a řešení závislostí. Obsahuje metody pro:

- Registraci služeb (`registerService`).
- Registraci služeb s životním cyklem (`registerService` s `LifetimeScope`).
- Registraci služeb s automatickým řešením závislostí (`registerServiceWithDependencies`).
- Registraci služeb s línou inicializací (`registerLazyService`).
- Řešení instancí služeb (`resolve`).

```cpp
class IoCContainer {
public:
  ~IoCContainer() { clear(); }

  template<typename TInterface, typename TImplementation>
  void registerService() { /* ... */ }

  template<typename TInterface, typename TImplementation>
  void registerService(LifetimeScope scope) { /* ... */ }

  template<typename TInterface, typename TImplementation>
  void registerServiceWithDependencies() { /* ... */ }

  template<typename TInterface, typename TImplementation>
  void registerLazyService() { /* ... */ }

  template<typename T>
  bool isRegistered() const { /* ... */ }

  void clear() { /* ... */ }

  template<typename T>
  std::shared_ptr<T> resolve() { /* ... */ }

private:
  template<typename T>
  std::shared_ptr<T> createInstance() { /* ... */ }

  template<typename T>
  void validateDependencies() { /* ... */ }

  std::unordered_map<std::string, std::function<std::shared_ptr<void>()>> services;
};
```

### 2.3 Implementace služeb
Kód obsahuje implementace rozhraní:

- `Database`: Implementuje `IDatabase`.
- `CarRepository`: Implementuje `ICarRepository` a závisí na `IDatabase`.
- `CarManager`: Implementuje `ICarManager` a závisí na `IDatabase`.

```cpp
class Database : public IDatabase {
public:
  void connect() override { std::cout << "Connected to database" << std::endl; }
};

class CarRepository : public ICarRepository {
private:
  std::shared_ptr<IDatabase> db;

public:
  explicit CarRepository(std::shared_ptr<IDatabase> database) : db(database) {}

  void show() override {
    std::cout << "CarRepository initialized" << std::endl;
    db->connect();
  }
};

class CarManager : public ICarManager {
private:
  std::shared_ptr<IDatabase> db;

public:
  explicit CarManager(std::shared_ptr<IDatabase> database) : db(database) {}

  void show() override {
    std::cout << "CarManager initialized" << std::endl;
    db->connect();
  }
};
```

### 2.4 ServiceCollection a IoCScope
- `ServiceCollection`: Umožňuje plynulou registraci služeb.
- `IoCScope`: RAII (Resource Acquisition Is Initialization) obal pro IoC kontejner, který automaticky registruje a uvolňuje služby.

```cpp
class ServiceCollection {
public:
  template<typename TInterface, typename TImplementation>
  ServiceCollection& addSingleton() { /* ... */ }

  template<typename TInterface, typename TImplementation>
  ServiceCollection& addTransient() { /* ... */ }

private:
  IoCContainer container;
};

class IoCScope {
private:
  IoCContainer& container;

public:
  explicit IoCScope(IoCContainer& c) : container(c) {
    container.registerService<IDatabase, Database>(LifetimeScope::Singleton);
    container.registerServiceWithDependencies<ICarRepository, CarRepository>();
    container.registerServiceWithDependencies<ICarManager, CarManager>();
  }
  ~IoCScope() { container.clear(); }
};
```

---

## 3. Jak používat IoC kontejner

### 3.1 Registrace služeb
Služby lze registrovat pomocí `IoCContainer` nebo `ServiceCollection`. Například:

```cpp
IoCContainer container;
container.registerService<IDatabase, Database>(LifetimeScope::Singleton);
container.registerServiceWithDependencies<ICarRepository, CarRepository>();
```

### 3.2 Řešení služeb
Instance služeb lze získat pomocí metody `resolve`:

```cpp
auto database = container.resolve<IDatabase>();
auto carRepository = container.resolve<ICarRepository>();
carRepository->show();
```

### 3.3 Použití ServiceCollection
`ServiceCollection` umožňuje plynulou registraci:

```cpp
ServiceCollection services;
services.addSingleton<IDatabase, Database>()
        .addTransient<ICarRepository, CarRepository>();
```

---

## 4. Životní cykly služeb
- **Singleton**: Jedna instance služby je vytvořena a sdílena v rámci celé aplikace.
- **Transient**: Při každém požadavku je vytvořena nová instance služby.

---

## 5. Příklad použití

```cpp
int main() {
  IoCContainer container;
  {
    IoCScope scope(container); // Automatická registrace služeb

    auto carManager = container.resolve<ICarManager>();
    carManager->show(); // Vytvoří a použije CarManager a Database
  } // Zde se služby automaticky uvolní
  return 0;
}
```

---

## 6. Závěr
Tento kód demonstruje jednoduchý, ale účinný IoC kontejner pro C++. Umožňuje snadnou správu závislostí a podporuje různé životní cykly služeb. Je vhodný pro menší projekty nebo jako výchozí bod pro složitější implementace.

Ve vašem kódu dochází k **vstřikování závislostí (Dependency Injection, DI)** v několika klíčových místech, kde jsou závislosti předávány do tříd prostřednictvím jejich konstruktorů. Konkrétně se to děje v následujících částech kódu:

---

# Jak dochází k samotnému vstřikování závislostí ?

### 1. **Vstřikování závislostí do konstruktorů implementací**

Závislosti jsou vstřikovány do tříd, které je vyžadují, prostřednictvím jejich konstruktorů. Například:

#### Třída `Logger`:
```cpp
class Logger : public ILogger {
private:
    std::shared_ptr<IDatabase> db;

public:
    explicit Logger(std::shared_ptr<IDatabase> database) : db(database) {
        if (!database) { throw std::invalid_argument("database cannot be null"); }
    }

    void log(const std::string& message) override {
        std::cout << "Logging message: " << message << std::endl;
        db->connect();  // Simulate saving log to database
    }
};
```

Zde je závislost `IDatabase` vstřikována do třídy `Logger` přes její konstruktor. Tato závislost je poté použita v metodě `log`.

#### Třída `LogManager`:
```cpp
class LogManager : public ILogManager {
private:
    std::shared_ptr<IDatabase> db;

public:
    explicit LogManager(std::shared_ptr<IDatabase> database) : db(database) {
        if (!database) { throw std::invalid_argument("database cannot be null"); }
    }

    void logMessage(const std::string& message) override {
        std::cout << "LogManager processing message: " << message << std::endl;
        db->connect();  // Simulate saving log to database
    }
};
```

Stejně jako u `Logger`, i zde je závislost `IDatabase` vstřikována přes konstruktor.

---

### 2. **Automatická resolvace závislostí v IoC kontejneru**

K vstřikování závislostí dochází také v metodě `createInstance` v IoC kontejneru. Tato metoda je zodpovědná za vytváření instancí tříd a automatické resolvování jejich závislostí.

#### Metoda `createInstance`:
```cpp
template<typename T>
std::shared_ptr<T> createInstance() {
    if constexpr (std::is_constructible_v<T, std::shared_ptr<IDatabase>>) {
        auto database = resolve<IDatabase>();
        if (!database) {
            throw std::runtime_error("Failed to resolve IDatabase dependency");
        }
        return std::make_shared<T>(database);
    } else if constexpr (std::is_default_constructible_v<T>) {
        return std::make_shared<T>();
    } else {
        throw std::runtime_error(
            "Cannot create instance - no matching constructor");
    }
}
```

Zde se provádí následující:
1. Pokud třída `T` vyžaduje v konstruktoru závislost `IDatabase`, kontejner nejprve resolvuje tuto závislost pomocí `resolve<IDatabase>()`.
2. Poté vytvoří instanci třídy `T` a předá jí resolvovanou závislost `IDatabase`.

Tímto způsobem dochází k **automatickému vstřikování závislostí** do tříd, které je vyžadují.

---

### 3. **Příklad vstřikování v praxi**

Když je například volána metoda `resolve<ILogger>()`, IoC kontejner provede následující kroky:
1. Zjistí, že `Logger` vyžaduje závislost `IDatabase`.
2. Resolvuje závislost `IDatabase` voláním `resolve<IDatabase>()`.
3. Vytvoří instanci `Logger` a předá jí resolvovanou instanci `IDatabase`.

```cpp
auto logger = container.resolve<IoCDependencyInjectionLog::ILogger>();
```

V tomto okamžiku je závislost `IDatabase` vstřikována do `Logger` přes jeho konstruktor.

---

### 4. **Registrace služeb s automatickou resolvací závislostí**

Kontejner také umožňuje registrovat služby s automatickou resolvací závislostí pomocí metody `registerServiceWithDependencies`. Tato metoda zajistí, že při vytváření instance budou všechny závislosti automaticky resolvovány.

```cpp
template<typename TInterface, typename TImplementation>
void registerServiceWithDependencies() {
    static_assert(std::is_base_of<TInterface, TImplementation>::value,
        "TImplementation must inherit from TInterface");
    services[typeid(TInterface).name()] = [this]() {
        return std::static_pointer_cast<void>(
            createInstance<TImplementation>());
    };
}
```

Při registraci služby `ILogger` s implementací `Logger`:
```cpp
container.registerServiceWithDependencies<ILogger, Logger>();
```

Kontejner automaticky resolvuje závislosti `Logger` (v tomto případě `IDatabase`) a vstřikuje je při vytváření instance.

---

### 5. **Shrnutí**

K vstřikování závislostí dochází v těchto místech:
1. **Při vytváření instancí tříd** (např. `Logger` a `LogManager`), kde jsou závislosti předávány přes konstruktor.
2. **V metodě `createInstance`** v IoC kontejneru, kde jsou závislosti automaticky resolvovány a vstřikovány.
3. **Při registraci služeb s automatickou resolvací závislostí** pomocí `registerServiceWithDependencies`.

Tento mechanismus zajišťuje, že třídy nejsou zodpovědné za vytváření svých závislostí, ale tyto závislosti jsou jim poskytovány (vstřikovány) externě, což je podstatou Dependency Injection.