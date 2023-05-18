#include "Stack.hpp"
#include <iostream>

template<typename T>
void swapStacks(Stack<T>& s1, Stack<T>& s2) {
  Stack<T> temp;
  while(!s1.empty()) {
    temp.push(s1.top());
    s1.pop();
  }
  while(!temp.empty()) {
    s2.push(temp.top());
    temp.pop();
  }
}

int main(void)
{
  Stack<double> s;
  s.push(4.5);
  s.push(5.5);
  s.push(6.5);
  s.push(7.5);
  s.push(8.5);
  s.push(9.5);
  s.pop();
  s.pop();
  s.pop();
  std::cout << s << std::endl;
  Stack<double> a;
  swapStacks(s, a);
  std::cout << s << std::endl;
  std::cout << a << std::endl;

  return 0;
}
