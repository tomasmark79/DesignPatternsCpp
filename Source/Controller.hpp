#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>

// Controller Design Pattern

// Usage:
// The Controller design pattern is a design pattern that is used to separate
// the presentation layer from the business logic layer. The Controller class is
// responsible for handling the user input and updating the model accordingly.
// It is also responsible for updating the view based on the changes in the
// model. The Controller class is typically used in conjunction with the
// Model-View-Controller (MVC) design pattern.

class Controller
{
public:
  Controller(std::string& model, std::string& view) :
    m_model(model),
    m_view(view)
  {
    // Initialization code if needed
    std::cout << "Controller instantiated" << std::endl;
  }

  ~Controller()
  {
    // Cleanup code if needed
    std::cout << "Controller uninstantiated" << std::endl;
  }

  void handleInput()
  {
    // Handle user input and update model
    m_model = "updated model";
    std::cout << "Input handled" << std::endl;
  }

  void updateView()
  {
    // Update the view based on the model
    m_view = m_model;
    std::cout << "View updated" << std::endl;
  }

private:
  std::string& m_model;
  std::string& m_view;
};

#endif // CONTROLLER_H