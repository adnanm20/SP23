#include "MojVektor.hpp"
#include <iostream>

// Vector implementation

MojVektor::MojVektor(): capacity_{10}, size_{0}, arr_{new int [capacity_]}{}

MojVektor::MojVektor(const std::initializer_list<int>& iL) : capacity_{iL.size()}, size_{iL.size()}, arr_{new int[capacity_]}{
  std::copy(iL.begin(), iL.end(), arr_);
}

MojVektor::MojVektor(const MojVektor& oV): capacity_{oV.capacity_}, size_{oV.size_}, arr_{new int[capacity_]}{
  std::copy(oV.arr_, oV.arr_ + size_, arr_);
}

MojVektor& MojVektor::operator=(const MojVektor& oV){
  delete [] arr_;
  capacity_ = oV.capacity_;
  size_ = oV.size_;
  arr_ = new int [capacity_];
  std::copy(oV.arr_, oV.arr_ + size_, arr_);

  return *this;
}

MojVektor::MojVektor(MojVektor&& oV): capacity_{oV.capacity_}, size_{oV.size_}, arr_{oV.arr_}{
  oV.capacity_ = 0;
  oV.size_ = 0;
  oV.arr_ = nullptr;
}

MojVektor& MojVektor::operator=(MojVektor&& oV){
  delete [] arr_;
  capacity_ = oV.capacity_;
  size_ = oV.size_;
  arr_ = oV.arr_;

  oV.capacity_ = 0;
  oV.size_ = 0;
  oV.arr_ = nullptr;

  return *this;
}

MojVektor::~MojVektor(){
  capacity_ = 0;
  size_ = 0;
  delete [] arr_;
  arr_ = nullptr;
}

MojVektor& MojVektor::push_back(int el){
  if(size_ == capacity_)
    realoc();

  arr_[size_++] = el;
  return *this;
}

MojVektor& MojVektor::push_front(int el){
  if(size_ == capacity_)
    capacity_ *= 2;

  int* newArr = new int [capacity_];
  newArr[0] = el;
  std::copy(arr_, arr_ + size_, newArr + 1);
  arr_ = newArr;
  ++size_;

  return *this;
}

size_t MojVektor::size() const{
  return size_;
}

int& MojVektor::at(size_t i) const{
  if(i >= size_)
    throw std::out_of_range{"Index out of range"};

  return arr_[i];
}

int& MojVektor::operator[](size_t i) const{
  return arr_[i];
}

void MojVektor::clear(){
  delete [] arr_;
  capacity_ = 0;
  size_ = 0;
  arr_ = nullptr;
}

void MojVektor::resize(size_t nC){
  int* tmpArr = new int [nC];
  if(nC < size_)
    size_ = nC;
  std::copy(arr_, arr_ + size_, tmpArr);
  delete [] arr_;
  capacity_ = nC;
  arr_ = tmpArr;
}

MojVektor& MojVektor::pop_back(){
  if(empty())
    throw std::out_of_range{"No elements"};

  --size_;
  return *this;
}

MojVektor& MojVektor::pop_front(){
  if(empty())
    throw std::out_of_range{"No elements"};

  std::copy(arr_ + 1, arr_ + size_, arr_);
  --size_;

  return *this;
}

int& MojVektor::back() const{
  if(empty())
    throw std::out_of_range{"No elements"};

  return arr_[size_ - 1];
}

int& MojVektor::front() const{
  if(empty())
    throw std::out_of_range{"No elements"};

  return arr_[size_ - 1];
}

bool MojVektor::empty() const{
  return size_ == 0;
}

size_t MojVektor::capacity() const{
  return capacity_;
}

bool MojVektor::operator==(const MojVektor& oV) const{
  if(size_ != oV.size_)
    return false;

  for(size_t i = 0; i < size_; ++i)
    if(arr_[i] != oV[i])
      return false;

  return true;
}

