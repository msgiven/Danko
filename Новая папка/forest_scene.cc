#include "forest_scene.h"

#include <Windows.h>
#include <conio.h>

#include "end_scene.h"
#include "enemy.h"
#include "fight_manager.h"
#include "global_void.h"
#include "item_game.h"
#include "narrator.h"
#include "start_scene.h"

ForestScene::ForestScene(Player& player, StateMachine& machine,
                         std::unordered_map<std::string, Quest>& quests,
                         std::unordered_map<std::string, Npc>& npcs,
                         EnemyFactory& en_fac, ItemFactory& item_fac)
    : player_(player),
      machine_(machine),
      npcs_(npcs),
      quests_(quests),
      enemy_fac_(en_fac),
      item_fac_(item_fac) {}

void ForestScene::MaelQuest() {
  player_.ChangeSunEnergy(-5);
  ClearConsole();
  Npc mael = npcs_["n02"];

#pragma region CorrectPhrase
  if (quests_[mael.availableQuests[0]].status == QuestStatus::kNotTaken) {
    Print(mael.meet_text);
    player_.AddQuest(mael.availableQuests[0], quests_[mael.availableQuests[0]]);
    menu_status_forest_ = MenuStatusForest::kInProgress;
    std::cout << std::endl
              << "✦ Квест был добавлен в ваш список ✦" << std::endl;
  } else if (quests_[mael.availableQuests[0]].status ==
             QuestStatus::kInProgress) {
    Print(mael.progress_text);
  } else if (quests_[mael.availableQuests[0]].status ==
             QuestStatus::kCompleted) {
    finish_quest_ = true;
    Print(mael.final_text);
    if (talk_mael_) {
      player_.ChangeEncPoint(quests_[mael.availableQuests[0]].enc_reward);
      talk_mael_ = false;
    }
  }
  std::cout << std::endl;
  while (_getch() != 13 && _getch() != 10) {
  }
#pragma endregion  // фраза старейшины в зависимости от состояния квеста
}

void ForestScene::InBeginning() {
  player_.ChangeSunEnergy(-5);
  ClearConsole();
  int selected = 0;

  while (menu_status_forest_ == MenuStatusForest::kInBeginning) {
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

      if (options_[selected] == "Поговорить с Маэль") {
        MaelQuest();
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

void ForestScene::InProgress() {
  player_.ChangeSunEnergy(-5);
  if (std::find(options_.begin(), options_.end(),
                "Отправиться на поиски цветка солнца") == options_.end()) {
    options_.push_front("Отправиться на поиски цветка солнца");
  }

  int selected = 0;
  while (menu_status_forest_ == MenuStatusForest::kInProgress) {
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

      if (options_[selected] == "Поговорить с Маэль") {
        MaelQuest();
      } else if (options_[selected] == "Инвентарь") {
        player_.SelectUseItem();
        _getch();
      } else if (options_[selected] == "Квесты") {
        player_.ShowQuests();
        _getch();
      } else if (options_[selected] == "Отправиться на поиски цветка солнца") {
        ToForest();
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

void ForestScene::ToForest() {
  player_.ChangeSunEnergy(-5);
  menu_status_forest_ = MenuStatusForest::kToForest;
  Print(Narrator::GetPhrase("descriptions.sun_flower_search"));
  for (int i = 0; i < 3; ++i) {
    if (i == 1) {
      std::cout << std::endl << "Приготовьтесь к следующему бою!" << std::endl;
    }
    Enemy shadow = enemy_fac_.GenerateEnemy(EnemyID::kShadow);
    FightManager fight_man(player_, shadow);
    fight_man.RunFight();
    std::cout << std::endl << "Вы получили цветок жимолости" << std::endl;
    player_.AddItem(item_fac_.GenerateItem(ItemID::kHoneySuckle), 1);
  }

  options_.pop_front();
  options_.pop_front();
  options_.push_front("Вернуться к племени");
  options_.push_front("Сорвать цветок солнца");
  int selected = 0;

  while (menu_status_forest_ == MenuStatusForest::kToForest) {
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

      if (options_[selected] == "Сорвать цветок солнца") {
        if (is_flower_) {
          ItemGame item_game(player_);
          item_game.Start();
          player_.AddItem(item_fac_.GenerateItem(ItemID::kSunFlower), 1);
          std::cout << "\n● Цветок солнца добавлен в ваш инвентарь"
                    << std::endl;
          // quests_["q02"].status = QuestStatus::kCompleted;
          is_flower_ = false;
        } else {
          std::cout << "Вы уже взяли цветок. Отнесите его Маэль." << std::endl;
          _getch();
        }
      } else if (options_[selected] == "Вернуться к племени") {
        if (!is_flower_) {
          InEnd();
        } else {
          std::cout << "Вы еще не забрали цветок." << std::endl;
          _getch();
        }
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

void ForestScene::InEnd() {
  player_.ChangeSunEnergy(-5);
  player_.CompleteQuest("q02");
  quests_["q02"].status = QuestStatus::kCompleted;
  menu_status_forest_ = MenuStatusForest::kInEnd;
  options_.pop_front();
  options_.pop_front();
  options_.push_front("Поговорить с Маэль");
  options_.push_front("Поговорить с племенем");
  ClearConsole();
  int selected = 0;

  while (menu_status_forest_ == MenuStatusForest::kInEnd) {
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

      if (options_[selected] == "Поговорить с племенем") {
        if (finish_quest_) {
          machine_.ChangeScene(std::make_unique<EndScene>());
        } else {
          std::cout << "Вы еще не поговорили с Маэль." << std::endl;
        }
      } else if (options_[selected] == "Поговорить с Маэль") {
        MaelQuest();
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

void ForestScene::Intro() {
  Narrator::Load("narrator.json");
  Print(Narrator::GetPhrase("intros.forest"));
  Print(Narrator::GetPhrase("intros.forest_quest"));
  std::cout << "\nНажмите ENTER, чтобы продолжить" << std::endl;
  intro_ = false;
  while (_getch() != 13 && _getch() != 10) {
  }
  ClearConsole();
}

void ForestScene::Display() {
  if (intro_) {
    Intro();
  }
  switch (menu_status_forest_) {
    case MenuStatusForest::kInBeginning:
      InBeginning();
      break;
    case MenuStatusForest::kInProgress:
      InProgress();
      break;
    case MenuStatusForest::kInEnd:
      InEnd();
      break;
  }
}
