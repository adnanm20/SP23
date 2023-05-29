#pragma once
#include <stack>
#include <string>
#include <stdexcept>

class RPN {
  public:
    RPN() = default;
    ~RPN() = default;
    int calculate(std::string s) {
      for(auto it = s.begin(); it != s.end(); ++it) {
        int a = 0, b = 0;
        if(*it == ' ') continue;
        if(*it >= '0' && *it <= '9') {
          while(*it != ' ') {
            a = a * 10 + *it - '0';
            ++it;
          }
          nums_.push(a);
        } else {
          b = nums_.top();
          nums_.pop();
          a = nums_.top();
          nums_.pop();
          if(*it == '+') {
            nums_.push(a+b);
          } else if(*it == '-') {
            nums_.push(a-b);
          } else if(*it == '*') {
            nums_.push(a*b);
          } else if(*it == '/') {
            nums_.push(a/b);
          }
        }
      }
      if(nums_.size() != 1) throw std::invalid_argument("calculation not possible");
      int res = nums_.top();
      nums_.pop();
      return res;
    }
  private:
    std::stack<int> nums_{};
};
