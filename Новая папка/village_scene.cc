#include "village_scene.h"

#include <Windows.h>
#include <conio.h>

#include "enemy.h"
#include "fight_manager.h"
#include "forest_scene.h"
#include "global_void.h"
#include "item_game.h"
#include "narrator.h"
#include "start_scene.h"

VillageScene::VillageScene(Player& player, StateMachine& machine,
                           std::unordered_map<std::string, Quest>& quests,
                           std::unordered_map<std::string, Npc>& npcs,
                           EnemyFactory& en_fac, ItemFactory& item_fac)
    : player_(player),
      machine_(machine),
      npcs_(npcs),
      quests_(quests),
      enemy_fac_(en_fac),
      item_fac_(item_fac) {}

void VillageScene::ElderQuest() {  // квест со старейшиной
  ClearConsole();
  Npc elder = npcs_["n01"];

#pragma region CorrectPhrase
  if (quests_[elder.availableQuests[0]].status == QuestStatus::kNotTaken) {
    Print(elder.meet_text);
    player_.AddQuest(elder.availableQuests[0],
                     quests_[elder.availableQuests[0]]);
    menu_status_ = MenuStatus::kInProgress;
    std::cout << std::endl
              << "✦ Квест был добавлен в ваш список ✦" << std::endl;
  } else if (quests_[elder.availableQuests[0]].status ==
             QuestStatus::kInProgress) {
    Print(elder.progress_text);
  } else if (quests_[elder.availableQuests[0]].status ==
             QuestStatus::kCompleted) {
    finish_quest_ = true;
    player_.ChangeEncPoint(quests_[elder.availableQuests[0]].enc_reward);
    Print(elder.final_text);
    if (talk_chest_) {
      player_.CompleteQuest(quests_[elder.availableQuests[0]].id);
      player_.AddItem(item_fac_.GenerateItem(ItemID::kKhife), 1);
      std::cout << "\n● Нож был добавлен в ваш инвентарь\n";
      talk_chest_ = false;
    }
  }
  std::cout << std::endl;
  while (_getch() != 13 && _getch() != 10) {
  }
#pragma endregion  // фраза старейшины в зависимости от состояния квеста
}

void VillageScene::InBeginning() {
  ClearConsole();
  int selected = 0;

  while (menu_status_ == MenuStatus::kInBeginning) {
    ClearConsole();
    for (int i = 0; i < options_.size(); ++i) {
      if (i == selected) {
        std::cout << "♥ " << options_[i] << "\n";
      } else {
        std::cout << "  " << options_[i] << "\n";
      }
    }

    int key = _getch();
    if (key == 224) {
      key = _getch();
      if (key == 72 && selected > 0) {
        selected--;
      } else if (key == 80 && selected < options_.size() - 1) {
        selected++;
      }
    } else if (key == 13) {
      ClearConsole();

      if (options_[selected] == "Поговорить со Старейшиной") {
        ElderQuest();
      } else if (options_[selected] == "Инвентарь") {
        player_.SelectUseItem();
        _getch();
      } else if (options_[selected] == "Квесты") {
        player_.ShowQuests();
        _getch();
      } else if (options_[selected] == "Показатели") {
        std::cout << "Здоровье: " << player_.GetHealth() << std::endl;
        std::cout << "Сила духа:" << player_.GetEncPoint() << std::endl;
        std::cout << "Сила света: " << player_.GetSunEnergy() << std::endl;
        std::cout << "Урон: " << player_.GetDamage();
        _getch();
      }

      ClearConsole();
    }
  }
}

void VillageScene::InProgress() {
  if (std::find(options_.begin(), options_.end(),
                "Отправиться в заброшенный дом") == options_.end()) {
    options_.push_front("Отправиться в заброшенный дом");
  }

  int selected = 0;
  while (menu_status_ == MenuStatus::kInProgress) {
    ClearConsole();
    for (int i = 0; i < options_.size(); ++i) {
      if (i == selected) {
        std::cout << "♥ " << options_[i] << "\n";
      } else {
        std::cout << "  " << options_[i] << "\n";
      }
    }

    int key = _getch();
    if (key == 224) {
      key = _getch();
      if (key == 72 && selected > 0) {  // стрелка вверх
        selected--;
      } else if (key == 80 && selected < options_.size() - 1) {  // вниз
        selected++;
      }
    } else if (key == 13) {  // Enter
      ClearConsole();

      if (options_[selected] == "Поговорить со Старейшиной") {
        ElderQuest();
      } else if (options_[selected] == "Инвентарь") {
        player_.SelectUseItem();
        _getch();
      } else if (options_[selected] == "Квесты") {
        player_.ShowQuests();
        _getch();
      } else if (options_[selected] == "Отправиться в заброшенный дом") {
        ToHouse();
      } else if (options_[selected] == "Показатели") {
        std::cout << "Здоровье: " << player_.GetHealth() << std::endl;
        std::cout << "Сила духа:" << player_.GetEncPoint() << std::endl;
        std::cout << "Сила света " << player_.GetSunEnergy() << std::endl;
        _getch();
      }

      ClearConsole();
    }
  }
}

