#include "item_game.h"

#include <conio.h>

#include <cctype>
#include <cstdlib>
#include <ctime>

#include "global_void.h"

ItemGame::ItemGame(Player& player) : player_(player) {
  srand(static_cast<unsigned>(time(NULL)));
  int idx = rand() % levels_;
  map = maps[idx];
  FindPlayerPosition();
}

void ItemGame::FindPlayerPosition() {
  for (int y = 0; y < height_; ++y) {
    for (int x = 0; x < width_; ++x) {
      if (map[y][x] == '*') {
        px = x;
        py = y;
        return;
      }
    }
  }
}

void ItemGame::DrawMap() {
  ClearConsole();
  for (int y = 0; y < height_; ++y) {
    std::cout << map[y] << "\n";
  }
  std::cout
      << "\nУправление: W A S D. Пройди путь сквозь тьму до выхода (X)!\n";
}

bool ItemGame::MovePlayer(char dir) {
  int dx = 0, dy = 0;
  switch (dir) {
    case 'W':
      dy = -1;
      break;
    case 'S':
      dy = 1;
      break;
    case 'A':
      dx = -1;
      break;
    case 'D':
      dx = 1;
      break;
  }

  int nx = px + dx;
  int ny = py + dy;

  if (map[ny][nx] == '#') {
    player_.ChangeHealth(-5);
    return false;
  } else if (map[ny][nx] == 'X') {
    map[py][px] = '.';
    map[ny][nx] = '*';
    DrawMap();
    return true;
  }

  map[py][px] = '.';
  map[ny][nx] = '*';
  px = nx;
  py = ny;

  return false;
}

bool ItemGame::Start() {
  DrawMap();
  while (true) {
    char input = toupper(_getch());
    if (input == 'W' || input == 'A' || input == 'S' || input == 'D') {
      bool success = MovePlayer(input);
      DrawMap();
      if (success) return true;
    }
  }
  return false;
}
