#include "quest_manager.h"

#include <fstream>

#include "json.hpp"

void QuestManager::LoadQuests(const std::string& file_name,
                              std::unordered_map<std::string, Quest>& quests) {
  std::ifstream file(file_name);
  nlohmann::json data;
  file >> data;

  for (const auto q_data : data["quests"]) {
    Quest q;
    q.id = q_data["id"];
    q.title = q_data["title"];
    q.description = q_data["description"];
    q.enc_reward = q_data["enc_reward"];
    std::string str_type = q_data["type"];
    if (str_type == "kill") {
      q.type = QuestType::kKill;
      q.content = QuestContent::kKillEnemy;
    } else if (str_type == "collect") {
      q.type = QuestType::kCollect;
      q.content = QuestContent::kCollectItem;
    } else if (str_type == "talk") {
      q.type = QuestType::kTalk;
      q.content = QuestContent::kTalkToNPC;
    }

    for (const auto g_data : q_data["goals"]) {
      QuestGoal g;
      g.target_id = g_data["target"];
      g.target_count = g_data["count"];
      q.goals.push_back(g);
    }
    quests[q.id] = q;
  }
}

void QuestManager::LoadNpcs(const std::string& file_name,
                            std::unordered_map<std::string, Npc>& npcs) {
  std::ifstream file(file_name);
  nlohmann::json data;
  file >> data;

  for (const auto npc_data : data["npcs"]) {
    Npc npc;
    npc.id = npc_data["id"];
    npc.name = npc_data["name"];
    npc.meet_text = npc_data["meet_text"];
    npc.progress_text = npc_data["progress_text"];
    npc.final_text = npc_data["final_text"];
    for (const auto& quest_id : npc_data["quests"]) {
      npc.availableQuests.push_back(quest_id);
    }
    npcs[npc.id] = npc;
  }
}
