#include "Zadatak.hpp"
#include <time.h>
#include <random>
#include <iostream>

Zadatak::Zadatak() : id_{Zadatak::generateId(5)} {}
Zadatak::Zadatak(const Zadatak&) = default;
Zadatak::Zadatak(Zadatak&&) = default;
Zadatak& Zadatak::operator=(const Zadatak&) = default;
Zadatak& Zadatak::operator=(Zadatak&&) = default;
Zadatak::~Zadatak() = default;

const std::string& Zadatak::id() const {return id_;}
const std::string& Zadatak::name() const {return name_;}
std::string& Zadatak::name() {return name_;}
const std::string& Zadatak::description() const {return description_;}
std::string& Zadatak::description() {return description_;}
const unsigned int& Zadatak::priority() const {return priority_;}
unsigned int& Zadatak::priority() {return priority_;}
const unsigned int& Zadatak::status() const {return status_;}
unsigned int& Zadatak::status() {return status_;}
std::string Zadatak::statusString() const {
  if(status_ == 2) return "Started";
  if(status_ == 3) return "Ended";
  return "Waiting";
}

unsigned int& Zadatak::completionId() {return completionNum;}
const unsigned int& Zadatak::completionId() const {return completionNum;}

void Zadatak::edit() {
  std::cout << *this << std::endl;
  std::cout << "What would you like to edit?\n"
    "Name"
    "Description"
    "Priority"
    "Status" << std::endl;
  std::string input;
  std::cin >> input;
  if(input == "Name") {

  } else if(input == "Name") {
    std::cout << "New name: ";
    std::cin.ignore(99999, '\n');
    getline(std::cin, name_);
  } else if(input == "Description") {
    std::cout << "New description: ";
    std::cin.ignore(99999, '\n');
    getline(std::cin, description_);
  } else if(input == "Priority") {
    std::cout << "New priority: ";
    std::cin >> priority_;
  } else if(input == "Status") {
    std::cout << "New status (\"Waiting\"/\"Started\"/\"Ended\"): ";
    std::cin >> input;
    if(input == "Waiting") status_ = 1;
    else if(input == "Started") status_ = 2;
    else if(input == "Ended") status_ = 3;
  }
}

std::string Zadatak::generateId(int len = 5) {
  srand(time(NULL));
  std::string chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
  std::string output = "";
  for(int i = 0; i < len; ++i)
    output.push_back(chars[rand() % chars.length()]);
  return output;
}

std::ostream& operator<<(std::ostream& o, const Zadatak& z) {
  return o << 
    "Id: " << z.id() << '\n' << 
    "Name: " << z.name() << '\n' << 
    "Description: " << z.description() << '\n' <<
    "Priority: " << z.priority() << '\n' << 
    "Status: " << z.statusString() << '\n';
}
