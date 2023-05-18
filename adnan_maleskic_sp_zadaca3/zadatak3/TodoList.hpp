#pragma once

#include "../zadatak1/DoubleLinkedList.hpp"
#include "Zadatak.hpp"
#include <string>
#include <list>

class TodoList {
  public:
    TodoList();
    TodoList(const TodoList&);
    TodoList(TodoList&&);
    TodoList& operator=(const TodoList&);
    TodoList& operator=(TodoList&&);
    ~TodoList();

    bool addTask(const Zadatak&);
    bool startTask(std::string);
    bool endTask(std::string);
    bool removeTask(std::string);
    bool editTask(std::string);
    void printAllTasks();
    void printWaitingTasks();
    void printStartedTasks();
    void printFinishedTasks();
  
  private:
    std::list<Zadatak> tasks;
    unsigned int lastCompleteCount = 0;
};
