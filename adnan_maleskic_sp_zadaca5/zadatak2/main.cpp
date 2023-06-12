#include <iostream>
#include "Map.hpp"

int main(void)
{
  Map<int, double> mapa;
  mapa[0] = 3.0;
  mapa[7] = 2.0;
  mapa[2] = 5.0;
  mapa[142] = 9.65;
  std::cout << mapa[0] << std::endl;
  std::cout << mapa[7] << std::endl;
  std::cout << mapa[2] << std::endl;
  std::cout << mapa[142] << std::endl;
  mapa.erase(142);
  std::cout << mapa[0] << std::endl;
  std::cout << mapa[7] << std::endl;
  std::cout << mapa[2] << std::endl;
  try {
    double x = mapa.at(142);
  } catch(std::out_of_range e) {
    std::cout << e.what() << std::endl;
  }
  double* d = mapa.find(7);
  if(d != nullptr)
    std::cout << *d << std::endl;
  d = mapa.find(4);
  if(d != nullptr)
    std::cout << *d << std::endl;
  return 0;
}
