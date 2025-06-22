#include < Windows.h>
#include <conio.h>
#include <curses.h>
#include <fcntl.h>
#include <io.h>

#include <cstdlib>  // Для rand
#include <ctime>    // Для srand и time
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "enemy.h"
#include "enemy_factory.h"
#include "fight.h"
#include "fight_manager.h"
#include "global_void.h"
#include "item.h"
#include "item_factory.h"
#include "player.h"
#include "quest.h"
#include "quest_manager.h"
#include "start_scene.h"
#include "state_machine.h"
#include "village_scene.h"

int main() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);

  std::ifstream file("player.json");
  nlohmann::json data;
  file >> data;
  Player player(data.value("health", 0), data.value("light_point", 0),
                data.value("enc_point", 0), data.value("damage", 0));

  std::unordered_map<std::string, Quest> quests;
  std::unordered_map<std::string, Npc> npcs;


  EnemyFactory en_fac("enemies.json");
  ItemFactory item_fac("items.json");
  QuestManager q_man;
  StateMachine machine;
  q_man.LoadQuests("quests.json", quests);
  q_man.LoadNpcs("npc.json", npcs);

  machine.PushScene(std::make_unique<VillageScene>(player, machine, quests,
                                                   npcs, en_fac, item_fac));

  while (true) {
    if (auto* scene = machine.GetCurrentScene()) {
      scene->Display();
    } else {
      break;
    }
  }

  return 0;
}
