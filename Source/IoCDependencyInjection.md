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