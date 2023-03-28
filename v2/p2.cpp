#include <iostream>
#include <vector>
#include <functional>
#include <string>

class Broj {
  int broj = 0;
  int *p = nullptr;
  public:
    Broj() : broj{0}, p{nullptr} {};
    Broj(int a, int b) : broj{a}, p{new int(b)} {};
    Broj(const Broj& br) : broj{br.broj}, p{new int(*br.p)} {};
    Broj(Broj&& br) : broj{br.broj}, p{br.p} {br.p = nullptr;};
    ~Broj() {delete p;};
};

int main() {
  Broj x;
  Broj y(2, 3);
  Broj z(y);
  Broj v(Broj(1, 2));

  return 0;
}
