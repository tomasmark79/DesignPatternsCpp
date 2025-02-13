#include "DesignPatternsCppLib/DesignPatternsCppLib.hpp"

// #include <EmojiTools/EmojiTools.hpp> // yet dissabled
#include <iostream>
#include <memory>
#include <designpatternscpplib/version.h>

#include <IoCDependencyInjection.hpp>

#include <ImmutableObjects.hpp>
#include <ObjectPool.hpp>
#include <Servant.hpp>
#include <PureFabrication.hpp>
#include <ProtectedVariations.hpp>
#include <Polymorphism.hpp>
#include <LowCoupling.hpp>
#include <InformationExpert.hpp>
#include <Indirection.hpp>
#include <HighCohesion.hpp>
#include <Creator.hpp>
#include <Controller.hpp>

#include <Command.hpp>
#include <ChainOfResponsibility.hpp>
#include <Iterator.hpp>
#include <Mediator.hpp>
#include <Interpreter.hpp>
#include <Memento.hpp>
#include <State.hpp>
#include <TemplateMethod.hpp>
#include <Strategy.hpp>
#include <Observer.hpp>
#include <Bridge.hpp>
#include <Composite.hpp>
#include <Flyweight.hpp>
#include <Decorator.hpp>
#include <Proxy.hpp>
#include <Facade.hpp>
#include <Wrapper.hpp>
#include <Builder.hpp>
#include <Prototype.hpp>
#include <Singleton.hpp>
#include <FactoryMethod.hpp>

