#pragma once

#include <iostream>
template <typename T>
struct Node {
  Node* left{nullptr};
  Node* right{nullptr};
  T data;
  Node(T& element) : data{element} {}
  Node(T&& element) : data{std::move(element)} {}
};

template <typename T>
class BST {
  public:
  BST() = default;
  BST(const BST& bst) { copy(root_, bst.root_); }
  BST(BST&& bst) : root_{bst.root_} { bst.root_ = nullptr; }
  BST& operator=(BST&& bst) {
    destroy(root_);
    root_ = bst.root_;
    bst.root_ = nullptr;
    return *this;
  }
  BST& operator=(const BST& bst) {
    if (&bst != this) {
      destroy(root_);
      copy(root_, bst.root_);
    }
    return *this;
  }
  ~BST() { destroy(root_); }

  template <typename U>
  BST& add(U&& element) {
    return add(element, root_);
  }

  void preorder() const {
    std::cout << "[";
    preorder(root_);
    std::cout << "]" << std::endl;
  }
  void inorder() const {
    std::cout << "[";
    inorder(root_);
    std::cout << "]" << std::endl;
  }
  void postorder() const {
    std::cout << "[";
    postorder(root_);
    std::cout << "]" << std::endl;
  }
  Node<T>* search(const T& element) { return (search(root_, element)); }

  private:
  Node<T>* root_{nullptr};

  template <typename U>
  BST& add(U&& element, Node<T>*& root) {
    if(root == nullptr) {
      root = new Node<T>{std::forward<U>(element)};
      return *this;
    }
    if(element > root->data)
      return add(element, root->right);
    else
      return add(element, root->left);
  }

  Node<T>* search(Node<T>* node, const T& element) {
    if(node == nullptr || node->data == element) return node;
    if(element > node->data)
      return search(node->right, element);
    return search(node->left, element);
  }

  void preorder(const Node<T>* const current) const {
    if(current == nullptr) return;
    std::cout << current->data << ' ';
    preorder(current->left);
    preorder(current->right);
  }

  void inorder(const Node<T>* const current) const {
    if(current == nullptr) return;
    inorder(current->left);
    std::cout << current->data << ' ';
    inorder(current->right);
  }

  void postorder(const Node<T>* const current) const {
    if(current == nullptr) return;
    postorder(current->left);
    postorder(current->right);
    std::cout << current->data << ' ';
  }

  void destroy(Node<T>* node) {
    if(node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  void copy(Node<T>*& dest, Node<T>* source) {
    if(source == nullptr) return;
    dest = new Node<T>{source->data};
    copy(dest->left, source->left);
    copy(dest->right, source->right);
  }
};
