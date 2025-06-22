#ifndef FOREST_SCENE_H_
#define FOREST_SCENE_H_
#include <deque>

#include "enemy_factory.h"
#include "item_factory.h"
#include "npc.h"
#include "player.h"
#include "quest.h"
#include "scene.h"
#include "state_machine.h"

enum class MenuStatusForest {
  kInBeginning,
  kInProgress,
  kToForest,
  kAroundFlower,
  kInEnd
};

class ForestScene : public Scene {
 public:
  ForestScene(Player& player, StateMachine& machine,
              std::unordered_map<std::string, Quest>& quests,
              std::unordered_map<std::string, Npc>& npcs, EnemyFactory& en_fac,
              ItemFactory& item_fac);
  void Display() override;
  void Intro();
  void MaelQuest();
  void InBeginning();
  void InProgress();
  void InEnd();
  void ToForest();

 private:
  std::deque<std::string> options_ = {"Поговорить с Маэль", "Квесты",
                                      "Инвентарь", "Показатели"};
  Player& player_;
  StateMachine& machine_;
  bool intro_ = true;
  bool is_flower_ = true;
  bool finish_quest_ = false;
  bool is_basement_vis_ = true;
  bool talk_mael_ = true;
  std::unordered_map<std::string, Quest> quests_;
  std::unordered_map<std::string, Npc> npcs_;
  MenuStatusForest menu_status_forest_ = MenuStatusForest::kInBeginning;
  EnemyFactory& enemy_fac_;
  ItemFactory& item_fac_;
};

#endif
