#include <iostream>
#include <string>
#include <stack>
#include <stdexcept>

bool check(std::string input) {
  std::stack<char> brackets_;
  for(auto it = input.begin(); it != input.end(); ++it) {
    switch(*it) {
      case '<':
        brackets_.push('<');
        break;
      case '>':
        if(brackets_.empty() || brackets_.top() != '<') return 0;
        brackets_.pop();
        break;
      case '(':
        if(!brackets_.empty() && brackets_.top() == '<') return 0;
        brackets_.push('(');
        break;
      case ')':
        if(brackets_.empty() || brackets_.top() != '(') return 0;
        brackets_.pop();
        break;
      case '[':
        if(!brackets_.empty() && brackets_.top() < '[') return 0;
        brackets_.push('[');
        break;
      case ']':
        if(brackets_.empty() || brackets_.top() != '[') return 0;
        brackets_.pop();
        break;
      case '{':
        if(!brackets_.empty() && brackets_.top() < '{') return 0;
        brackets_.push('{');
        break;
      case '}':
        if(brackets_.empty() || brackets_.top() < '{') return 0;
        brackets_.pop();
        break;
      default:
        throw std::invalid_argument{"invalid character"};
        break;
    }
  }
  return brackets_.empty();
}

int main(void)
{
  std::string input;
  while(std::cin >> input) {
    std::cout << (check(input) ? "dobar\n" : "pogresan\n");
  }

  return 0;
}
