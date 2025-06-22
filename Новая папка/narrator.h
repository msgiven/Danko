#ifndef NARRATOR_H_
#define NARRATOR_H_
#include <map>
#include <string>

#include "json.hpp"

class Narrator {
 public:
  static void Load(const std::string& filepath);

  static std::string GetPhrase(const std::string& key);

 private:
  static nlohmann::json data_;
};
#endif
