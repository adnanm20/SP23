#include <iostream>
#include "Library.hpp"
#include "Book.hpp"
#include "User.hpp"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void lines() {
  cout << string(50, '-') << endl;
}

void doubleLines() {
  cout << string(50, '=') << endl;
}

void dots() {
  cout << string(50, '.') << endl;
}

void help() {
  lines();
  cout << "List of commands" << endl;
  doubleLines();
  cout << "CreateUser" << endl;
  cout << "BookAdd" << endl;
  cout << "BookBorrow" << endl;
  cout << "BookReturn" << endl;
  cout << "BookSearchByTitle" << endl;
  cout << "BookSearchByAuthor" << endl;
  cout << "BookSearchByPublisher" << endl;
  cout << "BookSearchByPublicationYear" << endl;
  cout << "Help" << endl;
  cout << "Exit" << endl;
  lines();
}

void intro() {
  doubleLines();
  cout << "Univesity of Tuzla" << endl;
  cout << "Faculty of Electrical Engineering" << endl << endl;
  cout << "Library application" << endl;
  cout << "Version: April 2023" << endl << endl;
  doubleLines();
}

template<typename T>
std::ostream& operator<<(std::ostream& o, std::vector<T> s) {
  for(auto it = s.begin(); it != s.end(); ++it)
    o << *it;
  return o;
}

int main(void)
{
  std::string command;
  Library library;

  intro();
  help();

  while(1) {
    dots();
    cout << "Command: ";
    cin >> command;
    dots();
    if(command == "CreateUser") library.addUser();
    else if(command == "BookAdd") library.addBook();
    else if(command == "BookBorrow") library.borrowBook();
    else if(command == "BookReturn") library.returnBook();
    else if(command == "BookSearchByTitle") {
      string bookTitle;
      cout << "Title: ";
      cin.ignore(999999, '\n');
      getline(cin, bookTitle);
      auto book = library.searchBookByTitle(bookTitle);
      lines();
      if(book.empty()) cout << "No books found!" << endl;
      else cout << book << endl;
      lines();
    }
    else if(command == "BookSearchByAuthor") {
      string bookAuthor;
      cout << "Author: ";
      cin.ignore(999999, '\n');
      getline(cin, bookAuthor);
      auto book = library.searchBookByAuthor(bookAuthor);
      lines();
      if(book.empty()) cout << "No books found!" << endl;
      else cout << book << endl;
      lines();
    }
    else if(command == "BookSearchByPublisher") {
      string bookPublisher;
      cout << "Publisher: ";
      cin.ignore(999999, '\n');
      getline(cin, bookPublisher);
      auto book = library.searchBookByPublisher(bookPublisher);
      lines();
      if(book.empty()) cout << "No books found!" << endl;
      else cout << book << endl;
      lines();
    }
    else if(command == "BookSearchByPublicationYear") {
      int bookPublicationYear;
      cout << "Publication year: ";
      cin >> bookPublicationYear;
      auto book = library.searchBookByPublicationYear(bookPublicationYear);
      lines();
      if(book.empty()) cout << "No books found!" << endl;
      else cout << book << endl;
      lines();
    }
    else if(command == "Help") help();
    else if(command == "Exit") break;
    else {
      cout << "Invalid command. Please try again." << endl;
    }
  }
  
  return 0;
}
