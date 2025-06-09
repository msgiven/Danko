#ifndef FIGHT_H_
#define FIGHT_H_
#include <vector>

#include "player.h"

class Fight {
 public:
  Fight(int damage, int timeLimit);
  bool PlayRound(Player& player);

 private:
  std::vector<Arrow> sequence;
  int damage_per_mistake_;
  int time_limit_sec_;
  int attack_type_;
  void ChooseAttackType(Player& player);
  void GenerateRandomSequence();
  void DisplaySequence() const;
  std::vector<Arrow> GetPlayerInput();
  int CalculateDamage(const std::vector<Arrow>& playerInput) const;
};

#endif
