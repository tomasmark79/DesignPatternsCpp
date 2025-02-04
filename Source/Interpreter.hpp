#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>

// interpreter arithmetic expression

class InterpreterContext
{
public:
  InterpreterContext(const std::string& input) : input_(input), output_(0) {}

  std::string getInput() const
  {
    return input_;
  }

  void setInput(const std::string& input)
  {
    input_ = input;
  }

  int output() const
  {
    return output_;
  }

  void setOutput(int output)
  {
    output_ = output;
  }

private:
  std::string input_;
  int output_;
};

class AbstractExpression
{
public:
  virtual ~AbstractExpression() = default;
  virtual void interpret(InterpreterContext& context) = 0;
};

class TerminalExpression : public AbstractExpression
{
public:
  void interpret(InterpreterContext& context) override
  {
    std::string input = context.getInput();
    int output = context.output();
    if (input.find("add") != std::string::npos)
    {
      output += 1;
    }
    else if (input.find("sub") != std::string::npos)
    {
      output -= 1;
    }
    else if (input.find("mul") != std::string::npos)
    {
      output *= 2;
    }
    else if (input.find("div") != std::string::npos)
    {
      output /= 2;
    }
    context.setOutput(output);
  }
};

class NonTerminalExpression : public AbstractExpression
{
public:
  void interpret(InterpreterContext& context) override
  {
    std::string input = context.getInput();
    int output = context.output();
    if (input.find("add") != std::string::npos)
    {
      output += 1;
    }
    if (input.find("sub") != std::string::npos)
    {
      output -= 1;
    }
    if (input.find("mul") != std::string::npos)
    {
      output *= 2;
    }
    if (input.find("div") != std::string::npos)
    {
      output /= 2;
    }
    context.setOutput(output);
  }
};

#endif