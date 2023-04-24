// Vas kod ovdje
#pragma once
#include "Book.hpp"
#include <string>

class User {
  private:
    std::string firstName;
    std::string lastName;
    int userId;
  public:
    User();
    User(const std::string&, const std::string&, int);
    User(const User&);
    User(User&&);
    User& operator=(const User&);
    User& operator=(User&&);
    int getUserId() const;
};
