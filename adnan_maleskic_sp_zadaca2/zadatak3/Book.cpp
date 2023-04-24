// Vas kod ovdje

#include "Book.hpp"

Book::Book(const std::string& t, const std::string& a, const std::string& p, int pY, int c) :
  title{t}, author{a}, publisher{p}, pYear{pY}, numOfCopies{c} {}

Book::Book(const Book& o) :  
  title{o.title}, author{o.author}, publisher{o.publisher}, pYear{o.pYear}, numOfCopies{o.numOfCopies} {}
Book::Book(Book&& o) :
  title{o.title}, author{o.author}, publisher{o.publisher}, pYear{o.pYear}, numOfCopies{o.numOfCopies} {}
Book& Book::operator=(const Book& o) {
  title = o.title;
  author = o.author;
  publisher = o.publisher;
  pYear = o.pYear;
  numOfCopies = o.numOfCopies;
  return *this;
}
Book& Book::operator=(Book&& o) {
  title = o.title;
  author = o.author;
  publisher = o.publisher;
  pYear = o.pYear;
  numOfCopies = o.numOfCopies;
  return *this;
}

std::string Book::getTitle() const {return title;}
std::string Book::getAuthor() const {return author;}
std::string Book::getPublisher() const {return publisher;}
int Book::getPublishingYear() const {return pYear;}
const int& Book::getNumOfCopies() const {return numOfCopies;}
int& Book::getNumOfCopies() {return numOfCopies;}

bool Book::operator==(const Book& o) const {
  return 
    title == o.getTitle() && 
    author == o.getAuthor() &&
    publisher == o.getPublisher() &&
    pYear == o.getPublishingYear() &&
    numOfCopies == o.getNumOfCopies();
}

std::ostream& operator<<(std::ostream& o, const Book& b) {
  return o << "Title: " << b.getTitle() << '\n'
    << "Author: " << b.getAuthor() << '\n'
    << "Publisher: " << b.getPublisher() << '\n'
    << "Publication year: " << b.getPublishingYear() << '\n'
    << "Number of copies: " << b.getNumOfCopies()
    << std::endl;
}
