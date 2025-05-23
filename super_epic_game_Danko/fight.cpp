#include "fight.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <conio.h>
#include <windows.h>


bool isKeyPressed() {
#ifdef _WIN32
    return _kbhit() != 0;
#else
    struct timeval tv = { 0, 0 };
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
#endif
}

char getKeyPress() {
#ifdef _WIN32
    return _getch();
#else
    char buf = 0;
    struct termios old = { 0 };
    if (tcgetattr(0, &old) < 0) perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if (tcsetattr(0, TCSANOW, &old) < 0) perror("tcsetattr ICANON");
    if (read(0, &buf, 1) < 0) perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if (tcsetattr(0, TCSADRAIN, &old) < 0) perror("tcsetattr ~ICANON");
    return buf;
#endif
}

Fight::Fight(int damage, int timeLimit)
    : damagePerMistake(damage), timeLimitSec(timeLimit) {
    srand(time(nullptr));
}

void Fight::generateRandomSequence() {
    sequence.clear();
    for (int i = 0; i < 4; ++i) {
        int arrow = rand() % 4;
        sequence.push_back(static_cast<Arrow>(arrow));
    }
}

void Fight::displaySequence() const {
    std::cout << "Введите последовательность стрелок:" << std::endl;
    for (Arrow arrow : sequence) {
        switch (arrow) {
        case UP: std::cout << "W"; break;
        case DOWN: std::cout << "S"; break;
        case LEFT: std::cout << "A"; break;
        case RIGHT: std::cout << "D"; break;
        }
        std::cout << " ";
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    system("clear||cls");
}

std::vector<Arrow> Fight::getPlayerInput() {
    std::vector<Arrow> playerInput;
    std::cout << "У вас есть " << timeLimitSec << " секунд(ы)!" << std::endl;
    std::cout << "Введите последовательность (W, S, A, D): ";

    auto startTime = std::chrono::steady_clock::now();
    while (playerInput.size() < 4) {
        if (std::chrono::steady_clock::now() - startTime > std::chrono::seconds(timeLimitSec)) {
            std::cout << "\nВремя вышло!" << std::endl;
            break;
        }

        if (isKeyPressed()) {
            char input = getKeyPress();
            Arrow arrow;
            switch (toupper(input)) {
            case 'W': arrow = UP; break;
            case 'S': arrow = DOWN; break;
            case 'A': arrow = LEFT; break;
            case 'D': arrow = RIGHT; break;
            default: continue;
            }
            playerInput.push_back(arrow);
            std::cout << (arrow == UP ? "W" : arrow == DOWN ? "S" : arrow == LEFT ? "A" : "D") << " ";
        }
    }
    return playerInput;
}

int Fight::calculateDamage(const std::vector<Arrow>& playerInput) const {
    if (playerInput.size() != 4) return damagePerMistake * 4;

    int mistakes = 0;
    for (int i = 0; i < 4; ++i) {
        if (playerInput[i] != sequence[i]) {
            mistakes++;
        }
    }
    return mistakes * damagePerMistake;
}

bool Fight::playRound(Player& player) {
    generateRandomSequence();

    int delay = rand() % 3 + 1;
    std::this_thread::sleep_for(std::chrono::seconds(delay));

    displaySequence();
    std::vector<Arrow> playerInput = getPlayerInput();

    int damage = calculateDamage(playerInput);
    player.takeDamage(damage);

    if (damage == 0) {
        std::cout << "\nИдеально! Вы не получили урона." << std::endl;
    }
    else {
        std::cout << "\nВы получили " << damage << " урона!" << std::endl;
    }

    std::cout << "Оставшееся здоровье: " << player.getHealth() << "/" << player.getMaxHealth() << std::endl;
    return player.isAlive();
}