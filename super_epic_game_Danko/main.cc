#include <Windows.h>

#include <iostream>
#include <locale>

#include "fight.h"
#include "item.h"
#include "item_factory.h"
#include "player.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  setlocale(LC_ALL, "RUS");
  Player player(100, 100);
  Fight fight(25, 3);
  ItemFactory factory("items.json");

  std::cout << u8"Игра началась! Будьте готовы к последовательностям стрелок."
            << std::endl;
  std::cout << u8"Управление: W, S, A, D" << std::endl;
  std::cout << u8"У вас есть 3 секунды на ввод!" << std::endl;

  while (player.IsAlive()) {
    if (!fight.PlayRound(player)) break;

    std::cout << "Готовы к следующему раунду? (Нажмите Enter...)";
    std::cin.ignore();
  }

  player.AddItem(factory.GenerateItem(ItemID::kKhife));
  player.AddItem(factory.GenerateItem(ItemID::kKhife));
  player.AddItem(factory.GenerateItem(ItemID::kWolfMeat));
  player.AddItem(factory.GenerateItem(ItemID::kSunFlower));
  player.ShowInventory();
  std::cout << "Игра окончена! Вы проиграли." << std::endl;
  return 0;
}
