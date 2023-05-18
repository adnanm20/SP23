#include "TodoList.hpp"
#include <algorithm>
#include <list>
#include <iterator>
#define taskWait 1
#define taskStart 2
#define taskEnd 3
TodoList::TodoList() = default;
TodoList::TodoList(const TodoList&) = default;
TodoList::TodoList(TodoList&& o) : tasks{std::move(o.tasks)}, lastCompleteCount{o.lastCompleteCount} {}
TodoList& TodoList::operator=(const TodoList&) = default;
TodoList& TodoList::operator=(TodoList&& o) {tasks = std::move(o.tasks); lastCompleteCount = o.lastCompleteCount; return *this;}
TodoList::~TodoList() = default;

bool TodoList::addTask(const Zadatak& zadatak) {
  tasks.push_back(zadatak);
  return true;
}
bool TodoList::startTask(std::string taskId) {
  auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Zadatak& z) {return z.id() == taskId;});
  if(it != tasks.end()) {
    it->status() = taskStart;
    return true;
  } else {
    std::cout << "Task not found!" << std::endl;
    return false;
  }
}
bool TodoList::endTask(std::string taskId) {
  auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Zadatak& z) {return z.id() == taskId;});
  if(it != tasks.end()) {
    it->status() = taskEnd;
    it->completionId() = ++lastCompleteCount;
    return true;
  } else {
    std::cout << "Task not found!" << std::endl;
    return false;
  }
}
bool TodoList::removeTask(std::string taskId) {
  auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Zadatak& z) {return z.id() == taskId;});
  if(it != tasks.end()) {
    tasks.erase(it);
    return true;
  } else {
    std::cout << "Task not found!" << std::endl;
    return false;
  }
}
bool TodoList::editTask(std::string taskId) {
  auto it = std::find_if(tasks.begin(), tasks.end(), [taskId](const Zadatak& z) {return z.id() == taskId;});
  if(it != tasks.end()) {
    it->edit();
    return true;
  } else {
    std::cout << "Task not found!" << std::endl;
    return false;
  }
}
void TodoList::printAllTasks() {
  tasks.sort([](const Zadatak& a, const Zadatak& b) { return a.priority() < b.priority(); });
  std::cout << "-------------------------------------------" << std::endl;
  for(auto it = tasks.begin(); it != tasks.end(); ++it)
    std::cout << *it << std::endl;
  std::cout << "-------------------------------------------" << std::endl;
}
void TodoList::printWaitingTasks() {
  std::list<Zadatak> temp;
  std::copy_if(tasks.begin(), tasks.end(), back_inserter(temp), [](const Zadatak& z){return z.status() == taskWait;});
  temp.sort([](const Zadatak& a, const Zadatak& b) { return a.priority() < b.priority(); });
  std::cout << "-------------------------------------------" << std::endl;
  for(auto it = temp.begin(); it != temp.end(); ++it)
    std::cout << *it << std::endl;
  std::cout << "-------------------------------------------" << std::endl;
}
void TodoList::printStartedTasks() {
  std::list<Zadatak> temp;
  std::copy_if(tasks.begin(), tasks.end(), back_inserter(temp), [](const Zadatak& z){return z.status() == taskStart;});
  temp.sort([](const Zadatak& a, const Zadatak& b) { return a.priority() < b.priority(); });
  std::cout << "-------------------------------------------" << std::endl;
  for(auto it = temp.begin(); it != temp.end(); ++it)
    std::cout << *it << std::endl;
  std::cout << "-------------------------------------------" << std::endl;
}
void TodoList::printFinishedTasks() {
  std::list<Zadatak> temp;
  std::copy_if(tasks.begin(), tasks.end(), back_inserter(temp), [](const Zadatak& z){return z.status() == taskEnd;});
  temp.sort([](const Zadatak& a, const Zadatak& b) { return a.completionId() > b.completionId();});
  std::cout << "-------------------------------------------" << std::endl;
  for(auto it = temp.begin(); it != temp.end(); ++it)
    std::cout << *it << std::endl;
  std::cout << "-------------------------------------------" << std::endl;
}

