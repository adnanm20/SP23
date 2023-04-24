#include "SingleLinkedList.hpp"
#include <string>

int main(int argc, char* argv[]) {
  SingleLinkedList<std::string> lista;
  lista.push_back("word1").push_back("word2");
  lista.push_front("word3");
  std::cout << lista << std::endl;
  lista.pop_front();
  std::cout << lista << std::endl;
  return 0;
}
