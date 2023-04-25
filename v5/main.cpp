#include "SingleLinkedList.hpp"
#include <string>

int main(int argc, char* argv[]) {
  SingleLinkedList<std::string> lista;
  lista.push_back("word1").push_back("word2");
  lista.push_front("word3");
  std::cout << lista << std::endl;
  lista.pop_front();
  std::cout << lista << std::endl;
  SingleLinkedList<std::string> s;
  s.push_back("hello").push_back("1").push_back("2").push_back("3");
  lista.extend(s);
  std::cout << lista << std::endl;
  lista.pop_back();
  std::cout << lista << std::endl;
  lista.insert(0, "jafiusfogah");
  std::cout << lista << std::endl;
  SingleLinkedList<std::string> lista2;
  lista2.insert(0, "jafiusfogah");
  std::cout << lista2 << std::endl;
  lista.erase(1);
  std::cout << lista << std::endl;
  return 0;
}
