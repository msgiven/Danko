#ifndef FIGHT_H_
#define FIGHT_H_

#include <vector>

#include "enemy.h"
#include "player.h"

class Fight {
 public:
  Fight(int player_damage, int enemy_damage, int time_limit);
  bool PlayRound(Player& player, Enemy& enemy);
  bool PlayRound(Player& player);

 private:
  std::vector<Arrow> sequence_;
  int player_damage_;
  int enemy_damage_;
  int time_limit_sec_;
  int attack_type_;
  void ChooseAttackType(Player& player);
  void GenerateRandomSequence();
  void DisplaySequence() const;
  std::vector<Arrow> GetPlayerInput();
  int CalculatePlayerDamage(const std::vector<Arrow>& playerInput) const;
  int CalculateEnemyDamage(const std::vector<Arrow>& playerInput) const;
};

#endif