void VillageScene::ToHouse() {
  player_.ChangeSunEnergy(-5);
  menu_status_ = MenuStatus::kToHouse;
  Print(Narrator::GetPhrase("descriptions.house"));
  for (int i = 0; i < 2; ++i) {
    if (i == 1) {
      std::cout << std::endl << "Приготовьтесь к следующему бою!" << std::endl;
    }
    Enemy boar = enemy_fac_.GenerateEnemy(EnemyID::kBoar);
    FightManager fight_man(player_, boar);
    fight_man.RunFight();
    std::cout << std::endl << "● Вы получили кабанье мясо" << std::endl;
    player_.AddItem(item_fac_.GenerateItem(ItemID::kBoarMeat), 3);
  }

  while (_getch() != 13 && _getch() != 10) {
  }

  options_.pop_front();
  options_.pop_front();
  options_.push_front("Зайти в дом");
  int selected = 0;

  while (menu_status_ == MenuStatus::kToHouse) {
    ClearConsole();
    for (int i = 0; i < options_.size(); ++i) {
      if (i == selected) {
        std::cout << "♥ " << options_[i] << "\n";
      } else {
        std::cout << "  " << options_[i] << "\n";
      }
    }

    int key = _getch();
    if (key == 224) {
      key = _getch();
      if (key == 72 && selected > 0) {
        selected--;
      } else if (key == 80 && selected < options_.size() - 1) {
        selected++;
      }
    } else if (key == 13) {
      ClearConsole();

      if (options_[selected] == "Зайти в дом") {
        InsideHouse();
      } else if (options_[selected] == "Инвентарь") {
        player_.SelectUseItem();
        _getch();
      } else if (options_[selected] == "Квесты") {
        player_.ShowQuests();
        _getch();
      } else if (options_[selected] == "Показатели") {
        std::cout << "Здоровье: " << player_.GetHealth() << std::endl;
        std::cout << "Сила духа:" << player_.GetEncPoint() << std::endl;
        std::cout << "Сила света " << player_.GetSunEnergy() << std::endl;
        _getch();
      }

      ClearConsole();
    }
  }
}

void VillageScene::InsideHouse() {
  player_.ChangeSunEnergy(-5);
  menu_status_ = MenuStatus::kInsideHouse;
  options_.clear();
  options_.push_back("Проверить соседнюю комнату");
  options_.push_back("Заглянуть в погреб");
  options_.push_back("Открыть сундук");
  options_.push_back("Вернуться к племени");
  options_.push_back("Инвентарь");
  options_.push_back("Квесты");
  options_.push_back("Показатели");
  int selected = 0;

  while (menu_status_ == MenuStatus::kInsideHouse) {
    ClearConsole();
    for (int i = 0; i < options_.size(); ++i) {
      if (i == selected) {
        std::cout << "♥ " << options_[i] << "\n";
      } else {
        std::cout << "  " << options_[i] << "\n";
      }
    }

    int key = _getch();
    if (key == 224) {
      key = _getch();
      if (key == 72 && selected > 0) {
        selected--;
      } else if (key == 80 && selected < options_.size() - 1) {
        selected++;
      }
    } else if (key == 13) {
      ClearConsole();

      if (options_[selected] == "Открыть сундук") {
        if (is_chest_open_) {
          ItemGame item_game(player_);
          if (item_game.Start()) {
            player_.AddItem(item_fac_.GenerateItem(ItemID::kHoneySuckle), 2);
            is_chest_open_ = false;
            std::cout << "\n● Вы нашли два цветка жимолости";
          }
        } else {
          ClearConsole();
          std::cout << "Вы уже забрали вещи из сундука" << std::endl;
        }
        _getch();
      } else if (options_[selected] == "Заглянуть в погреб") {
        if (is_basement_vis_) {
          ItemGame item_game(player_);
          if (item_game.Start()) {
            player_.AddItem(item_fac_.GenerateItem(ItemID::kHoneySuckle), 2);
            is_basement_vis_ = false;
            std::cout << "\n● Вы нашли два цветка жимолости";
          }
        } else {
          ClearConsole();
          std::cout << "Вы уже проверили погреб" << std::endl;
        }
        _getch();
      } else if (options_[selected] == "Вернуться к племени") {
        if (!is_basement_vis_ && !is_chest_open_ && !is_room_vis_) {
          player_.CompleteQuest("q01");

          InEnd();
        } else {
          std::cout << "Вы еще не проверили весь дом\n";
        }
        _getch();
      } else if (options_[selected] == "Проверить соседнюю комнату") {
        if (is_room_vis_) {
          ItemGame item_game(player_);
          if (item_game.Start()) {
            player_.AddItem(item_fac_.GenerateItem(ItemID::kHoneySuckle), 2);
            is_room_vis_ = false;
            std::cout << "\n● Вы нашли два цветка жимолости";
          }
        } else {
          ClearConsole();
          std::cout << "Вы уже проверили эту комнату" << std::endl;
        }
        _getch();
      } else if (options_[selected] == "Инвентарь") {
        player_.SelectUseItem();
        _getch();
      } else if (options_[selected] == "Квесты") {
        player_.ShowQuests();
        _getch();
      } else if (options_[selected] == "Показатели") {
        std::cout << "Здоровье: " << player_.GetHealth() << std::endl;
        std::cout << "Сила духа:" << player_.GetEncPoint() << std::endl;
        std::cout << "Сила света: " << player_.GetSunEnergy() << std::endl;
        std::cout << "Урон: " << player_.GetDamage();
        _getch();
      }

      ClearConsole();
    }
  }
}

