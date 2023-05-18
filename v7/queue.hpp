#pragma once
#include <iostream>

template<typename T>
class Queue {
  public:
    Queue();
    Queue(const Queue&);
    Queue(Queue&&);
    Queue& operator=(const Queue&);
    Queue& operator=(Queue&&);
    ~Queue();
    void push(const T&);
    void pop();
    const T& front() const;
    T& front();
    const T& back() const;
    T& back();
    bool empty() const;
    size_t size() const;
  private:
    class Node {
      public:
        Node(const T& el) : data_{el} {};

        T data_;
        Node* next_{nullptr};

        void del() {
          if(next_ != nullptr) {
            next_->del();
            delete next_;
          }
        }
    };
    void copyList(const Queue&);
    void dealoc();
    Node* head_{nullptr};
    Node* tail_{nullptr};
    size_t size_{0};
};

template<typename T>
std::ostream& operator<<(std::ostream& o, const Queue<T>& q)
{
  Queue<T> temp{q};
  while(!temp.empty()) {
    o << temp.front() << ' ';
    temp.pop();
  }
  return o;
}

template<typename T>
Queue<T>::Queue() {}

template<typename T>
Queue<T>::Queue(const Queue& o) {
  copyList(o);
}

template<typename T>
Queue<T>::Queue(Queue&& o) : head_{o.head_}, tail_{o.tail_}, size_{o.size_} {
  o.head_ = nullptr;
  o.tail_ = nullptr;
  o.size_ = 0;
}

template<typename T>
Queue<T>& Queue<T>::operator=(const Queue& o) {
  dealoc();
  copyList(o);
}

template<typename T>
Queue<T>& Queue<T>::operator=(Queue&& o) {
  head_ = o.head_;
  tail_ = o.tail_;
  size_ = o.size_;
  o.head_ = nullptr;
  o.tail_ = nullptr;
  o.size_ = 0;
}

template<typename T>
Queue<T>::~Queue() {
  dealoc();
}

template<typename T>
bool Queue<T>::empty() const {
  return size_ == 0;
}

template<typename T>
size_t Queue<T>::size() const {
  return size_;
}

template<typename T>
void Queue<T>::push(const T& el) {
  if(empty()) {
    head_ = tail_ = new Node{el};
  } else {
    tail_->next_ = new Node{el};
    tail_ = tail_->next_;
  }
  ++size_;
}

template<typename T>
void Queue<T>::pop() {
  if(empty()) {
    throw std::out_of_range{"Queue is empty"};
  } else {
    Node* temp = head_->next_;
    delete head_;
    head_ = temp;
  }
  --size_;
}

template<typename T>
const T& Queue<T>::front() const {
  return head_->data_;
}

template<typename T>
T& Queue<T>::front() {
  return head_->data_;
}

template<typename T>
const T& Queue<T>::back() const {
  return tail_->data_;
}

template<typename T>
T& Queue<T>::back() {
  return tail_->data_;
}

template<typename T>
void Queue<T>::copyList(const Queue& o) {
  if(o.head_ == nullptr) return;
  if(head_ == nullptr) {
    head_ = tail_ = new Node{o.head_->data_};
  }

  Node* n = o.head_->next_;
  while(n != nullptr) {
    tail_->next_ = new Node{n->data_};
    tail_ = tail_->next_;
    n = n->next_;
  }
  size_ += o.size_;
}

template<typename T>
void Queue<T>::dealoc() {
  if(head_ != nullptr) {
    head_->del();
    delete head_;
  }
  // Node<T>* temp = head_;
  // while(head_ != nullptr) {
  //   head_ = head_->next_;
  //   delete temp;
  //   temp = head_;
  // }
}
