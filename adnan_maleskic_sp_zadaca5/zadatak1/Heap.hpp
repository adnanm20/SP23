#pragma once
#include <iostream>
#include <functional>

template<typename T>
class Heap {
  private:
    size_t capacity_;
    size_t size_;
    T* elements_;
    void fixTopDown();
    void fixBottomUp();
    void realoc();
  public:
    Heap();
    Heap(const Heap&);
    Heap(Heap&&);
    ~Heap();
    Heap& operator=(const Heap&);
    Heap& operator=(Heap&&);

    size_t size() const;
    size_t capacity() const;

    T& max();
    T& max() const;
    T& removeMax();
    Heap& push(const T&);
    Heap& push(T&&);
    
    void preorder(int, std::function<void(const T&)>) const;
};

template<typename T>
Heap<T>::Heap() : capacity_{10}, size_{0}, elements_{new T[capacity_]} {}
template<typename T>
Heap<T>::Heap(const Heap<T>& o) : capacity_{o.capacity_}, size_{o.size_}, elements_{new T[capacity_]} {
  std::copy(o.elements_, o.elements_+o.size_, elements_);
}
template<typename T>
Heap<T>::Heap(Heap<T>&& o) : capacity_{10}, size_{0}, elements_{o.elements_} {
  o.capacity_ = 0;
  o.size_ = 0;
  o.elements_ = nullptr;
}
template<typename T>
Heap<T>::~Heap() {
  delete[] elements_;
}
template<typename T>
Heap<T>& Heap<T>::operator=(const Heap<T>& o) {
  delete[] elements_;
  capacity_ = o.capacity_;
  size_ = o.size_;
  elements_ = new T[capacity_];
  std::copy(o.elements_, o.elements_+o.size_-1, elements_);
  return *this;
}
template<typename T>
Heap<T>& Heap<T>::operator=(Heap<T>&& o) {
  delete[] elements_;
  elements_ = o.elements_;
  capacity_ = o.capacity_;
  size_ = o.size_;
  o.elements_ = nullptr;
  o.capacity_ = 0;
  o.size_ = 0;
  return *this;
}

template<typename T>
size_t Heap<T>::size() const {
  return size_;
}
template<typename T>
size_t Heap<T>::capacity() const {
  return capacity_;
}

template<typename T>
T& Heap<T>::max() {
  return *elements_;
}
template<typename T>
T& Heap<T>::max() const {
  return *elements_;
}
template<typename T>
T& Heap<T>::removeMax() {
  std::swap(elements_[0], elements_[size_ - 1]);
  --size_;
  fixTopDown();
  return elements_[size_];
}

template<typename T>
Heap<T>& Heap<T>::push(const T& el) {
  if(size_ == capacity_) realoc();
  elements_[size_++] = el;
  fixBottomUp();
  return *this;
}
template<typename T>
Heap<T>& Heap<T>::push(T&& el) {
  if(size_ == capacity_) realoc();
  elements_[size_++] = std::move(el);
  fixBottomUp();
  return *this;
}
template<typename T>
void Heap<T>::realoc() {
  capacity_ *= 2;
  T* newEl = new T[capacity_];
  std::copy(elements_, elements_+size_, newEl);
  delete[] elements_;
  elements_ = newEl;
}

template<typename T>
void Heap<T>::fixTopDown() {
  int ind = 1;
  while(ind *2 <= size_) {
    int j = ind*2;
    if(j < size_ && elements_[j-1] < elements_[j+1-1]) ++j;
    if(elements_[ind-1] >= elements_[j-1]) break;
    std::swap(elements_[ind-1], elements_[j-1]);
    ind = j;
  }
}

template<typename T>
void Heap<T>::fixBottomUp() {
  int ind = size_;
  while(ind > 1 && elements_[ind-1] > elements_[ind/2-1]) {
    std::swap(elements_[ind-1], elements_[ind/2-1]);
    ind /= 2;
  }
}

template<typename T>
void Heap<T>::preorder(int n, std::function<void(const T&)> func) const {
  if(n <= size_) {
    func(elements_[n-1]);
    preorder(n*2, func);
    preorder(n*2+1, func);
  }
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const Heap<T>& h) {
  h.preorder(1, [&](const T& el) {o << el << ' ';});
  return o;
}
