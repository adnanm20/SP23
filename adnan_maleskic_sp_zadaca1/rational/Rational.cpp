#include "Rational.hpp"
#include <algorithm>
#include <iostream>
#include <cmath>
#include <numeric>
#include <sstream>
#include <string.h>


Rational::Rational() : numerator_{0}, denominator_{1} {}
// denominator should not be 0!
Rational::Rational(int numerator, int denominator) : numerator_{numerator} {
  if(denominator == 0) throw std::invalid_argument{"Denominator cannot be 0"};

  denominator_ = denominator;
  normalize();
}
// Split const char* by / delimiter
Rational::Rational(const char* rational) {
  int i = 0;
  bool m = true;
  numerator_ = 0;
  denominator_ = -1;
  while(rational[i] != 0)
  {
    if(rational[i] >= '0' && rational[i] <= '9')
    {
      if(m)
      {
        numerator_ *= 10;
        numerator_ += rational[i] - '0';
      }
      else
      {
        if(denominator_ == -1) denominator_ = 0;
        denominator_ *= 10;
        denominator_ += rational[i] - '0';
      }
    }
    else if (rational[i] == '/')
    {
      m = false;
    } 
    else
      throw std::invalid_argument{""};
    ++i;
  }
  if(denominator_ == 0) 
    throw std::invalid_argument{""};
  if(denominator_ == -1) denominator_ = 1;
  normalize();
}
Rational::Rational(const std::string& rational) {
  bool m = true;
  numerator_ = 0;
  denominator_ = -1;
  for(int i = 0; i < rational.size(); ++i)
  {
    if(rational[i] >= '0' && rational[i] <= '9')
    {
      if(m)
      {
        numerator_ *= 10;
        numerator_ += rational[i] - '0';
      }
      else
      {
        if(denominator_ == -1) denominator_ = 0;
        denominator_ *= 10;
        denominator_ += rational[i] - '0';
      }
    }
    else if (rational[i] == '/')
    {
      m = false;
    } 
    else
      throw std::invalid_argument{""};
  }
  if(denominator_ == 0) 
    throw std::invalid_argument{""};
  if(denominator_ == -1) denominator_ = 1;
  normalize();
}
// copy constructor
Rational::Rational(const Rational& rational) : numerator_{rational.numerator_}, 
denominator_{rational.denominator_} {
  normalize();
}
// Move constructor
Rational::Rational(Rational&& rational) : numerator_{rational.numerator_}, 
denominator_{rational.denominator_} {}
// Copy op=
Rational& Rational::operator=(const Rational& rational) {
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
  return *this;
}
// Move op=
Rational& Rational::operator=(Rational&& rational) {
  numerator_ = rational.numerator_;
  denominator_ = rational.denominator_;
  return *this;
}
// Return optimal rational number
// 2/3 + 4/3, operator should return 3/1.
// std::cout should print it as 3, not 3/1!
Rational Rational::operator+(const Rational& rational) const {
  auto r = Rational{numerator_ * rational.denominator_ + rational.numerator_ * denominator_,
    denominator_ * rational.denominator_};
  r.normalize();
  return r;
}
Rational Rational::operator+(int numerator) const {
  auto r = Rational{numerator_ + numerator*denominator_, denominator_};
  r.normalize();
  return r;
}
Rational Rational::operator-(const Rational& rational) const {
  auto r = Rational{numerator_ * rational.denominator_ - rational.numerator_ * denominator_,
    denominator_ * rational.denominator_};
  r.normalize();
  return r;
}
Rational Rational::operator-(int numerator) const {
  auto r = Rational{numerator_ - numerator*denominator_, denominator_};
  r.normalize();
  return r;
}
// Rational multiplication
Rational Rational::operator*(const Rational& rational) const {
  auto r = Rational{numerator_ * rational.numerator_, denominator_ * rational.denominator_};
  r.normalize();
  return r;
}
Rational Rational::operator*(int numerator) const {
  auto r = Rational{numerator_ * numerator, denominator_};
  r.normalize();
  return r;
}
// Rational division
Rational Rational::operator/(const Rational& rational) const {
  auto r = Rational{numerator_ * rational.denominator_, denominator_ * rational.numerator_};
  r.normalize();
  return r;
}
Rational Rational::operator/(int numerator) const {
  auto r = Rational{numerator_, denominator_ * numerator};
  r.normalize();
  return r;
}
// Pow operator: (4/3) ^ 2 = (16/9);
Rational Rational::operator^(int n) const {
  auto r = Rational{(int)pow(numerator_, n), (int)pow(denominator_, n)};
  r.normalize();
  return r;
}
// Prefix operator++, increase rational number by 1
Rational& Rational::operator++() {
  numerator_ += denominator_;
  normalize();
  return *this;
}
// Postfix operator++, increase rational number by 1
Rational Rational::operator++(int) {
  auto r = *this;
  numerator_ += denominator_;
  normalize();
  return r;
}
// Prefix operator--, decrease rational number by 1
Rational& Rational::operator--() {
  numerator_ -= denominator_;
  normalize();
  return *this;
}
// Postfix operator--, decrease rational number by 1
Rational Rational::operator--(int) {
  auto r = *this;
  numerator_ -= denominator_;
  normalize();
  return r;
}
bool Rational::operator==(const Rational& rational) const {
  return numerator_ == rational.numerator_ && denominator_ == rational.denominator_;
}
bool Rational::operator==(const char* rational) const {
  return *this == Rational{rational};
}
bool Rational::operator!=(const Rational& rational) const {
  return !(*this==rational);
}
bool Rational::operator!=(const char* rational) const {
  return !(*this == rational);
}
// Get numerator
const int Rational::numerator() const {
  return numerator_;
}
// Get denominator
const int Rational::denominator() const {
  return denominator_;
}

void Rational::normalize() {
  int x = std::__gcd(numerator_, denominator_);
  numerator_ /= x;
  denominator_ /= x;
}

Rational::~Rational() = default;
// Example:
// 5/1 should be printed as 5!
// // 10/5 should be printed as 2
// // 12/8 should be printed as 3/2
std::ostream& operator<<(std::ostream& os, const Rational& rational) {
  if(rational.denominator() != 1)
    os << rational.numerator() << '/' << rational.denominator();
  else
    os << rational.numerator();
  return os;
}
