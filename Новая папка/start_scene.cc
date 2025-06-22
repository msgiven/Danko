// #include "start_scene.h"
//
// #include < Windows.h>
// #include <conio.h>
//
// #include <iostream>
//
// #include "fight_manager.h"
// #include "quest_scene.h"
//
// StartScene::StartScene(Player& player, StateMachine& machine)
//     : player_(player),
//       // fight_man_(fight_man_),
//       machine_(machine),
//       enemy_fac_("enemies.json") {}
//
// void StartScene::Display() {
//   while (true) {
//     system("cls");  // Очистка экрана (Windows)
//     std::cout << "=== Меню ===\n";
//     for (int i = 0; i < options.size(); ++i) {
//       if (i == selected) {
//         std::cout << "> " << options[i] << "\n";
//       } else {
//         std::cout << "  " << options[i] << "\n";
//       }
//     }
//
//     int key = _getch();
//     if (key == 224) {
//       key = _getch();
//       if (key == 72 && selected > 0) {  // Стрелка вверх
//         selected--;
//       } else if (key == 80 && selected < options.size() - 1) {
//         selected++;
//       }
//     } else if (key == 13 && options[selected] == "Загрузить игру") {
//       system("cls");
//       Enemy enemy = enemy_fac_.GenerateEnemy(EnemyID::kSavage);
//       FightManager fight_man(player_, enemy);
//       fight_man.RunFight();
//       // enemy_fac_.GenerateEnemy(EnemyID::kSavage));
//       if (selected == 3) break;
//       _getch();
//     } else if (key == 13 && options[selected] == "Инвентарь") {
//       system("cls");
//       player_.ShowInventory();
//       if (selected == 3) break;
//       _getch();
//     } else if (key == 13 && options[selected] == "Квесты") {
//       player_.ShowQuests();
//       if (selected == 3) break;
//       _getch();
//       return;
//     }
//   }
// }
