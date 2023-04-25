#pragma once
#include <initializer_list>
#include <iterator>
#include <functional>

template <typename T>
class MojVektor {
  public:
  class Iterator;
  MojVektor();
  MojVektor(const std::initializer_list<T>&);
  MojVektor(const MojVektor&);
  MojVektor& operator=(const MojVektor&);
  MojVektor(MojVektor&&);
  MojVektor& operator=(MojVektor&&);
  ~MojVektor();
  MojVektor& push_back(const T&);
  MojVektor& push_front(const T&);
  MojVektor& push_back(T&&);
  MojVektor& push_front(T&&);
  size_t size() const;
  T& at(size_t) const;
  T& operator[](size_t) const;
  T* data() const;
  void clear();
  void resize(size_t newSize, const T& difference_value);
  MojVektor& pop_back();
  MojVektor& pop_front();
  T& back() const;
  T& front() const;
  bool empty() const;
  size_t capacity() const;
  bool operator==(const MojVektor&) const;
  bool operator!=(const MojVektor&) const;
  bool full() const;
  MojVektor subvector(Iterator begin, Iterator end);
  Iterator begin() const;
  Iterator end() const;
  Iterator find(const T&) const;
  Iterator find(std::function<bool(const T&)>) const;
  MojVektor<T> findAll(std::function<bool(const T&)>) const;
  Iterator erase(Iterator pos);
  Iterator insert(Iterator, const T&);
  Iterator insert(Iterator, T&&);
  Iterator rbegin() const;
  Iterator rend() const;
  Iterator erase(Iterator beginIt, Iterator endIt);
  void rotate();
  void rotate(Iterator beginIt, Iterator endIt);

  class Iterator {
    private:
      T* p_ = nullptr;
    public:
      Iterator() : p_{nullptr} {}
      Iterator(T* x) : p_{x} {}
      Iterator(const Iterator& o) : p_{o.p_} {};
      Iterator(Iterator&& o) : p_{o.p_} {o.p_ = nullptr;};
      Iterator& operator=(const Iterator& o) {
        p_ = o.p_;
      }
      Iterator& operator=(Iterator&& o) {
        p_ = o.p_;
        o.p_ = nullptr;
      }
      
      using iterator_category = std::random_access_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = T;
      using pointer = value_type*;
      using reference = value_type&;

      T& operator*() const {return *p_;}
      Iterator& operator++() {++p_; return *this;}
      Iterator operator++(int) {return p_++;}
      Iterator& operator--() {--p_; return *this;}
      Iterator operator--(int) {return p_--;}

      T* operator[](int ind) const {
        return p_ + ind;
      }

      Iterator operator+(int x) {
        return p_ + x;
      }

      Iterator operator-(int x) {
        return p_ - x;
      }

      T* operator->() const {
        return p_;
      }

      bool operator==(Iterator o) const {
        return p_ == o.p_;
      }
      bool operator!=(Iterator o) const {
        return p_ != o.p_;
      }

      bool operator<(Iterator o) const {
        return p_ < o.p_;
      }
      bool operator<=(Iterator o) const {
        return p_ <= o.p_;
      }
      bool operator>(Iterator o) const {
        return p_ > o.p_;
      }
      bool operator>=(Iterator o) const {
        return p_ >= o.p_;
      }

      size_t operator-(Iterator o) const {
        return p_ - o.p_;
      }

  };

  private:
  void realoc();
  size_t capacity_;
  size_t size_;
  T* arr_;
};

// Implementacija ovdje

template<typename T>
std::ostream& operator<<(std::ostream& o, const MojVektor<T>& v) {
  // o << '{';
  for(auto it = v.begin(); it < v.end(); ++it) {
    o << *it; //<< (it != v.end()-1 ? ", " : "");
  }
  // o << '}';
  return o;
}

