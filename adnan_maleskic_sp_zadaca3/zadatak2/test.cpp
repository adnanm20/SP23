#include <iostream>
#include "../zadatak1/DoubleLinkedList.hpp"

int main(void)
{
  using std::cout;
  using std::endl;

  DoubleLinkedList<int> l;
  l.push_back(4).push_back(1).push_back(7).push_back(2);
  l.push_back(-4).push_back(12).push_back(37).push_back(12);

  for(auto it = l.begin(); it != l.end(); ++it)
    cout << *it << ' ';
  cout << endl;

  l.sort([](int a, int b) {return a < b;});

  cout << "Sorted: ";
  for(auto it = l.begin(); it != l.end(); ++it)
    cout << *it << ' ';
  cout << endl;

  return 0;
}
