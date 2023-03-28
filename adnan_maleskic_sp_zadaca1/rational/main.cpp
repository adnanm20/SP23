#include "Rational.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

  std::string s;
  while(std::cin >> s)
  {
    try {
      Rational a{s};
      std::cout << a << std::endl;

    }
    catch (std::exception e)
    {
      std::cout << e.what() << " " << s << std::endl;
    }
  }

  Rational r1{};
  std::cout << "r1 " << r1 << std::endl;

  Rational r2(3, 3);
  std::cout << "r2 " << r2 << std::endl;

  Rational r3{"13/3"};
  std::cout << "r3 " << r3 << std::endl;

  std::string t{"16/24"};
  Rational r4{t};
  std::cout << "r4 " << r4 << std::endl;

  Rational r5 = r3;
  std::cout << "r5 " << r5 << std::endl;

  Rational r6 = Rational{1, 3};
  std::cout << "r6 " << r6 << std::endl;

  Rational r7 = r2 + r4;
  std::cout << "r7 " << r7 << std::endl;

  Rational r8 = r2 - r4;
  std::cout << "r8 " << r8 << std::endl;

  Rational r9 = r3 * r4;
  std::cout << "r9 " << r9 << std::endl;

  Rational r10 = r3 * 3;
  std::cout << "r10 " << r10 << std::endl;

  Rational r11{};
  std::cout << "r11 " << r11++ << std::endl;
  ++r11;
  std::cout << "r11 " << r11 << std::endl;
  std::cout << "r11 " << r11-- << std::endl;
  --r11;
  std::cout << "r11 " << r11 << std::endl;

  std::cout << (r11 == r1) << std::endl;
  std::cout << (r10 != r1) << std::endl;

  std::cout << (r11 == "4/3") << std::endl;
  std::cout << (r11 != "4/3") << std::endl;

  r11 = "4/5";
  std::cout << "r11 " << r11++ << std::endl;

  Rational r12{};

  r12 = r11 = r10;
  std::cout << "r11 " << r11 << std::endl;
  std::cout << "r12 " << r12 << std::endl;

  return 0;
}
