#ifndef PROXY_H
#define PROXY_H

#include <iostream>
#include <memory>

// The Proxy class controls access to the real subject and logs access.
// The Proxy can be used for caching results, restricting access, logging, etc.

class RealSubject {
public:
    void Request() const {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};

// Proxy
class Proxy {
private:
    std::shared_ptr<RealSubject> real_subject_;

public:
    Proxy(std::shared_ptr<RealSubject> real_subject) : real_subject_(real_subject) {}

    void Request() const {
        if (this->CheckAccess()) {
            this->real_subject_->Request(); // Forward request to the real subject.
            this->LogAccess();
        }
    }

private:
    bool CheckAccess() const {
        std::cout << "Proxy: Checking access prior to firing a real request." << std::endl;
        return true;
    }

    void LogAccess() const {
        std::cout << "Proxy: Logging the time of request." << std::endl;
    }
};

#endif