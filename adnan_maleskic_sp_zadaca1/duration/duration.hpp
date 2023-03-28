#pragma once
#include <iostream>

class Duration {
  public:
  Duration() : hours_{0}, minutes_{0}, seconds_{0} {};

  Duration(int s) {
    if(s < 0 || s > (99*3600 + 59*60 + 59)) throw std::out_of_range{"Value out of range"};
    seconds_ = s % 60;
    s /= 60;
    minutes_ = s % 60;
    s /= 60;
    hours_ = s % 60;
  }

  Duration(int h, int m, int s) {
    if(h > 99 || m > 59 || s > 59 || h < 0 || m < 0 || s < 0)
      throw std::out_of_range{"Values are out of range"};

    hours_ = h;
    minutes_ = m;
    seconds_ = s;
  }

  Duration(std::string s) {
    if(s.size() != 8) throw std::exception();
    for(int i = 0; i < 8; ++i)
    {
      if((i+1) % 3 == 0) continue;
      if((s[i] - '0') < 0 || (s[i] - '0') > 9) throw std::exception();
    }

    hours_ = (s[0] - '0') * 10 + s[1] - '0';
    minutes_ = (s[3] - '0') * 10 + s[4] - '0';
    if(minutes_ > 59) throw std::out_of_range{""};
    seconds_ = (s[6] - '0') * 10 + s[7] - '0';
    if(seconds_ > 59) throw std::out_of_range{""};
  }

  Duration(const Duration& other) = default;
  Duration(Duration&& other) = default;
  Duration& operator=(const Duration& other) = default;
  Duration& operator=(Duration&& other) = default;

  int get_h() const {return hours_;}
  int get_m() const {return minutes_;}
  int get_s() const {return seconds_;}

  Duration& set_h(int);
  Duration& set_m(int);
  Duration& set_s(int);

  operator bool() const {
    return hours_ || minutes_ || seconds_;
  }

  bool operator!() const {
    return !(bool)(*this);
  }

  bool operator==(const Duration&);
  bool operator!=(const Duration&);
  bool operator>(const Duration&);
  bool operator<(const Duration&);
  bool operator>=(const Duration&);
  bool operator<=(const Duration&);

  Duration operator+(const Duration&) const;
  Duration& operator+=(const Duration&);
  Duration operator-(const Duration&) const;
  Duration& operator-=(const Duration&);
  Duration operator*(int) const;
  Duration& operator*=(int);
  Duration operator/(int) const;
  Duration& operator/=(int);

  private:
    int toSeconds() const { return hours_ * 3600 + minutes_ * 60 + seconds_; }  

    int hours_;
    int minutes_;
    int seconds_;
};

std::istream& operator>>(std::istream&, Duration&);
std::ostream& operator<<(std::ostream&, const Duration&);
