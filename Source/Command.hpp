#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>

class Command
{
public:
  virtual void execute() = 0;
};

class ConcreteCommand : public Command
{
public:
  void execute() override
  {
    std::cout << "ConcreteCommand executed" << std::endl;
  }
};

class Receiver
{
public:
  void action()
  {
    std::cout << "Receiver action" << std::endl;
  }
};

class Invoker
{
public:
  void setCommand(Command* command)
  {
    this->command = command;
  }

  void executeCommand()
  {
    command->execute();
  }

private:
  Command* command;
};

#endif