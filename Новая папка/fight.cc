#include "fight.h"

#include <Windows.h>
#include <conio.h>

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

#include "global_void.h"

bool is_key_pressed() {
#ifdef _WIN32
  return _kbhit() != 0;
#else
  struct timeval tv = {0, 0};
  fd_set fds;
  FD_ZERO(&fds);
  FD_SET(STDIN_FILENO, &fds);
  return select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv) == 1;
#endif
}

char get_key_press() {
#ifdef _WIN32
  return _getch();
#else
  char buf = 0;
  struct termios old = {0};
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

Fight::Fight(int player_damage, int enemy_damage, int time_limit)
    : player_damage_(player_damage),
      enemy_damage_(enemy_damage),
      time_limit_sec_(time_limit) {
  srand(time(nullptr));
}

void Fight::GenerateRandomSequence() {
  sequence_.clear();
  for (int i = 0; i < 4; ++i) {
    int arrow = rand() % 4;
    sequence_.push_back(static_cast<Arrow>(arrow));
  }
}

void Fight::ChooseAttackType(Player& player) {
  PrintD("Выберите тип атаки:");
  std::cout << "1 - Обычная атака" << std::endl;
  std::cout << "2 - Атака энергией солнца (требуется 5 энергии)" << std::endl;

  while (true) {
    char input = _getch();
    if (input == '1') {
      attack_type_ = 1;
      DisplaySequence();
      break;
    } else if (input == '2' && player.GetSunEnergy() >= 5) {
      attack_type_ = 2;
      player.ChangeSunEnergy(-5);
      DisplaySequence();
      break;
    }
  }
}

void Fight::DisplaySequence() const {
  std::cout << "Введите последовательность стрелок: ";
  for (Arrow arrow : sequence_) {
    switch (arrow) {
      case UP:
        std::cout << "W";
        break;
      case DOWN:
        std::cout << "S";
        break;
      case LEFT:
        std::cout << "A";
        break;
      case RIGHT:
        std::cout << "D";
        break;
    }
    std::cout << " ";
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
  }
  ClearConsole();
}

std::vector<Arrow> Fight::GetPlayerInput() {
  std::vector<Arrow> player_input;
  std::cout << "Вводите стрелки (WASD): ";

  auto startTime = std::chrono::steady_clock::now();
  while (player_input.size() < 4) {
    if (std::chrono::steady_clock::now() - startTime >
        std::chrono::seconds(time_limit_sec_)) {
      std::cout << "\nВремя вышло!" << std::endl;
      break;
    }

    if (is_key_pressed()) {
      char input = get_key_press();
      Arrow arrow;
      switch (toupper(input)) {
        case 'W':
          arrow = UP;
          break;
        case 'S':
          arrow = DOWN;
          break;
        case 'A':
          arrow = LEFT;
          break;
        case 'D':
          arrow = RIGHT;
          break;
        default:
          continue;
      }
      player_input.push_back(arrow);
      std::cout << (arrow == UP     ? "W"
                    : arrow == DOWN ? "S"
                    : arrow == LEFT ? "A"
                                    : "D")
                << " ";
    }
  }
  return player_input;
}

int Fight::CalculatePlayerDamage(const std::vector<Arrow>& playerInput) const {
  if (playerInput.size() != 4) return enemy_damage_ * 4;

  int mistakes = 0;
  for (int i = 0; i < 4; ++i) {
    if (playerInput[i] != sequence_[i]) {
      mistakes++;
    }
  }
  return mistakes * enemy_damage_;
}

int Fight::CalculateEnemyDamage(const std::vector<Arrow>& playerInput) const {
  if (playerInput.size() != 4) return 0;

  int correct = 0;
  for (int i = 0; i < 4; ++i) {
    if (playerInput[i] == sequence_[i]) {
      correct++;
    }
  }
  return correct * player_damage_ * (attack_type_ == 2 ? 2 : 1);
}

bool Fight::PlayRound(Player& player, Enemy& enemy) {
  std::cout << "\n=== ВАШ ХОД ===" << std::endl;
  GenerateRandomSequence();

  std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1));
  ChooseAttackType(player);

  std::vector<Arrow> playerInput = GetPlayerInput();
  int damage = CalculateEnemyDamage(playerInput);
  enemy.TakeDamage(damage);

  std::cout << "\nВы нанесли " << damage << " урона!" << std::endl;
  std::cout << "Здоровье врага: " << enemy.GetHealth() << "/"
            << enemy.GetMaxHealth() << std::endl;
  std::cout << "Энергия солнца: " << player.GetSunEnergy() << "/"
            << player.GetMaxSunEnergy() << std::endl;

  return enemy.IsAlive();
}

bool Fight::PlayRound(Player& player) {
  std::cout << "\n=== ХОД ВРАГА ===" << std::endl;
  GenerateRandomSequence();

  std::this_thread::sleep_for(std::chrono::seconds(rand() % 3 + 1));
  DisplaySequence();

  std::vector<Arrow> playerInput = GetPlayerInput();
  int damage = CalculatePlayerDamage(playerInput);
  player.ChangeHealth(-damage);

  if (damage == 0) {
    std::cout << "\nИдеально! Вы не получили урона." << std::endl;
  } else {
    std::cout << "\nВы получили " << damage << " урона!" << std::endl;
  }
  std::cout << "Ваше здоровье: " << player.GetHealth() << "/"
            << player.GetMaxHealth() << std::endl;

  return player.IsAlive();
}
