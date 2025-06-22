#include "global_void.h"

#include <Windows.h>
#include <fcntl.h>
#include <io.h>

#include <chrono>
#include <ios>
#include <iostream>
#include <limits>
#include <string>
#include <thread>

// Простая функция вывода
void PrintD(const std::string& message) { std::cout << message << std::endl; }
void Print(const std::string& text) {
  for (const char c : text) {
    std::cout << c << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
  }
}
void ClearConsole() {
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD coordScreen = {0, 0};
  DWORD cCharsWritten;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD dwConSize;

  // Получаем размер буфера консоли
  GetConsoleScreenBufferInfo(hConsole, &csbi);
  dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

  // Заполняем консоль пробелами
  FillConsoleOutputCharacter(hConsole, ' ', dwConSize, coordScreen,
                             &cCharsWritten);

  // Устанавливаем атрибуты (цвета) текста
  FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen,
                             &cCharsWritten);

  // Перемещаем курсор в начало
  SetConsoleCursorPosition(hConsole, coordScreen);
}
