#ifndef QUEST_MANAGER_H_
#define QUEST_MANAGER_H_
#include <string>
#include <unordered_map>

#include "npc.h"
#include "quest.h"

class QuestManager {
 public:
  static void LoadQuests(const std::string& file_name,
                         std::unordered_map<std::string, Quest>& quests);
  static void LoadNpcs(const std::string& file_name,
                       std::unordered_map<std::string, Npc>& quests);
};
#endif
