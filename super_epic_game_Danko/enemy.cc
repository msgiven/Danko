#include "enemy.h"

Enemy::Enemy(std::string name, int max_health, int damage, float loot_chance)
    : max_health_(max_health),
      health_(max_health),
      damage_(damage),
      loot_chance_(loot_chance) {};

void Enemy::TakeDamage(int damage) {
  health_ = (health_ - damage < 0) ? 0 : health_ - damage;
}

bool Enemy::IsAlive() const { return health_ > 0; }

int Enemy::GetHealth() const { return health_; }

int Enemy::GetMaxHealth() const { return max_health_; }
