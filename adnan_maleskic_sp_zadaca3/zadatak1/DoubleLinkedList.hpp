#pragma once

#include <iterator>
#include <iostream>
#include <functional>

template <typename T>
struct Node {
  Node* prev{nullptr};
  Node* next{nullptr};
  T data;
  Node(const T& element) : data{element}, next{nullptr}, prev{nullptr} {}
};

template <typename T>
class DoubleLinkedList {
  public:
  class Iterator;
  DoubleLinkedList();
  DoubleLinkedList(const DoubleLinkedList&);
  DoubleLinkedList(DoubleLinkedList&&);
  DoubleLinkedList& operator=(const DoubleLinkedList&);
  DoubleLinkedList& operator=(DoubleLinkedList&&);
  ~DoubleLinkedList();

  DoubleLinkedList& push_back(const T&);
  DoubleLinkedList& push_front(const T&);
  DoubleLinkedList& push_back(T&&);
  DoubleLinkedList& push_front(T&&);
  DoubleLinkedList& pop_front();
  DoubleLinkedList& pop_back();
  bool empty() const;
  size_t size() const;
  T& front();
  T& back();
  Iterator begin() const;
  Iterator end() const;
  const Iterator cbegin() const;
  const Iterator cend() const;
  Iterator rbegin() const;
  Iterator rend() const;
  const Iterator rcbegin() const;
  const Iterator rcend() const;
  void clear();
  Iterator insert(Iterator pos, const T& element);
  Iterator erase(Iterator pos);
  Iterator erase(Iterator beginIt, Iterator endIt);
  void remove_if(std::function<bool(const T&)>&& p);
  void reverse();
  Iterator find(const T& element) const;
  Iterator find(std::function<bool(const T&)>) const;
  void sort(std::function<bool(const T&, const T&)>);
  DoubleLinkedList<T> filter(std::function<bool(const T&)>);

  class Iterator {
    private:
      Node<T>* p_ = nullptr;
    public:
      Iterator() : p_{nullptr} {}
      Iterator(Node<T>* x) : p_{x} {}
      Iterator(const Iterator& o) : p_{o.p_} {};
      Iterator(Iterator&& o) : p_{o.p_} {o.p_ = nullptr;};
      Iterator& operator=(const Iterator& o) {
        p_ = o.p_;
      }
      Iterator& operator=(Iterator&& o) {
        p_ = o.p_;
        o.p_ = nullptr;
      }
      
      using iterator_category = std::bidirectional_iterator_tag;
      using difference_type = std::ptrdiff_t;
      using value_type = Node<T>;
      using pointer = value_type*;
      using reference = value_type&;

      T& operator*() const {return p_->data;}
      Iterator& operator++() {p_ = p_->next; return *this;}
      Iterator operator++(int) {auto temp = p_; p_ = p_->next; return temp;}
      Iterator& operator--() {p_ = p_->prev; return *this;}
      Iterator operator--(int) {auto temp = p_; p_ = p_->prev; return temp;}
      Node<T>* node() {return p_;};

      bool operator==(Iterator o) const {
        return p_ == o.p_;
      }
      bool operator!=(Iterator o) const {
        return p_ != o.p_;
      }

      T* operator->() const {
        return &p_->data;
      }

  };

  private:
  void dealoc();
  Node<T>* merge(Node<T>*, Node<T>*, std::function<bool(const T&, const T&)>); 
  Node<T>* mergeSort(Node<T>*, std::function<bool(const T&, const T&)>); 
  Node<T>* split(Node<T>*);
  void setTail(Node<T>*);
  Node<T>* head_{nullptr};
  Node<T>* tail_{nullptr};
  size_t size_{0};
};

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList() {}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(const DoubleLinkedList& o) {
  if(o.empty()) return;

  head_ = tail_ = new Node<T>(o.head_->data);
  Node<T>* n = o.head_->next;
  while(n != nullptr) {
    tail_->next = new Node<T>(n->data);
    tail_->next->prev = tail_;
    tail_ = tail_->next;
    n = n->next;
  }
  size_ = o.size_;
}