void VillageScene::InEnd() {
  player_.ChangeSunEnergy(-5);
  options_.pop_front();
  player_.CompleteQuest("q01");
  quests_["q01"].status = QuestStatus::kCompleted;
  menu_status_ = MenuStatus::kInEnd;
  Narrator::GetPhrase("descriptions.return_to_tribe");
  options_.pop_front();
  options_.pop_front();
  options_.pop_front();
  options_.push_front("Поговорить со Старейшиной");
  options_.push_front("Отправиться в поход");
  ClearConsole();
  int selected = 0;

  while (menu_status_ == MenuStatus::kInEnd) {
    ClearConsole();
    for (int i = 0; i < options_.size(); ++i) {
      if (i == selected) {
        std::cout << "♥ " << options_[i] << "\n";
      } else {
        std::cout << "  " << options_[i] << "\n";
      }
    }

    int key = _getch();
    if (key == 224) {
      key = _getch();
      if (key == 72 && selected > 0) {
        selected--;
      } else if (key == 80 && selected < options_.size() - 1) {
        selected++;
      }
    } else if (key == 13) {
      ClearConsole();

      if (options_[selected] == "Отправиться в поход") {
        if (finish_quest_) {
          machine_.ChangeScene(std::make_unique<ForestScene>(
              player_, machine_, quests_, npcs_, enemy_fac_, item_fac_));
          return;
        } else {
          std::cout << "Поговорите со Старейшиной";
          _getch();
        }
      } else if (options_[selected] == "Поговорить со Старейшиной") {
        ElderQuest();
      } else if (options_[selected] == "Инвентарь") {
        player_.SelectUseItem();
        _getch();
      } else if (options_[selected] == "Квесты") {
        player_.ShowQuests();
        _getch();
      } else if (options_[selected] == "Показатели") {
        std::cout << "Здоровье: " << player_.GetHealth() << std::endl;
        std::cout << "Сила духа:" << player_.GetEncPoint() << std::endl;
        std::cout << "Сила света: " << player_.GetSunEnergy() << std::endl;
        std::cout << "Урон: " << player_.GetDamage();
        _getch();
      }

      ClearConsole();
    }
  }
}

void VillageScene::Intro() {
  Narrator::Load("narrator.json");
  Print(Narrator::GetPhrase("intros.village"));
  std::cout << "\nНажмите ENTER, чтобы продолжить" << std::endl;
  while (_getch() != 13 && _getch() != 10) {
  }
  ClearConsole();

  std::cout << Narrator::GetPhrase("intros.instruction");
  std::cout << "\nНажмите ENTER, чтобы продолжить" << std::endl;
  while (_getch() != 13 && _getch() != 10) {
  }
  intro_ = false;
  ClearConsole();
}

void VillageScene::Display() {
  if (intro_) {
    Intro();
  }
  switch (menu_status_) {
    case MenuStatus::kInBeginning:
      InBeginning();
      break;
    case MenuStatus::kInProgress:
      InProgress();
      break;
    case MenuStatus::kInEnd:
      if (finish_quest_) {
        InEnd();
      }
      break;
  }
}
