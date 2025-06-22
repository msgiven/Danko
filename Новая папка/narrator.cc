#include "narrator.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

nlohmann::json Narrator::data_;

void Narrator::Load(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    throw std::runtime_error("Failed to open narrator JSON file: " + filepath);
  }
  file >> data_;
}

std::string Narrator::GetPhrase(const std::string& key) {
  // Разбиваем ключ на части (например, "intros.start" → ["intros", "start"])
  size_t dot_pos = key.find('.');
  std::string main_key = key.substr(0, dot_pos);
  std::string sub_key = key.substr(dot_pos + 1);

  if (!data_.contains(main_key) || !data_[main_key].contains(sub_key)) {
    std::cout << ("Phrase key not found: " + key);
  }

  return data_[main_key][sub_key].get<std::string>();
}
