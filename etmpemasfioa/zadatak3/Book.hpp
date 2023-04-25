// Vas kod ovdje
#pragma once
#include <string>
#include <iostream>

class Book {
  private:
    std::string title;
    std::string author;
    std::string publisher;
    int pYear;
    int numOfCopies;
  public:
    Book() {};
    Book(const std::string&, const std::string&, const std::string&, int, int);
    Book(const Book&);
    Book(Book&&);
    Book& operator=(const Book&);
    Book& operator=(Book&&);
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getPublisher() const;
    int getPublishingYear() const;
    const int& getNumOfCopies() const;
    int& getNumOfCopies();
    bool operator==(const Book&) const;
};

std::ostream& operator<<(std::ostream&, const Book&);
