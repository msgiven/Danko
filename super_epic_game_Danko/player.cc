#include "player.h"

#include <iostream>
#include <vector>
Player::Player(int max_health, int max_sun_energy)
    : max_health_(max_health),
      max_sun_energy_(max_sun_energy),
      health_(max_health),
      item_(item_),
      sun_energy_(max_sun_energy) {}

void Player::TakeDamage(int damage) {
  health_ = (health_ - damage < 0) ? 0 : health_ - damage;
}

void Player::ChangeSunEnergy(int sun_energy) {
  sun_energy_ = (sun_energy_ + sun_energy < 0) ? 0 : sun_energy_ + sun_energy;
}

void Player::AddItem(std::shared_ptr<Item> item) {
  auto& entry = items[item->GetID()];
  if (!entry.first) {
    entry.first = item;
  }
  ++entry.second;
}

void Player::ShowInventory() {
  for (const auto& [id, pair] : items) {
    const auto& item = pair.first;
    int count = pair.second;
    if (item) {
      std::cout << item->GetName() << " x" << count << std::endl;
      // std::wcout << L"• " << item->GetName() << L" x" << count << std::endl;
    }
  }
}

bool Player::IsAlive() const { return health_ > 0; }

int Player::GetHealth() const { return health_; }

int Player::GetMaxHealth() const { return max_health_; }

int Player::GetSunEnergy() const { return sun_energy_; }

int Player::GetMaxSunEnergy() const { return max_sun_energy_; }
