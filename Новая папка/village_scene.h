#ifndef VILLAGE_SCENE_H_
#define VILLAGE_SCENE_H_
#include <deque>

#include "enemy_factory.h"
#include "item_factory.h"
#include "npc.h"
#include "player.h"
#include "quest.h"
#include "scene.h"
#include "state_machine.h"

enum class MenuStatus {
  kInBeginning,
  kInProgress,
  kToHouse,
  kInsideHouse,
  kInEnd
};

class VillageScene : public Scene {
 public:
  VillageScene(Player& player, StateMachine& machine,
               std::unordered_map<std::string, Quest>& quests,
               std::unordered_map<std::string, Npc>& npcs, EnemyFactory& en_fac,
               ItemFactory& item_fac);
  void Display() override;
  void Intro();
  void ElderQuest();
  void InBeginning();
  void InProgress();
  void InEnd();
  void ToHouse();
  void InsideHouse();

 private:
  std::deque<std::string> options_ = {"Поговорить со Старейшиной", "Квесты",
                                      "Инвентарь", "Показатели"};
  Player& player_;
  StateMachine& machine_;
  bool intro_ = true;
  bool is_chest_open_ = true;
  bool is_room_vis_ = true;
  bool is_basement_vis_ = true;
  bool finish_quest_ = false;
  bool talk_chest_ =  true;
  std::unordered_map<std::string, Quest> quests_;
  std::unordered_map<std::string, Npc> npcs_;
  MenuStatus menu_status_ = MenuStatus::kInBeginning;
  EnemyFactory& enemy_fac_;
  ItemFactory& item_fac_;
};
#endif
