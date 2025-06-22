#ifndef ITEM_GAME_H_
#define ITEM_GAME_H_

#include <iostream>

#include "player.h"
class ItemGame {
 public:
  ItemGame(Player& player);
  bool Start();

 private:
  Player& player_;
  static const int width_ = 10;
  static const int height_ = 7;
  static const int levels_ = 5;

  char maps[levels_][height_][width_ + 1] = {
      {"##########", "#.*......#", "#.####.#.#", "#....#.#.#", "##.#.#.#.#",
       "#....#...X", "##########"},
      {"##########", "#*.......#", "#.###.##.#", "#.#......#", "#.#.###..#",
       "#...#....X", "##########"},
      {"##########", "#....#...#", "#.##.#.#.#", "#..#.#.#.#", "#.##.#.#.#",
       "#*.....#X#", "##########"},
      {"##########", "#.###....#", "#...#.#..#", "#.#.#.#.##", "#.#...#..#",
       "#.*###..X#", "##########"},
      {"##########", "#*.......#", "#.#.##.#.#", "#.#....#.#", "#.####.#.#",
       "#......#X#", "##########"}};

  int px = 1, py = 1;
  char (*map)[width_ + 1];

  void FindPlayerPosition();
  void DrawMap();
  bool MovePlayer(char dir);
};
#endif
