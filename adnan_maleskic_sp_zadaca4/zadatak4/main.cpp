#include <iostream>
#include "Queue.hpp"

int main(void)
{
  Queue<int> q(10);
  q.push(10).push(9).push(8).push(7);
  q.push(6).push(5).push(4).push(3).push(2).push(1);
  Queue<int> p;
  p = q;
  while(!q.empty()) {
    std::cout << q.pop() << std::endl;
  }
  while(!p.empty()) {
    std::cout << p.pop() << std::endl;
  }

  return 0;
}
