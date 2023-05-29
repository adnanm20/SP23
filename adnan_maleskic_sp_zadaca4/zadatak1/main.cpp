#include <iostream>
#include <string>
#include "RPN.cpp"

void primjeri() {
  RPN rpn_;
  std::cout << rpn_.calculate("4 5 9 - 7 + 3 + *") << std::endl;
  std::cout << rpn_.calculate("5 1 2 + 4 * + 3 -") << std::endl;
  std::cout << rpn_.calculate("104 25 - 39 +") << std::endl;
  std::cout << rpn_.calculate("21 5 * 3 + 7 -") << std::endl;
}

int main(void)
{
  RPN rpn_;
  // primjeri();
  
  std::string input;
  while(1) {
    getline(std::cin, input);
    if(!std::cin) break;
    std::cout << "Result: " << rpn_.calculate(input) << '\n';
  }

  
  return 0;
}
