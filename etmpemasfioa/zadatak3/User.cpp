// Vas kod ovdje
#include "User.hpp"

User::User() : firstName{""}, lastName{""}, userId{0} {}

User::User(const std::string& f, const std::string& l, int i) :
  firstName{f}, lastName{l}, userId{i} {}

User::User(const User& o) : firstName{o.firstName}, lastName{o.lastName}, userId{o.userId} {}

User::User(User&& o) : firstName{o.firstName}, lastName{o.lastName}, userId{o.userId}  {}

User& User::operator=(const User& o) {
  firstName = o.firstName;
  lastName = o.lastName;
  userId = o.userId;
  return *this;
}

User& User::operator=(User&& o) {
  firstName = o.firstName;
  lastName = o.lastName;
  userId = o.userId;
  return *this;
}

int User::getUserId() const {return userId;}
