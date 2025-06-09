#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
#include <unordered_map>

#include "item.h"
enum Arrow { UP, DOWN, LEFT, RIGHT };

class Player {
 public:
  Player(int max_health, int max_sun_energy);
  void TakeDamage(int damage);
  void ChangeSunEnergy(int sun_energy);
  bool IsAlive() const;
  void AddItem(std::shared_ptr<Item> item);
  void ShowInventory();

  int GetHealth() const;
  int GetSunEnergy() const;
  int GetMaxSunEnergy() const;
  int GetMaxHealth() const;


 private:
  int health_;
  int sun_energy_;
  int max_sun_energy_;
  int max_health_;
  Item item_;
  std::unordered_map<ItemID, std::pair<std::shared_ptr<Item>, int>> items;
};

#endif
