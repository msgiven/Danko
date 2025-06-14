#include "enemy_factory.h"

#include <fstream>
#include <iostream>

EnemyFactory::EnemyFactory(const std::string& file_name) {
  std::ifstream file(file_name, std::ios::binary);
  file >> data;
};

Enemy EnemyFactory::GenerateEnemy(EnemyID id) {
  std::string name = EnemyIDToString(id);
  nlohmann::json enemy_data = data[name];
  return Enemy(enemy_data["display_name"], enemy_data["health"],
               enemy_data["damage"], enemy_data["loot_chance"]);
}

std::string EnemyFactory::EnemyIDToString(EnemyID id) const {
  switch (id) {
    case EnemyID::kSavage: {
      return "Savage";
      break;
    }
    case EnemyID::kWolf: {
      return "Wolf";
      break;
    }
    default: {
      return "";
      break;
    }
  }
};
