#include "duration.hpp"

Duration& Duration::set_h(int h) {
  if(h < 0 || h > 99) throw std::out_of_range{"Value out of range"};
  hours_ = h;
  return *this;
}

Duration& Duration::set_m(int m) {
  if(m < 0 || m > 59) throw std::out_of_range{"Value out of range"};
  minutes_ = m;
  return *this;
}

Duration& Duration::set_s(int s) {
  if(s < 0 || s > 59) throw std::out_of_range{"Value out of range"};
  seconds_ = s;
  return *this;
}


bool Duration::operator==(const Duration& other) {
  return this->toSeconds() == other.toSeconds();
}
bool Duration::operator!=(const Duration& other) {
  return this->toSeconds() != other.toSeconds();
}
bool Duration::operator>(const Duration& other) {
  return this->toSeconds() > other.toSeconds();
}
bool Duration::operator<(const Duration& other) {
  return this->toSeconds() < other.toSeconds();
}
bool Duration::operator>=(const Duration& other) {
  return this->toSeconds() >= other.toSeconds();
}
bool Duration::operator<=(const Duration& other) {
  return this->toSeconds() <= other.toSeconds();
}

Duration Duration::operator+(const Duration& other) const {
  return Duration(this->toSeconds() + other.toSeconds());
}
Duration& Duration::operator+=(const Duration& other) {
  int s = other.toSeconds();
  seconds_ += s % 60;
  minutes_ += seconds_/60;
  seconds_ %= 60;
  s /= 60;
  minutes_ += s % 60;
  hours_ += minutes_/60;
  minutes_ %= 60;
  s /= 60;
  hours_ += s % 60;
  return *this;
}
Duration Duration::operator-(const Duration& other) const {
  return Duration(this->toSeconds() - other.toSeconds());
}
Duration& Duration::operator-=(const Duration& other) {
  if(hours_ < other.hours_) throw std::out_of_range{""};
  hours_ -= other.hours_;
  
  if(minutes_ < other.minutes_ && hours_ == 0) throw std::out_of_range{""};
  minutes_ -= other.minutes_;
  if(minutes_ < 0) {
    minutes_ += 60;
    --hours_;
  }

  if(seconds_ < other.seconds_ && hours_ == 0 && minutes_ == 0) throw std::out_of_range{""};
  seconds_ -= other.seconds_;
  if(seconds_ < 0) {
    seconds_ += 60;
    --minutes_;
    if(minutes_ < 0) {
      minutes_ += 60;
      --hours_;
    }
  }

  return *this;
}
Duration Duration::operator*(int n) const {
  return Duration(this->toSeconds() * n);
}
Duration& Duration::operator*=(int n) {
  int s = this->toSeconds() * n;
  if(s < 0 || s > (99*3600 + 59*60 + 59)) throw std::out_of_range{"Value out of range"};
  seconds_ = s % 60;
  s /= 60;
  minutes_ = s % 60;
  s /= 60;
  hours_ = s % 60;
  
  return *this;
}
Duration Duration::operator/(int n) const {
  return Duration(this->toSeconds() / n);
}
Duration& Duration::operator/=(int n) {
  int s = this->toSeconds() / n;
  seconds_ = s % 60;
  s /= 60;
  minutes_ = s % 60;
  s /= 60;
  hours_ = s % 60;
  
  return *this;
}

std::istream& operator>>(std::istream& i, Duration& d) {
  std::string s;
  i >> s;
  d = Duration(s);
  return i;
}

std::ostream& operator<<(std::ostream& o, const Duration& d) {
  if(d.get_h() < 10) o << 0;
  o << d.get_h() << ":";

  if(d.get_m() < 10) o << 0;
  o << d.get_m() << ":";

  if(d.get_s() < 10) o << 0;
  o << d.get_s();
  return o;
}
