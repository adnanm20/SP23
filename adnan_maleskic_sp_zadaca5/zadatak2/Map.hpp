#pragma once
#include <iostream>
#include <functional>

template<typename K, typename V>
class Map {
  private:
    class Node {
      public:
        K key_;
        V value_;
        Node* left;
        Node* right;
        Node(const K& key) : key_{key}, value_{}, left{nullptr}, right{nullptr} {}
        Node(const K& key, const V& val) : key_{key}, value_{val}, left{nullptr}, right{nullptr} {}
    };
    Node* root_;
    size_t size_;
    Node*& find(Node*&, const K&);
    void destroy(Node*);
    void copy(Node*&, Node*);
    void erase(Node*);
    Node*& getParent(Node*&, Node*);
    Node*& getIOP(Node*);
    template<typename F>
    void inorder(Node*, F) const;
  public:
    Map();
    Map(const Map&);
    Map(Map&&);
    Map& operator=(const Map&);
    Map& operator=(Map&&);
    ~Map();
    bool empty() const;
    size_t size() const;

    V& at(const K&);
    const V& at(const K&) const;

    V* find(const K&);
    const V* find(const K&) const;
    V& operator[](const K&);

    template <typename F>
    Map& insert(const K&, F&&);
    bool erase(const K&);
    void clear();
    template<typename F>
    void inorder(F) const;
};

template<typename K, typename V>
Map<K, V>::Map() : root_{nullptr}, size_{0} {}

template<typename K, typename V>
Map<K, V>::Map(const Map<K, V>& o) : root_{nullptr}, size_{0} {
  copy(root_, o.root_);
}

template<typename K, typename V>
void Map<K, V>::copy(Node*& dest, Node* source) {
  if(source == nullptr) return;
  dest = new Node{source->key_, source->value_};
  copy(dest->left, source->left);
  copy(dest->right, source->right);
  ++size_;
}

template<typename K, typename V>
Map<K, V>::Map(Map<K, V>&& o) : root_{o.root_}, size_{o.size_} {
  o.root_ = nullptr;
  o.size_ = 0;
}

template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(const Map<K, V>& o) {
  destroy(root_);
  root_ = nullptr;
  size_ = 0;
  copy(root_, o.root_);
  return *this;
}

template<typename K, typename V>
Map<K, V>& Map<K, V>::operator=(Map<K, V>&& o) {
  destroy(root_);
  root_ = o.root_;
  size_ = o.size_;
  o.root_ = nullptr;
  o.size_ = 0;
  return *this;
}

template<typename K, typename V>
Map<K, V>::~Map() {
  destroy(root_);
}

template<typename K, typename V>
void Map<K, V>::destroy(Node* n) {
  if(n == nullptr) return;
  destroy(n->left);
  destroy(n->right);
  delete n;
}

template<typename K, typename V>
bool Map<K, V>::empty() const { return size_ == 0; }

template<typename K, typename V>
size_t Map<K, V>::size() const { return size_; }

template<typename K, typename V>
V& Map<K, V>::at(const K& key) {
  Node*& n = find(root_, key);
  if(n == nullptr) throw std::out_of_range("Kljuc ne postoji");
  return n->value_;
}

template<typename K, typename V>
const V& Map<K, V>::at(const K& key) const {
  Node*& n = find(root_, key);
  if(n == nullptr) throw std::out_of_range("Kljuc ne postoji");
  return &(n->value_);
}

template<typename K, typename V>
V* Map<K, V>::find(const K& key) {
  Node*& n = find(root_, key);
  return n != nullptr ? &(n->value_) : nullptr;
}

template<typename K, typename V>
const V* Map<K, V>::find(const K& key) const {
  Node*& n = find(root_, key);
  return n != nullptr ? &(n->value_) : nullptr;
}

template<typename K, typename V>
V& Map<K, V>::operator[](const K& key) {
  Node*& n = find(root_, key);
  if(n == nullptr) {
    n = new Node{key};
    ++size_;
  }
  return n->value_;
}

template<typename K, typename V>
typename Map<K, V>::Node*& Map<K, V>::find(Node*& n, const K& key) {
  if(n == nullptr || n->key_ == key) return n;
  if(key < n->key_) return find(n->left, key);
  return find(n->right, key);
}

template<typename K, typename V>
template <typename F>
Map<K, V>& Map<K, V>::insert(const K& key, F&& val) {
  Node*& n = find(root_, key);
  if(n == nullptr) {
    n = new Node{key, std::forward<F>(val)};
    ++size_;
  }
  else
    throw std::out_of_range("Kljuc vec postoji");
  return *this;
}

template<typename K, typename V>
bool Map<K, V>::erase(const K& key) {
  Node*& n = find(root_, key);
  if(n == nullptr) {
    return false;
  }
  if(n->left == nullptr || n->right == nullptr)
    erase(n);
  else {
    Node*& iop = getIOP(n);
    std::swap(n, iop);
    erase(iop);
  }

  return true;
}


template<typename K, typename V>
void Map<K, V>::erase(Node* n) {
  Node*& p = getParent(root_, n);
  if(n->left == nullptr) {
    if(p == nullptr)
      root_ = n->right;
    else {
      if(p->left == n)
        p->left = n->right;
      else
        p->right = n->right;
    }
  }
  else if(n->right == nullptr) {
    if(p == nullptr)
      root_ = n->left;
    else {
      if(p->left == n)
        p->left = n->left;
      else
        p->right = n->left;
    }
  }
  delete n;
  --size_;
}

template<typename K, typename V>
typename Map<K, V>::Node*& Map<K, V>::getParent(Node*& curr, Node* n) {
  if(curr == nullptr) return curr;
  if(curr->left == n || curr->right == n) return curr;
  Node*& x = getParent(curr->left, n);
  if(x == nullptr)
    x = getParent(curr->right, n);
  return x;
}

template<typename K, typename V>
typename Map<K, V>::Node*& Map<K, V>::getIOP(Node* n) {
  Node*& x = n->left;
  while(x->right != nullptr)
    x = x->right;
  return x;
}

template<typename K, typename V>
void Map<K, V>::clear() {
  destroy(root_);
}

template<typename K, typename V>
template<typename F>
void Map<K, V>::inorder(F func) const {
  inorder(root_, func);
}

template<typename K, typename V>
template<typename F>
void Map<K, V>::inorder(Node* n, F func) const {
  if(n == nullptr) return;
  inorder(n->left, func);
  func(n->key_, n->value_);
  inorder(n->right, func);
}
