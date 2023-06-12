#include <iostream>
#include "../zadatak2/Map.hpp"
#include <vector>
#include <string>

int main(void)
{
  Map<std::string, std::vector<int>> rijeci;
  int i = 1;
  std::string rijec;
  while(std::cin >> rijec) {
    rijeci[rijec].push_back(i++);
  }

  rijeci.inorder([](const std::string& key, const std::vector<int>& vec){
        std::cout << "Rijec je '" << key << "' i nalazi se na sljedecim pozicijama:\n";
        for(int i = 0; i < vec.size(); ++i)
          std::cout << vec[i] << ", ";
        std::cout << std::endl;
      });
  
  return 0;
}
