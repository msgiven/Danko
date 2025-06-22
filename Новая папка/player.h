#ifndef PLAYER_H_
#define PLAYER_H_
#include <memory>
#include <unordered_map>
#include <vector>

#include "item.h"
#include "quest.h"
enum Arrow { UP, DOWN, LEFT, RIGHT };

class Player {
 public:
  Player(int max_health, int max_sun_energy, int max_enc_point, int damage);
  void ChangeHealth(int damage);
  void ChangeEncPoint(int enc_point);
  void ChangeSunEnergy(int sun_energy);
  void Equip(int damage);
  bool IsAlive() const;
  void SelectUseItem();
  int GetDamage() const;
  void AddItem(std::shared_ptr<Item> item, int num);

  void UseItem(Item& item);
  void AddQuest(std::string& id, Quest& quest);
  void CompleteQuest(const std::string& id);
  void ShowQuests();
  int GetHealth() const;
  int GetSunEnergy() const;
  int GetMaxSunEnergy() const;
  int GetMaxHealth() const;
  int GetEncPoint() const;
  const std::unordered_map<std::string, Quest>& GetQuests() const;

 private:
  int health_;
  int enc_point_;
  int sun_energy_;
  int damage_;
  int max_sun_energy_;
  int max_enc_point_;
  int max_health_;

  std::unordered_map<std::string, Quest> quests_;
  std::unordered_map<ItemID, std::pair<std::shared_ptr<Item>, int>> items_;
};

#endif
