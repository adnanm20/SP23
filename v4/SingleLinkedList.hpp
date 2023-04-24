#pragma once
#include <iostream>

template <typename T>
struct Node {
  T data;
  Node* next{nullptr};
  Node(const T& element) : data{element}, next{nullptr} {}
};

template <typename T>
class SingleLinkedList {
  public:
  SingleLinkedList();
  SingleLinkedList(const SingleLinkedList&);
  SingleLinkedList(SingleLinkedList&&);
  SingleLinkedList& operator=(const SingleLinkedList&);
  SingleLinkedList& operator=(SingleLinkedList&&);
  ~SingleLinkedList();
  SingleLinkedList& push_back(const T&);
  Node<T>* head() const;
  Node<T>* tail() const;
  SingleLinkedList& push_front(const T&);
  SingleLinkedList& pop_front();
  SingleLinkedList& pop_back();
  T& front() const;
  T& back() const;

  bool empty() const;
  size_t size() const;
  SingleLinkedList& extend(const SingleLinkedList&);

  private:
  void copyList(const SingleLinkedList&);
  void dealoc();
  Node<T>* head_{nullptr};
  Node<T>* tail_{nullptr};
  size_t size_{0};
};

// template <typename T>
// std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T>& lista){}

template <typename T>
SingleLinkedList<T>::SingleLinkedList() {}
  
template <typename T>
SingleLinkedList<T>::SingleLinkedList(const SingleLinkedList& oL) {
  if(oL.empty()) return;

  head_ = tail_ = new Node<T>(oL.head_->data);
  Node<T>* n = oL.head_->next;
  while(n != nullptr)
  {
    tail_->next = new Node<T>(n->data);
    tail_ = tail_->next;
    n = n->next;
  }
  size_ = oL.size_;
}
  
template <typename T>
SingleLinkedList<T>::SingleLinkedList(SingleLinkedList&& oL) : head_{oL.head_},
  tail_{oL.tail_}, size_{oL.size_} {
    oL.head_ = nullptr;
    oL.tail_ = nullptr;
    oL.size_ = 0;
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(const SingleLinkedList& oL) {
  Node<T>* temp = head_->next;
  while(head_ != nullptr) {
    delete head_;
    head_ = temp;
    temp = head_->next;
  }

  if(oL.empty()) return;

  head_ = tail_ = new Node<T>(oL.head_->data);
  Node<T>* n = oL.head_->next;
  while(n != nullptr) {
    tail_->next = new Node<T>(n->data);
    tail_ = tail_->next;
    n = n->next;
  }
  size_ = oL.size_;
  return *this;
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::operator=(SingleLinkedList&& oL) {
  Node<T>* temp = head_->next;
  while(head_ != nullptr) {
    delete head_;
    head_ = temp;
    temp = head_->next;
  }

  head_ = oL.head_;
  tail_ = oL.tail_;
  size_ = oL.size_;

  oL.head_ = nullptr;
  oL.tail_ = nullptr;
  oL.size_ = 0;

  return *this;
}
  
template <typename T>
SingleLinkedList<T>::~SingleLinkedList() {
  Node<T>* temp = head_->next;
  while(head_ != nullptr) {
    delete head_;
    head_ = temp;
    temp = head_->next;
  }
}
  
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::push_back(const T&){}
  
// template <typename T>
// Node<T>* SingleLinkedList<T>::head() const{}
  
// template <typename T>
// Node<T>* SingleLinkedList<T>::tail() const{}
  
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::push_front(const T&){}
  
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::pop_front(){}
  
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::pop_back(){}
  
// template <typename T>
// T& SingleLinkedList<T>::front() const{}
  
// template <typename T>
// T& SingleLinkedList<T>::back() const{}

// template <typename T>
// bool SingleLinkedList<T>::empty() const{}
  
// template <typename T>
// size_t SingleLinkedList<T>::size() const{}
  
// template <typename T>
// SingleLinkedList<T>& SingleLinkedList<T>::extend(const SingleLinkedList&){}

// template <typename T>
// void SingleLinkedList<T>::copyList(const SingleLinkedList&){}

// template <typename T>
// void SingleLinkedList<T>::dealoc(){}
