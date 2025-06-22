#ifndef QUEST_H_
#define QUEST_H_
#include <string>
#include <vector>

enum class QuestContent {
  kPreparation,
  kKillEnemy,
  kCollectItem,
  kTalkToNPC,
  kExplore
};
enum class QuestType{kCollect, kKill, kTalk};
enum class QuestStatus { kNotTaken, kInProgress, kCompleted };

struct QuestGoal {
  std::string target_id;  // ID цели: ID монстра, ID предмета, ID NPC
  int target_count;
};

struct Quest {
  std::string id;
  std::string title;
  std::string description;
  QuestType type;
  QuestContent content;
  QuestStatus status = QuestStatus::kNotTaken;
  std::vector<QuestGoal> goals;
  int enc_reward;
};
#endif
