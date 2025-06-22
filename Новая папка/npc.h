#ifndef NPC_H_
#define NPC_H_

#include <unordered_set>

struct Npc {
  std::string id;
  std::string name;
  std::string meet_text;
  std::string progress_text;
  std::string final_text;
  std::vector<std::string> availableQuests;  // ID квестов, которые можно вз€ть
  std::unordered_set<std::string> givenQuests;  //  весты, которые уже выданы
};
#endif
