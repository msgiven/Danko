#include "player.h"

Player::Player(int maxHp) : maxHealth(maxHp), health(maxHp) {}

void Player::takeDamage(int damage) {
    health = (health - damage < 0) ? 0 : health - damage;
}

bool Player::isAlive() const {
    return health > 0;
}

int Player::getHealth() const {
    return health;
}

int Player::getMaxHealth() const {
    return maxHealth;
}