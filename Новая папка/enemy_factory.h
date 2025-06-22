#ifndef ENEMY_FACTORY_H_
#define ENEMY_FACTORY_H_
#include <string>

#include "enemy.h"
#include "item.h"
#include "json.hpp"
class EnemyFactory {
 public:
  EnemyFactory(const std::string& file_name);
  Enemy GenerateEnemy(EnemyID id);

 private:
  nlohmann::json data;
  std::string EnemyIDToString(EnemyID id) const;
};
#endif
