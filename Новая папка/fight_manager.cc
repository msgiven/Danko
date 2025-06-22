#include "fight_manager.h"

#include < Windows.h>
#include <fcntl.h>
#include <io.h>

#include <iostream>

#include "global_void.h"

FightManager::FightManager(Player& player, Enemy& enemy)
    : player_(player), enemy_(enemy), fight_(player_.GetDamage(), enemy_.GetDamage(), 3) {}

bool FightManager::Attack(Player& player, Enemy& enemy) {
  if (!fight_.PlayRound(player, enemy)) {
    return false;
  }

  if (!enemy.IsAlive()) {
    std::cout << "\nВы победили врага!" << std::endl;
    return false;
  }
  // fight_.PlayRound(player, enemy);
}

bool FightManager::Defence(Player& player, Enemy& enemy) {
  // std::cout << "\n=== ХОД ВРАГА ===" << std::endl;
  if (!enemy.IsAlive() || !fight_.PlayRound(player)) {
    return false;
  }
  // fight_.PlayRound(player);
}

void FightManager::RunFight() {
  while (player_.IsAlive() && enemy_.IsAlive()) {
    Attack(player_, enemy_);
    Defence(player_, enemy_);
  }
}
