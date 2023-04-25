// Vas kod ovdje
#pragma once
#include <vector>
#include "Book.hpp"
#include "User.hpp"


class Library {
  private:
    std::vector<Book> books_;
    std::vector<User> users_;
    std::vector<std::pair<std::vector<User>::iterator, std::vector<Book>::iterator>> borrowedBooks_;
  public:
    Library();
    Library(const std::vector<Book>&);
    Library(const std::vector<User>&);
    Library(const std::vector<Book>&, const std::vector<User>&);
    Library(const Library&);
    Library(Library&&);
    Library& operator=(const Library&);
    Library& operator=(Library&&);
    bool addUser();
    bool addBook();
    bool borrowBook();
    bool returnBook();
    std::vector<Book> searchBookByTitle(const std::string&) const;
    std::vector<Book> searchBookByAuthor(const std::string&) const;
    std::vector<Book> searchBookByPublisher(const std::string&) const;
    std::vector<Book> searchBookByPublicationYear(int) const;
};
