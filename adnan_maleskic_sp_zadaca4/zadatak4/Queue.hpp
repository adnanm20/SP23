#pragma once
#include <iostream>

template<typename T>
class Queue {
  public:
    Queue();
    Queue(size_t);
    Queue(const Queue&);
    Queue(Queue&&);
    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&);
    ~Queue();
    template<typename U>
    Queue& push(U&&);
    T pop();
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
    bool empty() const;
    size_t size() const;
    size_t capacity() const;
  private:
    size_t indexer(size_t) const;
    void copyList(const Queue&);
    void realoc();
    size_t capacity_{10};
    T* elements_{nullptr};
    size_t front_{0};
    size_t back_{0};
    size_t size_{0};
};

template<typename T>
Queue<T>::Queue() : capacity_{10}, elements_{new T[capacity_]},
  front_{0}, back_{0}, size_{0} {}

template<typename T>
Queue<T>::Queue(size_t cap) : capacity_{cap}, elements_{new T[capacity_]},
  front_{0}, back_{0}, size_{0} {}

template<typename T>
Queue<T>::Queue(const Queue& o) : capacity_{o.capacity_}, elements_{new T[capacity_]},
  front_{0}, back_{0}, size_{0} {
    copyList(o);
}

template<typename T>
void Queue<T>::copyList(const Queue<T>& o) {
  for(size_t i = 0; i < o.size_; ++i) {
    back_ = indexer(front_+i);
    elements_[back_] = o.elements_[indexer(o.front_+i)];
  }
  size_ += o.size_;
}

template<typename T>
size_t Queue<T>::indexer(size_t ind) const {
  return ind % capacity_;
}

template<typename T>
Queue<T>::Queue(Queue&& o) : capacity_{o.capacity_}, elements_{o.elements_},
  front_{o.front_}, back_{o.back_}, size_{o.size_} {
    o.elements_ = nullptr;
    o.size_ = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& o) {
  delete[] elements_;
  size_ = 0;
  capacity_ = o.capacity_;
  elements_ = new T[capacity_];
  front_ = 0;
  back_ = 0;
  copyList(o);
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& o) {
  delete[] elements_;
  capacity_ = o.capacity_;
  elements_ = o.elements_;
  front_ = o.front_;
  back_ = o.back_;
  size_ = o.size_;
  o.elements_ = nullptr;
  o.size_ = 0;
}

template<typename T>
Queue<T>::~Queue() {
  delete[] elements_;
}

template<typename T>
template<typename U>
Queue<T>& Queue<T>::push(U&&val) {
  if(size_ == capacity_) {
    //realoc()
    throw std::out_of_range("max capacity reached");
  }

  elements_[back_] = std::forward<U>(val);
  back_ = indexer(back_+1);
  ++size_;
  return *this;
}

template<typename T>
T Queue<T>::pop() {
  front_ = indexer(front_ + 1);
  --size_;
  return elements_[indexer(front_-1)];
}

template<typename T>
const T& Queue<T>::front() const {if(!empty())  return elements_[front_]; else throw std::out_of_range("queue is empty");}

template<typename T>
T& Queue<T>::front() {if(!empty()) return elements_[front_]; else throw std::out_of_range("queue is empty");}

template<typename T>
const T& Queue<T>::back() const {if(!empty()) return elements_[indexer(back_-1)]; else throw std::out_of_range("queue is empty");}

template<typename T>
T& Queue<T>::back() {if(!empty()) return elements_[indexer(back_-1)]; else throw std::out_of_range("queue is empty");}

template<typename T>
bool Queue<T>::empty() const { return size_ == 0; }

template<typename T>
size_t Queue<T>::size() const { return size_; }

template<typename T>
size_t Queue<T>::capacity() const { return capacity_; }

template<typename T>
void Queue<T>::realoc() {
  capacity_ *= 2;
  T* newEl = new T[capacity_];
  for(size_t i = 0; i < size_; ++i) {
    newEl[i] = elements_[(front_+i)%size_];
  }
  front_ = 0;
  back_ = size_-1;
  delete[] elements_;
  elements_ = newEl;
}
