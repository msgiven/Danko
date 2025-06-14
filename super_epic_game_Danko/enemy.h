#ifndef ENEMY_H_
#define ENEMY_H_
#include <iostream>
#include <string>
enum class EnemyID { kSavage, kWolf };

class Enemy {
 public:
  Enemy(std::string name, int max_health, int damage, float loot_chance);
  void TakeDamage(int damage);
  bool IsAlive() const;
  void check() { std::cout << "блалыб"; }
  int GetHealth() const;
  int GetMaxHealth() const;

 private:
  int health_;
  const std::string name;
  const int damage_;
  const int max_health_;
  const float loot_chance_;
};
#endif
