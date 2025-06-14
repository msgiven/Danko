#include < Windows.h>
#include <fcntl.h>
#include <io.h>

#include <iostream>

#include "enemy.h"
#include "enemy_factory.h"
#include "fight.h"
#include "fight_manager.h"
#include "global_void.h"
#include "item.h"
#include "item_factory.h"
#include "player.h"
#include "quest.h"
#include "tribe.h"
//
// int main() {

//
//   Player player(100, 100);
//   ItemFactory factory("items.json");
//   EnemyFactory en_factory("enemies.json");
//   Enemy enemy = en_factory.GenerateEnemy(EnemyID::kSavage);
//   FightManager fight_man(player, enemy);
//   Tribe tribe;
//   Quest quest;
//   // Print("\nИгра началась! Будьте готовы к последовательностям стрелок.");
//   // std::cout << "Управление: W, S, A, D" << std::endl;
//   // std::cout << "У вас есть 3 секунды на ввод!" << std::endl;
//   //  enemy.check();
//   //  fight_man.RunFight();
//
//
//
//   //quest.AddQuest({"AAA", "ффф", false});
//   //quest.ShowQuests();
//   player.AddItem(factory.GenerateItem(ItemID::kHoneySuckle));
//   //player.ShowInventory();
//
//   return 0;
// }
#include <conio.h>  // Для _kbhit() и _getch()
#include <curses.h>

#include <iostream>
#include <string>
#include <vector>

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
  std::vector<std::string> options = {"Новая игра", "Загрузить игру",
                                      "Инвентарь", "Выход"};
  int selected = 0;

  Player player(100, 100);
  ItemFactory factory("items.json");
  EnemyFactory en_factory("enemies.json");
  Enemy enemy = en_factory.GenerateEnemy(EnemyID::kSavage);
  FightManager fight_man(player, enemy);
  player.AddItem(factory.GenerateItem(ItemID::kHoneySuckle));
  while (true) {
    system("cls");  // Очистка экрана (Windows)
    std::cout << "=== Меню ===\n";
    for (int i = 0; i < options.size(); ++i) {
      if (i == selected) {
        std::cout << "> " << options[i] << "\n";  // Выделение выбранного пункта
      } else {
        std::cout << "  " << options[i] << "\n";
      }
    }

    int key = _getch();  // Ожидание нажатия клавиши
    if (key == 224) {    // Специальные клавиши (стрелки)
      key = _getch();
      if (key == 72 && selected > 0) {  // Стрелка вверх
        selected--;
      } else if (key == 80 && selected < options.size() - 1) {
        selected++;
      }
    } else if (key == 13 && options[selected] == "Загрузить игру") {
      system("cls");
      fight_man.RunFight();
      if (selected == 3) break;
      _getch();
    } else if (key == 13 && options[selected] == "Инвентарь") {
      system("cls");
      player.ShowInventory();
      if (selected == 3) break;
      _getch();
    }
  }

  return 0;
}
