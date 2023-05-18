#pragma once

#include <iostream>
#include <string>

class Zadatak {
  public:
    Zadatak();
    Zadatak(const Zadatak&);
    Zadatak(Zadatak&&);
    Zadatak& operator=(const Zadatak&);
    Zadatak& operator=(Zadatak&&);
    ~Zadatak();

    const std::string& id() const;
    const std::string& name() const;
    std::string& name();
    const std::string& description() const;
    std::string& description();
    const unsigned int& priority() const;
    unsigned int& priority();
    const unsigned int& status() const;
    unsigned int& status();
    std::string statusString() const;
    unsigned int& completionId();
    const unsigned int& completionId() const;

    void edit();
  private:
    std::string generateId(int);
    std::string id_;
    std::string name_;
    std::string description_;
    unsigned int priority_;
    unsigned int status_;
    unsigned int completionNum = 0;
};

std::ostream& operator<<(std::ostream& o, const Zadatak& z);
