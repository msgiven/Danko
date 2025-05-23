#pragma once
#include <vector>

enum Arrow { UP, DOWN, LEFT, RIGHT };

class Player {
private:
    int health;
    int maxHealth;

public:
    Player(int maxHp = 100);
    void takeDamage(int damage);
    bool isAlive() const;
    int getHealth() const;
    int getMaxHealth() const;
};