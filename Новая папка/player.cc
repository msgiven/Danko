#include "player.h"

#include < Windows.h>
#include <conio.h>

#include <iostream>
#include <vector>

#include "global_void.h"
Player::Player(int max_health, int max_sun_energy, int max_enc_point,
               int damage)
    : max_health_(max_health),
      max_sun_energy_(max_sun_energy),
      health_(max_health),
      sun_energy_(max_sun_energy),
      max_enc_point_(max_enc_point),
      enc_point_(max_enc_point),
      damage_(damage) {}

void Player::ChangeHealth(int damage) {
  health_ += damage;
  if (health_ <= 0) {
    health_ = 0;
    std::cout << "\nВы умерли. Игра окончена." << std::endl;
    exit(0);
  }
}

void Player::ChangeSunEnergy(int sun_energy) {
  sun_energy_ = (sun_energy_ + sun_energy < 0) ? 0 : sun_energy_ + sun_energy;
}

void Player::Equip(int damage) { damage_ += damage; }

void Player::ChangeEncPoint(int enc_point) {
  enc_point_ = (enc_point_ + enc_point < 0) ? 0 : enc_point_ + enc_point;
}

void Player::AddItem(std::shared_ptr<Item> item, int num) {
  for (int i = 0; i < num; ++i) {
    auto& entry = items_[item->GetID()];
    if (!entry.first) {
      entry.first = item;
    }
    ++entry.second;
  }
}

void Player::UseItem(Item& item) {
  auto stats = item.GetStats();
  const std::string& type = item.GetType();

  if (type == "food") {
    if (const auto* food = std::get_if<Food>(&stats)) {
      ChangeHealth(food->heal_point);

      std::cout << "Использовано: " << item.GetName()
                << ". Восстановлено здоровья: " << food->heal_point << "\n";
    }
  } else if (type == "weapon") {
    if (const auto* weapon = std::get_if<Weapon>(&stats)) {
      Equip(weapon->damage);
      std::cout << "Предмет " << item.GetName()
                << " экипирован (урон: " << weapon->damage
                << ", прочность: " << weapon->durability << ")\n";
    }
  } else if (type == "flower") {
    if (const auto* flower = std::get_if<Flower>(&stats)) {
      ChangeEncPoint(flower->encourage_point);
      ChangeSunEnergy(flower->light_point);
      std::cout << "Использовано: " << item.GetName()
                << ". Получено очков духа: " << flower->encourage_point
                << ", энергии солнца: " << flower->light_point << "\n";
    }
  }

  auto it = items_.find(item.GetID());
  if (it != items_.end()) {
    it->second.second--;
    if (it->second.second <= 0) {
      items_.erase(it);
    }
  }
}

void Player::SelectUseItem() {
  std::vector<std::pair<ItemID, std::pair<std::shared_ptr<Item>, int>>>
      itemList(items_.begin(), items_.end());

  int selected = 0;
  bool done = false;

  while (!done) {
    ClearConsole();
    std::cout << "=== ИНВЕНТАРЬ ===\n";

    for (int i = 0; i < itemList.size(); ++i) {
      const auto& item = itemList[i].second.first;
      int count = itemList[i].second.second;

      if (i == selected) {
        std::cout << "♥ ";
      } else {
        std::cout << "  ";
      }

      std::cout << item->GetName() << " x" << count << "\n";
    }

    std::cout << "\nИспользуйте стрелки для выбора, Enter для использования, "
                 "Esc для выхода\n";

    int key = _getch();
    if (key == 224) {
      key = _getch();
      switch (key) {
        case 72:
          selected = (selected > 0) ? selected - 1 : itemList.size() - 1;
          break;
        case 80:
          selected = (selected < itemList.size() - 1) ? selected + 1 : 0;
          break;
      }
    } else if (key == 13) {
      UseItem(*itemList[selected].second.first);
      _getch();

      itemList =
          std::vector<std::pair<ItemID, std::pair<std::shared_ptr<Item>, int>>>(
              items_.begin(), items_.end());

      if (itemList.empty()) {
        done = true;
      } else if (selected >= itemList.size()) {
        selected = itemList.size() - 1;
      }
    } else if (key == 27) {  // Esc
      done = true;
    }
  }
}

void Player::AddQuest(std::string& id, Quest& quest) {
  quests_[id] = quest;
  quest.status = QuestStatus::kInProgress;
}

void Player::CompleteQuest(const std::string& id) {
  auto it = quests_.find(id);
  if (it == quests_.end()) return;

  Quest& quest = it->second;

  /*if (quest.type == QuestType::kCollect) { //на будущее
    bool has_all_items = true;

    for (const auto& goal : quest.goals) {
      bool found = false;

      for (const auto& [item_id, item_pair] : items_) {
        const auto& item = item_pair.first;
        int count = item_pair.second;

        if (item && item->GetName() == goal.target_id &&
            count >= goal.target_count) {
          found = true;
          break;
        }
      }

      if (!found) {
        has_all_items = false;
      }
    }

    if (!has_all_items) return;
  }*/

  quest.status = QuestStatus::kCompleted;
  quests_.erase(it);
}

void Player::ShowQuests() {
  system("cls");
  if (quests_.empty()) {
    std::cout << "Нет активных квестов.\n";
    return;
  }

  int selected_index = 0;
  std::vector<std::pair<std::string, Quest>> quest_list(quests_.begin(),
                                                        quests_.end());
  std::cout << "=== Квесты ===\n";
  for (int i = 0; i < quest_list.size(); ++i) {
    std::cout << "▶ " << quest_list[i].second.title << " ◀" << std::endl;
    std::cout << quest_list[i].second.description << std::endl << std::endl;
  }
}

bool Player::IsAlive() const { return health_ > 0; }

int Player::GetHealth() const { return health_; }

int Player::GetMaxHealth() const { return max_health_; }

int Player::GetDamage() const { return damage_; }

int Player::GetSunEnergy() const { return sun_energy_; }
int Player::GetEncPoint() const { return enc_point_; }

int Player::GetMaxSunEnergy() const { return max_sun_energy_; }

const std::unordered_map<std::string, Quest>& Player::GetQuests() const {
  return quests_;
}
