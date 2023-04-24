#pragma once
#include <algorithm>
#include <stdexcept>
class MojVektor {
  public:
  class Iterator;
  MojVektor();
  MojVektor(const std::initializer_list<int>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(int);
  MojVektor& push_front(int);
  size_t size() const;
  int& at(size_t) const;
  int& operator[](size_t) const;
  void clear();
  void resize(size_t);
  MojVektor& pop_back();
  MojVektor& pop_front();
  int& back() const;
  int& front() const;
  bool empty() const;
  size_t capacity() const;
  int* data();
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  
  Iterator begin() const;
  Iterator end() const;
  Iterator find(int) const;
  Iterator erase(Iterator);
  Iterator insert(Iterator, int);
  Iterator erase(Iterator, Iterator);

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  int* arr_;
};

std::ostream& operator<<(std::ostream&, const MojVektor&);

class MojVektor::Iterator{
    private:
      int* ptr_;

    public:
      Iterator(int* p = nullptr);

      int& operator*();

      Iterator& operator++();
      Iterator operator++(int);
      Iterator& operator--();
      Iterator operator--(int);

      Iterator operator+(int);
      Iterator operator-(int);

      bool operator<(const Iterator&);
      bool operator>(const Iterator&);
      bool operator<=(const Iterator&);
      bool operator>=(const Iterator&);

      size_t operator-(const Iterator&);

      bool operator==(const Iterator& oI);
      bool operator!=(const Iterator& oI);
};