template<typename T>
MojVektor<T>::MojVektor() : capacity_{10}, size_{0}, arr_{new T[capacity_]} {}
template<typename T>
MojVektor<T>::MojVektor(const std::initializer_list<T>& l) : capacity_{l.size()}, size_{l.size()}, arr_{new T[capacity_]} {
  std::copy(l.begin(), l.end(), arr_);
}
template<typename T>
MojVektor<T>::MojVektor(const MojVektor<T>& o) : capacity_{o.capacity_}, size_{o.size_}, arr_{new T[capacity_]} {
  std::copy(o.begin(), o.end(), arr_);
}
template<typename T>
MojVektor<T>& MojVektor<T>::operator=(const MojVektor<T>& o) {
  delete[] arr_;
  capacity_ = o.capacity_;
  size_ = o.size_;
  arr_ = new T[capacity_];
  std::copy(o.begin(), o.end(), arr_);
  return *this;
}
template<typename T>
MojVektor<T>::MojVektor(MojVektor<T>&& o) : capacity_{o.capacity_}, size_{o.size_}, arr_{o.arr_} {
  o.arr_ = nullptr;
  o.size_ = 0;
  o.capacity_ = 0;
}
template<typename T>
MojVektor<T>& MojVektor<T>::operator=(MojVektor<T>&& o) {
  delete[] arr_;
  capacity_ = o.capacity_;
  size_ = o.size_;
  arr_ = o.arr_;
  o.arr_ = nullptr;
  o.size_ = 0;
  o.capacity_ = 0;
  return *this;
}
template<typename T>
MojVektor<T>::~MojVektor() {
  delete[] arr_;
  size_ = 0;
  capacity_ = 0;
}

template<typename T>
void MojVektor<T>::realoc() {
  capacity_ *= 2;
  T* newArr = new T[capacity_];
  std::copy(begin(), end(), newArr);
  delete[] arr_;
  arr_ = newArr;
}

