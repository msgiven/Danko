#include <Windows.h>
#include <fcntl.h>
#include <io.h>

#include <ios>
#include <iostream>
#include <limits>

#include "global_void.h"

// Простая функция вывода
void Print(const std::string& message) {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  // std::locale::global(std::locale("Russian"));
  std::cout << message << std::endl;
}
int GetValidIntegerInput() {
  int value;
  while (true) {
    std::cin >> value;

    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
      std::cout << "Ошибка: введите корректное число.\n";
    } else {
      break;
    }
  }
  return value;
}
