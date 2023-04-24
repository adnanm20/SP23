// Vas kod ovdje
#include "Library.hpp"
#include <iostream>

Library::Library() : books_{}, users_{}, borrowedBooks_{} {}
Library::Library(const std::vector<Book>& b) : books_{b}, users_{}, borrowedBooks_{}  {}
Library::Library(const std::vector<User>& u) : books_{}, users_{u}, borrowedBooks_{}  {}
Library::Library(const std::vector<Book>& b, const std::vector<User>& u) : books_{b}, users_{u}, borrowedBooks_{}  {}
Library::Library(const Library& o) : books_{o.books_}, users_{o.users_}, borrowedBooks_{o.borrowedBooks_} {}
Library::Library(Library&& o) : books_{std::move(o.books_)}, users_{std::move(o.users_)}, borrowedBooks_{std::move(o.borrowedBooks_)}  {}
Library& Library::operator=(const Library& o) {
  books_ = o.books_;
  users_ = o.users_;
  borrowedBooks_ = o.borrowedBooks_;
  return *this;
}
Library& Library::operator=(Library&& o) {
  books_ = std::move(o.books_);
  users_ = std::move(o.users_);
  borrowedBooks_ = std::move(o.borrowedBooks_);
  return *this;
}

bool Library::addUser() {
  std::string fName, lName;
  int id;
  std::cout << "First Name: ";
  std::cin >> fName;
  std::cout << "First Name: ";
  std::cin >> lName;
  std::cout << "User ID: ";
  std::cin >> id;

  auto s = users_.begin();
  while(s != users_.end()) {
    if((*s).getUserId() == id)
      break;
  }
  
  if(s != users_.end()) {
    std::cout << "User with id {" << id << "} already exists!" << std::endl;
    return 0;
  }

  users_.push_back(User(fName, lName, id));
  return 1;

}

bool Library::addBook() {
  std::string title, author, publisher;
  int publishingYear, numOfCopies;
  std::cout << "Title: ";
  std::cin.ignore(999999, '\n');
  getline(std::cin, title);
  std::cout << "Author: ";
  getline(std::cin, author);
  std::cout << "Publisher: ";
  getline(std::cin, publisher);
  std::cout << "Publication year: ";
  std::cin >> publishingYear;
  std::cout << "Number of copies: ";
  std::cin >> numOfCopies;

  Book newBook{title, author, publisher, publishingYear, numOfCopies};
  auto s = books_.begin();
  while(s != books_.end()) {
    if((*s) == newBook)
      break;
  }
  
  if(s != books_.end()) {
    std::cout << "Book already exists!" << std::endl;
    return 0;
  }

  books_.push_back(newBook);
  return 1;
}
bool Library::borrowBook() {
  int uID;
  std::string bookTitle;
  std::cout << "User ID: ";
  std::cin >> uID;
  std::cout << "Book title: ";
  std::cin >> bookTitle;
  auto bookIt = books_.begin();
  while(bookIt != books_.end()) {
    if((*bookIt).getTitle() == bookTitle)
      break;
  }
  
  if(bookIt == books_.end()) {
    std::cout << "Book \"" << bookTitle << "\" doesn't exist!" << std::endl; 
    return 0;
  }
  auto userIt = users_.begin();
  while(userIt != users_.end()) {
    if((*userIt).getUserId() == uID)
      break;
  }
  
  if(userIt == users_.end()) {
    std::cout << "User with id {" << uID << "} doesn't exist!" << std::endl;
    return 0;
  }
  --(*bookIt).getNumOfCopies();

  borrowedBooks_.push_back(std::pair<std::vector<User>::iterator, std::vector<Book>::iterator>(userIt, bookIt));
  return 1;
}
bool Library::returnBook() {
  int uID;
  std::string bookTitle;
  std::cout << "User ID: ";
  std::cin >> uID;
  std::cout << "Book title: ";
  std::cin >> bookTitle;
  auto bookIt = books_.begin();
  while(bookIt != books_.end()) {
    if((*bookIt).getTitle() == bookTitle)
      break;
  }
  
  auto userIt = users_.begin();
  while(userIt != users_.end()) {
    if((*userIt).getUserId() == uID)
      break;
  }
  
  auto borrowedBookIt = borrowedBooks_.begin();
  while(borrowedBookIt != borrowedBooks_.end()) {
    if((*borrowedBookIt).first == userIt && (*borrowedBookIt).second == bookIt)
      break;
  }
  
  if(borrowedBookIt == borrowedBooks_.end()) {
    std::cout << "Book \"" << bookTitle << "\" is not borrowed by user with id {" << uID << "}!" << std::endl;
    return 0;
  }

  ++(*bookIt).getNumOfCopies();
  borrowedBooks_.erase(borrowedBookIt);
  return 1;
}

std::vector<Book> Library::searchBookByTitle(const std::string& title) const {
  std::vector<Book> ret;
  for(auto it = books_.begin(); it != books_.end(); ++it)
    if((*it).getTitle() == title)
      ret.push_back(*it);
  return ret;
}
std::vector<Book> Library::searchBookByAuthor(const std::string& author) const {
  std::vector<Book> ret;
  for(auto it = books_.begin(); it != books_.end(); ++it)
    if((*it).getAuthor() == author)
      ret.push_back(*it);
  return ret;
}
std::vector<Book> Library::searchBookByPublisher(const std::string& publisher) const {
  std::vector<Book> ret;
  for(auto it = books_.begin(); it != books_.end(); ++it)
    if((*it).getPublisher() == publisher)
      ret.push_back(*it);
  return ret;
}
std::vector<Book> Library::searchBookByPublicationYear(int publishingYear) const {
  std::vector<Book> ret;
  for(auto it = books_.begin(); it != books_.end(); ++it)
    if((*it).getPublishingYear() == publishingYear)
      ret.push_back(*it);
  return ret;
}