bool MojVektor::operator!=(const MojVektor& oV) const{
  return !(*this == oV);
}

int* MojVektor::data(){
  return arr_;
}

void MojVektor::realoc(){
  int* tmpArr = new int [capacity_ * 2];
  std::copy(arr_, arr_ + size_, tmpArr);
  delete [] arr_;
  capacity_ *= 2;
  arr_ = tmpArr;
}

// Standalone funcs

std::ostream& operator<<(std::ostream& out, const MojVektor& mV){
  std::string outString {"{"};

  for(size_t i = 0; i < mV.size(); ++i)
    outString += (std::to_string(mV[i]) + ", ");

  if(!mV.empty()){
    outString.pop_back();
    outString.pop_back();
  }

  outString.push_back('}');
  out << outString;

  return out;
}

// Iterator implementation

MojVektor::Iterator::Iterator(int* p) : ptr_{p} {}

int& MojVektor::Iterator::operator*() {
  return *ptr_;
}

MojVektor::Iterator& MojVektor::Iterator::operator++() {
  ++ptr_;
  return *this;
}

MojVektor::Iterator MojVektor::Iterator::operator++(int) {
  Iterator it = Iterator(ptr_);
  ++ptr_;
  return it;
}

MojVektor::Iterator& MojVektor::Iterator::operator--() {
  --ptr_;
  return *this;
}

MojVektor::Iterator MojVektor::Iterator::operator--(int) {
  Iterator it = Iterator(ptr_);
  --ptr_;
  return it;
}

MojVektor::Iterator MojVektor::Iterator::operator+(int n) {
  Iterator it = Iterator{ptr_ + n};
  return it;
}

MojVektor::Iterator MojVektor::Iterator::operator-(int n) {
  Iterator it = Iterator{ptr_ - n};
  return it;
}

bool MojVektor::Iterator::operator<(const Iterator& oI) {
  return ptr_ < oI.ptr_;
}

bool MojVektor::Iterator::operator>(const Iterator& oI) {
  return ptr_ > oI.ptr_;
}

bool MojVektor::Iterator::operator<=(const Iterator& oI) {
  return ptr_ <= oI.ptr_;
}

bool MojVektor::Iterator::operator>=(const Iterator& oI) {
  return ptr_ >= oI.ptr_;
}

bool MojVektor::Iterator::operator==(const MojVektor::Iterator& oI) {
  return ptr_ == oI.ptr_;
}

bool MojVektor::Iterator::operator!=(const MojVektor::Iterator& oI) {
  return ptr_ != oI.ptr_;
}

size_t MojVektor::Iterator::operator-(const Iterator& oI) {
  return ptr_ - oI.ptr_;
}

// Methods using iterators

MojVektor::Iterator MojVektor::begin() const {
  return Iterator{arr_};
}

MojVektor::Iterator MojVektor::end() const {
  return Iterator{arr_ + size_};
}

MojVektor::Iterator MojVektor::find(int value) const {
  for(int i = 0; i < size_; ++i)
    if(arr_[i] == value)
      return Iterator{arr_ + i};
  return end();
}

MojVektor::Iterator MojVektor::erase(Iterator pos) {
  Iterator it = pos + 1;
  while(it < end())
  {
    *(it - 1) = *it;
    ++it;
  }
  // std::copy(pos+1, end(), pos);
  --size_;
  return pos;
}

MojVektor::Iterator MojVektor::insert(Iterator pos, int value) {
  if(size_ == capacity_) {
    size_t posI = pos - begin();
    realoc();
    pos = Iterator{arr_ + posI};
  }

  Iterator it = end();
 
  while(it > pos)
  {
    *it = *(it - 1);
    --it;
  }
  ++size_;
  *pos = value;
  return pos;
}

MojVektor::Iterator MojVektor::erase(Iterator bPos, Iterator ePos) {
  while(bPos != ePos)
  {
    bPos = erase(bPos);
    --ePos;
  }
  return bPos;
}

