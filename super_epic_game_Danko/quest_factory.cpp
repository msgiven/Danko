#include "quest_factory.h"

#include <fstream>
QuestFactory::QuestFactory(const std::string& file_name) {
  std::ifstream file(file_name, std::ios::binary);
  file >> data_;
}

//Quest QuestFactory::GenerateQuest(QuestID id) {
//  std::string data_name = QuestIDToString(id);
//  nlohmann::json quest_data = data_[data_name];
//  std::string name = quest_data["name"];
//  std::string display_name = quest_data["display_name"];
//  std::string description = quest_data["description"];
//  
//
//  return QuestInfo({name, display_name, description, false, id});
//}

const std::string QuestFactory::QuestIDToString(QuestID id) {
  switch (id) {
  case QuestID::kPreparation: {
      return "Preparation";
      break;
  }
    case QuestID::kKillEnemy: {
      return "Shadow_fighter";
      break;
    }
    case QuestID::kCollectItem: {
      return "Heal_potion";
      break;
    }
    case QuestID::kTalkToNPC: {
      return "Talk";
      break;
    }
    default: {
      return "";
      break;
    }
  }
}
