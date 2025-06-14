#pragma once
#include <string>

#include <vector>
enum class QuestID { kPreparation, kKillEnemy, kCollectItem, kTalkToNPC };

struct QuestInfo {
  std::string name;
  std::string display_name;
  std::string description;
  bool is_completed;
  QuestID id;
};

class Quest {
 public:
  Quest();
  void CompleteQuest(/*что-то передаем*/);
  void AddQuest(QuestInfo quest_info);
  void ShowDescription(int i);
  void ShowQuests();

 private:
  std::vector<QuestInfo> quests_;
};
