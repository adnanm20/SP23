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
  SingleLinkedList& insert(size_t, const T&);
  SingleLinkedList& erase(size_t);
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

template <typename T>
std::ostream& operator<<(std::ostream& os, const SingleLinkedList<T>& lista) {
  Node<T>* el = lista.head();
  while(el != nullptr) {
    os << el->data << '\n';
    el = el->next;
  }
  return os;
}

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

  if(oL.empty()) return *this;

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
  if(empty()) return;
  Node<T>* temp = head_;
  while(temp != nullptr) {
      head_ = head_->next;
    delete temp;
    temp = head_;
  }
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::push_back(const T& val) {
  Node<T>* newNode = new Node<T>(val);
  if(empty()) {
    head_ = tail_ = newNode;
  }
  else {
    tail_->next = newNode;
    tail_ = newNode;
  }
  ++size_;
  return *this;
}
  
template <typename T>
Node<T>* SingleLinkedList<T>::head() const {
  return head_;
}
  
template <typename T>
Node<T>* SingleLinkedList<T>::tail() const {
  return tail_;
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::push_front(const T& val) {
  Node<T>* newNode = new Node<T>(val);
  newNode->next = head_;
  head_ = newNode;
  ++size_;
  return *this;
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::pop_front() {
  if(empty()) return *this;
  Node<T>* temp = head_;
  head_ = head_->next;
  delete temp;
  --size_;
  return *this;
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::pop_back() {
  if(empty()) return *this;
  if(head_ == tail_) {
    delete head_;
    head_ = tail_ = nullptr;
    return *this;
  }
  Node<T>* inc = head_;
  while(inc->next != tail_) {
    inc = inc->next;
  }
  delete tail_;
  tail_ = inc;
  tail_->next = nullptr;
  --size_;
  return *this;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::insert(size_t pos, const T& val) {
  if(pos > size_) return *this;
  Node<T>* newNode = new Node<T>(val);
  ++size_;
  if(empty()) {
    head_ = tail_ = newNode;
    return *this;
  }
  if(pos == 0) {
    newNode->next = head_;
    head_ = newNode;
    return *this;
  }
  Node<T>* temp = head_;
  for(size_t i = 1; i < pos && i < size_; ++i) {
    temp = temp->next;
  }
  newNode->next = temp->next;
  temp->next = newNode;
  return *this;
}

template<typename T>
SingleLinkedList<T>& SingleLinkedList<T>::erase(size_t pos) {
  if(empty()) return *this;
  if(pos >= size_) return *this;
  --size_;
  if(pos == 0) {
    Node<T>* temp = head_;
    head_ = head_->next;
    delete temp;
    return *this;
  }
  Node<T>* temp = head_;
  for(size_t i = 1; i < pos && i < size_; ++i) {
    temp = temp->next;
  }
  Node<T>* temp2 = temp->next;
  temp->next = temp2->next;
  delete temp2;
  return *this;
}
  
template <typename T>
T& SingleLinkedList<T>::front() const {
  return head_->data;
}
  
template <typename T>
T& SingleLinkedList<T>::back() const {
  return tail_->data;
}

template <typename T>
bool SingleLinkedList<T>::empty() const {
  return size_ == 0;
}
  
template <typename T>
size_t SingleLinkedList<T>::size() const {
  return size_;
}
  
template <typename T>
SingleLinkedList<T>& SingleLinkedList<T>::extend(const SingleLinkedList& oL) {
  Node<T>* n = oL.head_;
  if(empty()) {
    head_ = tail_ = new Node<T>(n->data);
    n = n->next;
  }
  while(n != nullptr) {
    tail_->next = new Node<T>(n->data);
    tail_ = tail_->next;
    n = n->next;
  }
  size_ += oL.size_;
}

template <typename T>
void SingleLinkedList<T>::copyList(const SingleLinkedList& oL) {
  dealoc();

  if(oL.empty()) return;

  head_ = tail_ = new Node<T>(oL.head_->data);
  Node<T>* n = oL.head_->next;
  while(n != nullptr) {
    tail_->next = new Node<T>(n->data);
    tail_ = tail_->next;
    n = n->next;
  }
  size_ = oL.size_;
}

template <typename T>
void SingleLinkedList<T>::dealoc() {
  Node<T>* temp = head_->next;
  while(head_ != nullptr) {
    delete head_;
    head_ = temp;
    temp = temp->next;
  }
  tail_ = nullptr;
}
