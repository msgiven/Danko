#include "quest.h"

#include "global_void.h" #include < iostream>
Quest::Quest() {};

void Quest::AddQuest(QuestInfo quest_info) { quests_.push_back(quest_info); }

void Quest::ShowDescription(int i) {
  std::cout << quests_[i].description << std::endl;
}

void Quest::ShowQuests() {
  for (int i = 0; i < quests_.size(); ++i) {
    std::cout << i + 1 << quests_[i].name
              << " статус: " << quests_[i].is_completed << std::endl;
  }

  int choice;
  do {
    std::cout << "Введите номер квеста, если хотите посмотреть его описание: ";
    choice = GetValidIntegerInput();
    if (choice < 1 || choice > quests_.size()) {
      std::cout << "Ошибка: введите номер квеста от 1 до " << quests_.size()
                << ".\n";
    } else {
      ShowDescription(choice - 1);
    }
  } while (choice < 1 || choice > quests_.size());
}
