#ifndef FIGHT_MANAGER_H_
#define FIGHT_MANAGER_H_
#include "enemy.h"
#include "fight.h"
#include "player.h"

class FightManager {
 public:
  FightManager(Player& player, Enemy& enemy);
  bool Attack(Player& player, Enemy& enemy);
  bool Defence(Player& player, Enemy& enemy);
  void RunFight();

 private:
  Player& player_;
  Enemy enemy_;
  Fight fight_;
};
#endif