template<typename T>
MojVektor<T>& MojVektor<T>::push_back(const T& el) {
  if(full() || arr_ == nullptr) realoc();

  arr_[size_] = el;
  ++size_;
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_front(const T& el) {
  if(full() || arr_ == nullptr) realoc();

  for(size_t i = size_; i > 0; --i)
    arr_[i] = arr_[i-1];

  arr_[0] = el;
  ++size_;
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_back(T&& el) {
  if(full() || arr_ == nullptr) realoc();

  arr_[size_] = std::move(el);
  ++size_;
  return *this;
}
template<typename T>
MojVektor<T>& MojVektor<T>::push_front(T&& el) {
  if(full() || arr_ == nullptr) realoc();

  for(size_t i = size_; i > 0; --i)
    arr_[i] = arr_[i-1];

  arr_[0] = std::move(el);
  ++size_;
  return *this;
}
template<typename T>
size_t MojVektor<T>::size() const {return size_;}

template<typename T>
T& MojVektor<T>::at(size_t ind) const {
  if(ind < 0 || ind >= size_) throw std::out_of_range("Index out of range");
  return arr_[ind];
}
template<typename T>
T& MojVektor<T>::operator[](size_t ind) const {return arr_[ind];}
template<typename T>
void MojVektor<T>::clear() {
  delete[] arr_;
  arr_ = nullptr;
  size_ = 0;
}

template<typename T>
T* MojVektor<T>::data() const {
  return arr_;
}

template<typename T>
void MojVektor<T>::resize(size_t newSize, const T& difference_value) {
  if (newSize > size_) {
    T* newArr = new T[newSize];
    std::copy(begin(), end(), newArr);
    for(size_t i = size_; i < newSize; ++i)
      newArr[i] = difference_value;
    delete[] arr_;
    arr_ = newArr;
    capacity_ = newSize;
  }
  size_ = newSize;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_back() {
  if(empty()) throw std::out_of_range("Container is empty.");
  --size_;
  return *this;
}

template<typename T>
MojVektor<T>& MojVektor<T>::pop_front() {
  if(empty()) throw std::out_of_range("Container is empty.");

  std::copy(begin()+1, end(), begin());
  --size_;
  return *this;
}
template<typename T>
T& MojVektor<T>::back() const {
  if(empty()) throw std::out_of_range("Container is empty.");
  
  return arr_[size_-1];
}
template<typename T>
T& MojVektor<T>::front() const {
  if(empty()) throw std::out_of_range("Container is empty.");

  return arr_[0];
}
template<typename T>
bool MojVektor<T>::empty() const {
  return size_ == 0;
}
template<typename T>
size_t MojVektor<T>::capacity() const {
  return capacity_;
}
template<typename T>
bool MojVektor<T>::operator==(const MojVektor& o) const {
  if(size_ != o.size_) return false;
  for(size_t i = 0; i < size_; ++i)
    if(arr_[i] != o[i]) 
      return false;

  return true;
}
template<typename T>
bool MojVektor<T>::operator!=(const MojVektor<T>& o) const {
  return !operator==(o);
}
template<typename T>
bool MojVektor<T>::full() const {
  return size_ == capacity_;
}
template<typename T>
MojVektor<T> MojVektor<T>::subvector(typename MojVektor<T>::Iterator begin, typename MojVektor<T>::Iterator end) {
  MojVektor<T> r;
  while(begin != end) {
    r.push_back(*begin);
    ++begin;
  }
  return r;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::begin() const {
  return Iterator{arr_};
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::end() const {
  return Iterator{arr_ + size_};
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(const T& val) const {
  Iterator b = begin();
  while(b != end()) {
    if(*b == val) break;
    ++b;
  }
  return b;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::find(std::function<bool(const T&)> pred) const {
  Iterator b = begin();
  while(b != end()) {
    if(pred(*b)) break;
    ++b;
  }
  return b;
}

template<typename T>
MojVektor<T> MojVektor<T>::findAll(std::function<bool(const T&)> pred) const {
  Iterator b = begin();
  MojVektor<T> ret;
  while(b != end()) {
    if(pred(*b)) ret.push_back(*b);
    ++b;
  }
  return ret;
}

template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator pos) {
  if(empty()) throw std::out_of_range("Container is empty");
  if(pos == end()) return pos;

  std::copy(pos+1, end(), pos);
  --size_;
  return pos;
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, const T& val) {
  if(pos >= end()) throw std::out_of_range("dmasiofnl");
  size_t x = pos - begin();
  if(full()) {
    realoc();
    pos = begin() + x;
  }

  for(Iterator i = end(); i > pos; --i)
    *i = *(i -1);

  *pos = val;
  ++size_;
  return pos;
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::insert(Iterator pos, T&& val) {
  if(pos >= end()) throw std::out_of_range("dmasiofnl");
  size_t x = pos - begin();
  if(full()) {
    realoc();
    pos = begin() + x;
  }

  for(Iterator i = end(); i > pos; --i)
    *i = *(i -1);

  *pos = std::move(val);
  ++size_;
  return pos;
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rbegin() const {
  return Iterator{arr_ + size_ - 1};
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::rend() const {
  return Iterator{arr_ - 1};
}
template<typename T>
typename MojVektor<T>::Iterator MojVektor<T>::erase(Iterator beginIt, Iterator endIt) {
  while(beginIt != endIt) {
    beginIt = erase(beginIt);
    --endIt;
  }
  return beginIt;
}

template<typename T>
void MojVektor<T>::rotate() {
  Iterator b = begin(), e = rbegin();
  while(b < e) {
    std::swap(*b, *e);
    ++b;
    --e;
  }
}
template<typename T>
void MojVektor<T>::rotate(Iterator beginIt, Iterator endIt) {
  --endIt;

  while(beginIt < endIt) {
    std::swap(*beginIt, *endIt);
    ++beginIt;
    --endIt;
  }
}
