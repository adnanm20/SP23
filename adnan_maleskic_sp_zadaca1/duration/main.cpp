#include <iostream>
#include "duration.hpp"

int main() {
  // ovdje možete samostalno testirati neke funkcionalnosti. 
  // Napomena: main.cpp se ne pregleda, sva implementacija 
  // ide u duration .cpp i .hpp fileove.
  
  Duration d1{"10:30:45"};
  std::cout << (d1 == Duration{"10:30:50"}) << std::endl;
}
