#pragma once
#include "player.h"
#include <vector>
#include <chrono>
#include <thread>

class Fight {
private:
    std::vector<Arrow> sequence;
    int damagePerMistake;
    int timeLimitSec;

    void generateRandomSequence();
    void displaySequence() const;
    std::vector<Arrow> getPlayerInput();
    int calculateDamage(const std::vector<Arrow>& playerInput) const;

public:
    Fight(int damage = 25, int timeLimit = 5);
    bool playRound(Player& player);
};