#include <iostream>
#include "queue.hpp"

template<typename T>
void swap(Queue<T>& q1, Queue<T>& q2) {
  size_t n1 = q1.size();
  size_t n2 = q2.size();
  for(size_t i = 0; i < n1; ++i) {
    q2.push(q1.front());
    q1.pop();
  }
  for(size_t i = 0; i < n2; ++i) {
    q1.push(q2.front());
    q2.pop();
  }
}

int main(void)
{
  Queue<int> q;
  q.push(1);
  q.push(2);
  q.push(3);
  q.push(4);
  q.push(5);
  Queue<int> b;
  b.push(6);
  b.push(7);
  b.push(8);
  std::cout << "q: " << q << std::endl;
  std::cout << "b: " << b << std::endl;
  swap(q, b);
  std::cout << "q: " << q << std::endl;
  std::cout << "b: " << b << std::endl;
  return 0;
}