template<typename T>
DoubleLinkedList<T>::DoubleLinkedList(DoubleLinkedList&& o) :
  head_{o.head_}, tail_{o.tail_}, size_{o.size_} {
    o.head_ = nullptr;
    o.tail_ = nullptr;
    o.size_ = 0;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(const DoubleLinkedList& o) {
  if(head_ == o.head_) return *this;
  clear();

  if(o.empty()) return *this;

  head_ = tail_ = new Node<T>(o.head_->data);
  Node<T>* n = o.head_->next;
  while(n != nullptr) {
    tail_->next = new Node<T>(n->data);
    tail_->next->prev = tail_;
    tail_ = tail_->next;
    n = n->next;
  }
  size_ = o.size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::operator=(DoubleLinkedList&& o) {
  clear();

  head_ = o.head_;
  tail_ = o.tail_;
  size_ = o.size_;
  o.head_ = nullptr;
  o.tail_ = nullptr;
  o.size_ = 0;
  return *this;
}

template<typename T>
DoubleLinkedList<T>::~DoubleLinkedList() {
  clear();
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(const T& val) {
  if(empty()) {
    head_ = tail_ = new Node<T>(val);
  } else {
    tail_->next = new Node<T>(val);
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  }
  ++size_;
  return *this;
}

template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(const T& val) {
  if(empty()) {
    head_ = tail_ = new Node<T>(val);
  } else {
    head_->prev = new Node<T>(val);
    head_->prev->next = head_;
    head_ = head_->prev;
  }
  ++size_;
  return *this;
}
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_back(T&& val) {
  if(empty()) {
    head_ = tail_ = new Node<T>(std::move(val));
  } else {
    tail_->next = new Node<T>(val);
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  }
  ++size_;
  return *this;
}
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::push_front(T&& val) {
  if(empty()) {
    head_ = tail_ = new Node<T>(std::move(val));
  } else {
    head_->prev = new Node<T>(std::move(val));
    head_->prev->next = head_;
    head_ = head_->prev;
  }
  ++size_;
  return *this;
}
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_front() {
  if(empty()) throw std::out_of_range("List is empty!");

  if(head_ == tail_) {
    delete head_;
    --size_;
    return *this;
  }
  head_ = head_->next;
  delete head_->prev;
  head_->prev = nullptr;
  --size_;
  return *this;
}
template<typename T>
DoubleLinkedList<T>& DoubleLinkedList<T>::pop_back() {
  if(empty()) throw std::out_of_range("List is empty!");

  if(head_ == tail_) {
    delete head_;
    --size_;
    return *this;
  }
  tail_ = tail_->prev;
  delete tail_->next;
  tail_->next = nullptr;
  --size_;
  return *this;
}
template<typename T>
bool DoubleLinkedList<T>::empty() const {
  return size_ == 0;
}
template<typename T>
size_t DoubleLinkedList<T>::size() const {
  return size_;
}
template<typename T>
T& DoubleLinkedList<T>::front() {
  if(empty()) throw std::out_of_range("List is empty!");
  return head_->data;
}
template<typename T>
T& DoubleLinkedList<T>::back() {
  if(empty()) throw std::out_of_range("List is empty!");
  return tail_->data;
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::begin() const {
  return Iterator{head_};
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::end() const {
  if(tail_ == nullptr) return Iterator(nullptr);
  return Iterator{tail_->next};
}
template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cbegin() const {
  return Iterator{head_};
}
template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::cend() const {
  if(tail_ == nullptr) return Iterator(nullptr);
  return Iterator{tail_->next};
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rbegin() const {
  return Iterator{tail_};
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rend() const {
  if(head_ == nullptr) return Iterator(nullptr);
  return Iterator{head_->prev};
}
template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcbegin() const {
  return Iterator{tail_};
}
template<typename T>
const typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::rcend() const {
  if(head_ == nullptr) return Iterator(nullptr);
  return Iterator{head_->prev};
}
template<typename T>
void DoubleLinkedList<T>::clear() {
  while(head_ != tail_) {
    Node<T>* temp = head_->next;
    delete head_;
    head_ = temp;
  }
  delete tail_;
  size_ = 0;
  head_ = nullptr;
  tail_ = nullptr;
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::insert(typename DoubleLinkedList<T>::Iterator pos, const T& element) {
  if(pos == begin()) {
    push_front(element);
    pos = begin();
  } else if (pos == end()) {
    push_back(element);
    pos = end();
  } else {
    Node<T>* temp = new Node<T>(element);
    temp->prev = pos.node()->prev;
    temp->next = pos.node();
    pos.node()->prev->next = temp;
    pos.node()->prev = temp;
    --pos;
    ++size_;
  }
  return pos;
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(typename DoubleLinkedList<T>::Iterator pos) {
  Iterator temp = pos;
  ++temp;
  if(pos != begin()) {
    pos.node()->prev->next = pos.node()->next;
  } else {
    head_ = pos.node()->next;
  }
  if(pos != rbegin()) {
    pos.node()->next->prev = pos.node()->prev;
  } else {
    tail_ = pos.node()->prev;
  }
  delete pos.node();
  --size_;
  return temp;
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::erase(typename DoubleLinkedList<T>::Iterator beginIt, typename DoubleLinkedList<T>::Iterator endIt) {
  while(beginIt != endIt) {
    beginIt = erase(beginIt);
  }
  return beginIt;
}
template<typename T>
void DoubleLinkedList<T>::remove_if(std::function<bool(const T&)>&& p) {
  Iterator b = begin();
  while(b != end()) {
    if(p(*b)) {
      b = erase(b);
    } else {
      ++b;
    }
  }
}
template<typename T>
void DoubleLinkedList<T>::reverse() {
  Iterator b = begin(), e = rbegin();
  while(b != e && b.node()->prev != e.node()) {
    std::swap(*b, *e);
    ++b;
    --e;
  }
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(const T& element) const {
  Iterator b = begin();
  while(b != end()) {
    if(*b == element) break;
    ++b;
  }
  return b;
}
template<typename T>
typename DoubleLinkedList<T>::Iterator DoubleLinkedList<T>::find(std::function<bool(const T&)> p) const {
  Iterator b = begin();
  while(b != end()) {
    if(p(*b)) break;
    ++b;
  }
  return b;
}
template<typename T>
void DoubleLinkedList<T>::sort(std::function<bool(const T&, const T&)> p) {
  if(empty()) return;
  head_ = mergeSort(head_, p);
  setTail(head_);
}

template<typename T>
void DoubleLinkedList<T>::setTail(Node<T>* start) {
  tail_ = start;
  while(tail_->next != nullptr) {
    tail_ = tail_->next;
  }
}

template<typename T>
Node<T>* DoubleLinkedList<T>::mergeSort(Node<T>* p, std::function<bool(const T&, const T&)> func) {
  if(p == nullptr || p->next == nullptr) return p;

  Node<T>* second = split(p);
  Node<T>* first = mergeSort(p, func);
  second = mergeSort(second, func);

  return merge(first, second, func);
}

template<typename T>
Node<T>* DoubleLinkedList<T>::merge(Node<T>* f, Node<T>* s, std::function<bool(const T&, const T&)> func) {
  if(f == nullptr) return s;
  if(s == nullptr) return f;

  if(func(f->data, s->data)) {
    f->next = merge(f->next, s, func);
    f->next->prev = f;
    f->prev = nullptr;
    return f;
  } else {
    s->next = merge(f, s->next, func);
    s->next->prev = s;
    s->prev = nullptr;
    return s;
  }
}

template<typename T>
Node<T>* DoubleLinkedList<T>::split(Node<T>* start) {
  Node<T>* out = start;
  while(start->next != nullptr && start->next->next != nullptr) {
    out = out->next;
    start = start->next->next;
  }
  Node<T>* temp = out->next;
  out->next = nullptr;
  return temp;
}
template<typename T>
DoubleLinkedList<T> DoubleLinkedList<T>::filter(std::function<bool(const T&)> p) {
  DoubleLinkedList<T> out;
  for(Iterator it = begin(); it != end(); ++it) {
    if(p(*it)) out.push_back(*it);
  }
  return out;
}
