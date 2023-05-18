#include<iostream>

template<typename T>
class Stack {
  public:
    template<typename U>
    friend std::ostream& operator<<(std::ostream&, const Stack<U>&);
    Stack();
    Stack(const Stack<T>&);
    Stack(Stack<T>&&);
    Stack& operator=(const Stack<T>&);
    Stack& operator=(Stack<T>&&);
    ~Stack();

    Stack& push(const T&);
    void pop();
    T& top();
    bool empty();


  private:
    size_t size_;
    size_t capacity_;
    T* elements_;
};

template<typename T>
Stack<T>::Stack() : size_{0}, capacity_{10}, elements_{new T[capacity_]} {}

template<typename T>
Stack<T>::Stack(const Stack<T>& o) : size_{o.size_}, capacity_{o.capacity_}, elements_{new T[capacity_]} {
  std::copy(o.elements_, o.elements_+o.size_, elements_);
}

template<typename T>
Stack<T>::Stack(Stack<T>&& o) : size_{o.size_}, capacity_{o.capacity_}, elements_{o.elements_} {
  o.elements_ = nullptr;
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack<T>& o) {
  delete[] elements_;
  size_ = o.size_;
  capacity_ = o.capacity_;
  elements_ = new T[size_];
  std::copy(o.elements_, o.elements_+o.size_, elements_);
}

template<typename T>
Stack<T>& Stack<T>::operator=(Stack<T>&& o) {
  delete[] elements_;
  size_ = o.size_;
  capacity_ = o.capacity_;
  elements_ = o.elements_;
  o.elements_ = nullptr;
}

template<typename T>
Stack<T>::~Stack() {
  delete[] elements_;
}

template<typename T>
Stack<T>& Stack<T>::push(const T& val) {
  if(size_ == capacity_) {
    capacity_ *= 2;
    T* newEl = new T[capacity_];
    std::copy(elements_, elements_ + size_, newEl);
    delete[] elements_;
    elements_ = newEl;
  }

  elements_[size_] = std::move(val);
  ++size_;
  return *this;
}

template<typename T>
void Stack<T>::pop() {
  if(size_ == 0) throw std::out_of_range("Stack is empty!");
  --size_;
}

template<typename T>
T& Stack<T>::top() {
  if(size_ == 0) throw std::out_of_range("Stack is empty!");
  return elements_[size_-1];
}

template<typename T>
bool Stack<T>::empty() {
  return size_ == 0;
}

template<typename T>
std::ostream& operator<<(std::ostream& o, const Stack<T>& s) {
  for(size_t i = 0; i < s.size_; ++i)
    o << s.elements_[i] << " ";
  return o;
}