DesignPatternsCppLib::DesignPatternsCppLib()
{
  std::cout << "--- DesignPatternsCppLib v." << DESIGNPATTERNSCPPLIB_VERSION
            << " instantiated ---" << std::endl;

  // Dependency Injection
  IoCContainer container;
  {
    IoCScope scope(container);
    auto carManager = container.resolve<ICarManager>();
    carManager->show();
  } // Automatically clears the container

  // Immutable Objects
  std::unique_ptr<ImmutableObjects> immutableObjects =
    std::make_unique<ConcreteImmutableObjects>("name", 1);
  immutableObjects->operation();
  std::cout << "ImmutableObjects name: " << immutableObjects->getName()
            << " value: " << immutableObjects->getValue() << std::endl;

  // Object Pool
  std::unique_ptr<ObjectPool> objectPool =
    std::make_unique<ConcreteObjectPool>();
  objectPool->operation();
  std::unique_ptr<ObjectPool> objectPool2 = objectPool->acquireObject();
  objectPool2->operation();
  objectPool->releaseObject(std::move(objectPool2));

  // Servant
  Servant servant;
  Client client(1);
  Client client2(2);
  client.accept(servant);
  client2.accept(servant);
  std::cout << "Servant output: " << client.getValue() << std::endl;
  std::cout << "Servant output: " << client2.getValue() << std::endl;

  // Pure Fabrication
  PureFabrication pureFabrication;

  // Protected Variations
  ProtectedVariations protectedVariations;

  // Polymorphism
  Animal* animal = new Dog();
  animal->sound();
  animal = new Cat();
  animal->sound();

  // Low Coupling
  LowCoupling lowCoupling;

  // Information Expert
  InformationExpert informationExpert;

  // Indirection
  Indirection indirection;

  // High Cohesion
  HighCohesion highCohesion;

  // Creator
  Creator* creator = new Creator();
  creator->createProduct();
  delete creator;

  // Controller
  std::string model = "model";
  std::string view = "view";
  Controller* controller = new Controller(model, view);
  controller->handleInput();
  controller->updateView();
  delete controller;

  // Command
  ConcreteCommand concreteCommand;
  Receiver receiver;
  concreteCommand.setReceiver(&receiver);
  concreteCommand.execute();
  Invoker invoker;
  invoker.setCommand(&concreteCommand);
  invoker.executeCommand();

  // Chain of Responsibility
  ConcreteChainA concreteChainA;
  ConcreteChainB concreteChainB;
  ConcreteChainC concreteChainC;
  concreteChainA.setNext(&concreteChainB);
  concreteChainB.setNext(&concreteChainC);
  concreteChainA.handle(-1);
  concreteChainA.handle(0);
  concreteChainA.handle(1);

  // Iterator / Enumerator
  int array[] = {1, 2, 3, 4, 5};
  ConcreteIterator concreteIterator(array, sizeof(array) / sizeof(array[0]));
  std::cout << "Iterator output: ";
  for (concreteIterator.first(); !concreteIterator.isDone();
       concreteIterator.next())
  {
    std::cout << concreteIterator.currentItem() << " ";
  }
  std::cout << std::endl;

  // Mediator
  ConcreteMediator concreteMediator;
  ConcreteColleagueA concreteColleagueA(&concreteMediator);
  ConcreteColleagueB concreteColleagueB(&concreteMediator);
  concreteColleagueA.notify(1);
  concreteColleagueB.notify(2);

  // Interpreter terminal expression
  InterpreterContext interpreterContext("add");
  AbstractExpression* abstractExpression = new TerminalExpression();
  abstractExpression->interpret(interpreterContext);
  std::cout << "Interpreter output: add: " << interpreterContext.output()
            << std::endl;
  delete abstractExpression;
  // Interpreter non-terminal expression
  interpreterContext.setInput("add sub mul");
  abstractExpression = new NonTerminalExpression();
  abstractExpression->interpret(interpreterContext);
  std::cout << "Interpreter output: add sub mul: "
            << interpreterContext.output() << std::endl;
  delete abstractExpression;

  // Memento
  Originator originator;
  Caretaker caretaker(&originator);
  originator.setState(1);
  caretaker.saveState();
  originator.setState(2);
  std::cout << "State: " << originator.getState() << std::endl;
  caretaker.restoreState();
  std::cout << "Restored State: " << originator.getState() << std::endl;

  // State
  ContextState* contextState = new ContextState(new ConcreteStateA());
  contextState->request();
  contextState->setState(new ConcreteStateB());
  contextState->request();
  delete contextState;

  // Template Method
  ConcreteTemplateMethodA concreteTemplateMethodA;
  concreteTemplateMethodA.templateMethod();
  ConcreteTemplateMethodB concreteTemplateMethodB;
  concreteTemplateMethodB.templateMethod();

  // Strategy
  Context* context = new Context(new ConcreteStrategyA());
  context->contextInterface();
  delete context;
  context = new Context(new ConcreteStrategyB());
  context->contextInterface();
  delete context;

  // Observer
  ConcreteSubject* concreteSubject = new ConcreteSubject();
  Observer* observerA = new ConcreteObserverA();
  Observer* observerB = new ConcreteObserverB();
  concreteSubject->attach(observerA);
  concreteSubject->attach(observerB);
  concreteSubject->notify();
  concreteSubject->detach(observerA);
  concreteSubject->notify();
  delete concreteSubject;
  delete observerA;
  delete observerB;

  // Bridge
  Implementor* implementorA = new ConcreteImplementorA();
  Implementor* implementorB = new ConcreteImplementorB();
  Bridge* bridgeA = new RefinedAbstraction(implementorA);
  Bridge* bridgeB = new RefinedAbstraction(implementorB);
  bridgeA->operation();
  bridgeB->operation();
  delete bridgeA;
  delete bridgeB;
  // No need to delete implementorA and implementorB as they are deleted by
  // Bridge's destructor

  // Composite
  ComponentComposite* root = new Composite("root");
  ComponentComposite* branch1 = new Composite("branch1");
  ComponentComposite* branch2 = new Composite("branch2");
  ComponentComposite* leaf1 = new Leaf("leaf1");
  ComponentComposite* leaf2 = new Leaf("leaf2");
  ComponentComposite* leaf3 = new Leaf("leaf3");
  root->add(branch1);
  root->add(branch2);
  branch1->add(leaf1);
  branch1->add(leaf2);
  branch2->add(leaf3);
  root->operation();
  delete root;
  delete branch1;
  delete branch2;
  delete leaf1;
  delete leaf2;
  delete leaf3;

  // Flyweight
  FlyweightFactory* flyweightFactory = new FlyweightFactory();
  std::shared_ptr<Flyweight> flyweight1 = flyweightFactory->getFlyweight("A");
  std::shared_ptr<Flyweight> flyweight2 = flyweightFactory->getFlyweight("B");
  std::shared_ptr<Flyweight> flyweight3 = flyweightFactory->getFlyweight("A");
  flyweight1->operation();
  flyweight2->operation();
  flyweight3->operation();
  delete flyweightFactory;

  // Decorator
  std::shared_ptr<Component> component = std::make_shared<ConcreteComponent>();
  std::shared_ptr<Component> decoratorA =
    std::make_shared<ConcreteDecoratorA>(component);
  std::shared_ptr<Component> decoratorB =
    std::make_shared<ConcreteDecoratorB>(decoratorA);
  decoratorB->Operation();

  // Proxy
  std::shared_ptr<RealSubject> real_subject = std::make_shared<RealSubject>();
  Proxy proxy(real_subject);
  proxy.Request();

  // Facade
  Facade* facade = new Facade();
  facade->operation();
  delete facade;

  // Wrapper / Adapter
  Wrapper* wrapper = new Wrapper();
  Adaptee* adaptee = new Adaptee();
  delete adaptee;
  delete wrapper;

  // Builder
  ConcreteBuilder* concreteBuilder = new ConcreteBuilder();
  Director* director = new Director();
  director->setBuilder(concreteBuilder);
  director->construct();
  Product product = concreteBuilder->getProduct();
  product.show();
  delete director;
  delete concreteBuilder;

  // Prototype/Clone
  Prototype* prototype = new ConcretePrototype1();
  std::unique_ptr<Prototype> clone = prototype->clone();
  prototype->print();
  clone->print();
  delete prototype;

  // Singleton - anti-pattern
  Singleton& singleton = Singleton::getInstance();
  singleton.print();

  // Factory Method
  ComputerFactory* computerFactory = new ComputerFactory();
  Computer* computer = computerFactory->createComputer("HP", "FireFly 14");
  std::cout << "Computer: " << computer->computer
            << " Model: " << computer->model << std::endl;
  delete computerFactory;
  delete computer;
}

DesignPatternsCppLib::~DesignPatternsCppLib()
{
  std::cout << "--- DesignPatternsCppLib uninstantiated ---" << std::endl;
}
