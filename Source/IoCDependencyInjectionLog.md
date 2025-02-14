### Jak funguje Inversion of Control (IoC) a Dependency Injection (DI) v ukázkovém kódu

Inversion of Control (IoC) a Dependency Injection (DI) jsou dva klíčové koncepty v moderním softwarovém inženýrství, které pomáhají vytvářet modulární, testovatelný a snadno udržovatelný kód. V tomto článku si podrobně vysvětlíme, jak tyto koncepty fungují v ukázkovém kódu, který implementuje jednoduchý IoC kontejner s podporou dependency injection.

#### 1. **Základní koncepty**

- **Inversion of Control (IoC):** Tento princip znamená, že řízení toku programu je obráceno. Místo toho, aby třídy samy vytvářely instance svých závislostí, je tento úkol delegován na externí komponentu (IoC kontejner).

- **Dependency Injection (DI):** Tento vzor je specifickou implementací IoC, kde závislosti jsou "vstřikovány" do tříd, obvykle přes konstruktor, metodu nebo vlastnost.

#### 2. **Struktura kódu**

Kód je rozdělen do několika hlavních částí:

- **Rozhraní (Interfaces):** Definují kontrakty pro služby, které budou poskytovány.
- **Implementace (Implementations):** Třídy, které implementují daná rozhraní.
- **IoC kontejner (IoCContainer):** Třída, která spravuje registraci a resolvování služeb.
- **ServiceCollection:** Pomocná třída pro fluentní registraci služeb.
- **IoCScope:** RAII (Resource Acquisition Is Initialization) scope pro správu životního cyklu kontejneru.

#### 3. **Registrace služeb**

Služby jsou registrovány v IoC kontejneru pomocí metod `registerService`, `registerServiceWithDependencies` a `registerLazyService`. Každá z těchto metod umožňuje registrovat služby s různými životními cykly (Singleton, Transient) a různými způsoby inicializace.

```cpp
template<typename TInterface, typename TImplementation>
void registerService(LifetimeScope scope) {
    static_assert(std::is_base_of<TInterface, TImplementation>::value,
        "TImplementation must inherit from TInterface");

    if (scope == LifetimeScope::Singleton) {
        auto instance = std::make_shared<TImplementation>();
        services[typeid(TInterface).name()] = [instance]() { return instance; };
    } else {
        services[typeid(TInterface).name()] = []() {
            return std::make_shared<TImplementation>();
        };
    }
}
```

- **Singleton:** Vytvoří jednu instanci služby, která je sdílena napříč celou aplikací.
- **Transient:** Vytvoří novou instanci služby pokaždé, když je požadována.

#### 4. **Resolvování služeb**

Když je potřeba získat instanci služby, použije se metoda `resolve`. Tato metoda vyhledá registrovanou službu a vrátí její instanci.

```cpp
template<typename T>
std::shared_ptr<T> resolve() {
    try {
        auto it = services.find(typeid(T).name());
        if (it == services.end()) {
            throw std::runtime_error(
                "Service " + std::string(typeid(T).name()) + " not registered");
        }
        auto instance = std::static_pointer_cast<T>(it->second());
        if (!instance) {
            throw std::runtime_error(
                "Failed to create instance of " + std::string(typeid(T).name()));
        }
        return instance;
    } catch (const std::exception& e) {
        std::cerr << "Error resolving service: " << e.what() << std::endl;
        throw;
    }
}
```

#### 5. **Automatická resolvace závislostí**

Kontejner také podporuje automatickou resolvaci závislostí. Pokud třída vyžaduje závislosti v konstruktoru, kontejner se pokusí tyto závislosti automaticky resolvovat.

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

#### 6. **Příklad použití**

Následující kód ukazuje, jak by se dal IoC kontejner použít v praxi:

```cpp
int main() {
    IoCDependencyInjectionLog::IoCContainer container;
    IoCDependencyInjectionLog::IoCScope scope(container);

    auto logger = container.resolve<IoCDependencyInjectionLog::ILogger>();
    logger->log("Test log message");

    auto logManager = container.resolve<IoCDependencyInjectionLog::ILogManager>();
    logManager->logMessage("Test log message from LogManager");

    return 0;
}
```

#### 7. **Závěr**

Tento jednoduchý IoC kontejner demonstruje základní principy Inversion of Control a Dependency Injection. Umožňuje registrovat služby s různými životními cykly, resolvovat závislosti a automaticky vytvářet instance služeb. Tento přístup výrazně zlepšuje modularitu a testovatelnost kódu, což je klíčové pro vývoj velkých a komplexních aplikací.