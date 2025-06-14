#ifndef QUEST_FACTORY_H_
#define QUEST_FACTORY_H_
#include "json.hpp"
#include "quest.h"
class QuestFactory {
 public:
  QuestFactory(const std::string& file_name);
  // Quest GenerateQuest(QuestID id);

 private:
  nlohmann ::json data_;
  const std::string QuestIDToString(QuestID id);
};
#endif
