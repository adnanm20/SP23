#include <iostream>
#include "Heap.hpp"

int main(void)
{
  Heap<int> heap;
  heap.push(5).push(4).push(3).push(6).push(2).push(8);
  std::cout << heap << std::endl;
  heap.removeMax();
  std::cout << heap << std::endl;
  heap.removeMax();
  std::cout << heap << std::endl;

  return 0;
}
