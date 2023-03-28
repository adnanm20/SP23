#include <iostream>
#include <vector>
#include <functional>
#include <string>

template<typename T, typename arr, typename U>
T func(T poc, arr niz, U lambda)
{
  for(auto it = niz.begin(); it != niz.end(); ++it)
  {
    poc = lambda(*it, poc);
  }
  return poc;
}

int main(void)
{
  std::vector<std::string> niz = {"1", "2", "3", "4"};
  std::string t = "";

  auto rez = func(t, niz, [](std::string a, std::string b) {return a + b;});

  std::cout << rez << std::endl;
  
  return 0;
}
