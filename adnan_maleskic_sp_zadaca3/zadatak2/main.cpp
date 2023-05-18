#include "TodoList.hpp"
#include "Zadatak.hpp"
#include <iostream>
#include <string>

void printOptions() {
  std::cout << 
  "1. addTask\n"
  "2. printAllTasks\n"
  "3. printWaitingTasks\n"
  "4. printStartedTasks\n"
  "5. printFinishedTasks\n"
  "6. startTask\n"
  "7. endTask\n"
  "8. removeTask\n"
  "9. editTask\n"
  "10. exit"
  << std::endl;
}

int main(void)
{
  TodoList todoList;

  std::string inputString;
  while(1) {
    printOptions();
    std::cin >> inputString;
    if(inputString == "addTask" || inputString == "1") {
      Zadatak newTask;
      std::cout << "Id: " << newTask.id() << '\n'; 
      std::cout << "Name: ";
      std::cin.ignore(9999, '\n');
      getline(std::cin, newTask.name());
      std::cout <<"Description: ";
      getline(std::cin, newTask.description());
      std::cout <<"Priority: ";
      std::cin >> newTask.priority();
      std::string temp;
      std::cout << "Status(\"Waiting\"/\"Started\"/\"Ended\"): ";
      std::cin >> temp;
      if(temp == "Waiting") newTask.status() = 1;
      else if(temp == "Started") newTask.status() = 2;
      else if(temp == "Ended") newTask.status() = 3;
      if(todoList.addTask(newTask))
        std::cout << "Task succesfully added!" << std::endl;
    } else if(inputString == "printAllTasks" || inputString == "2") {
      todoList.printAllTasks();
    } else if(inputString == "printWaitingTasks" || inputString == "3") {
      todoList.printWaitingTasks();
    } else if(inputString == "printStartedTasks" || inputString == "4") {
      todoList.printStartedTasks();
    } else if(inputString == "printFinishedTasks" || inputString == "5") {
      todoList.printFinishedTasks();
    } else if(inputString == "startTask" || inputString == "6") {
      std::string temp;
      std::cout << "Id of task to start: ";
      std::cin >> temp;
      todoList.startTask(temp);
    } else if(inputString == "endTask" || inputString == "7") {
      std::string temp;
      std::cout << "Id of task to end: ";
      std::cin >> temp;
      todoList.endTask(temp);
    } else if(inputString == "removeTask" || inputString == "8") {
      std::string temp;
      std::cout << "Id of task to remove: ";
      std::cin >> temp;
      todoList.removeTask(temp);
    } else if(inputString == "editTask" || inputString == "9") {
      std::string temp;
      std::cout << "Id of task to edit: ";
      std::cin >> temp;
      todoList.editTask(temp);
    } else if(inputString == "exit" || inputString == "10") {
      break;
    }
  }




  return 0;
}
