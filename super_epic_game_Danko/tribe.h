#pragma once
#include <string>
class Tribe {
 public:
  void Speak();
  void ChangeHealth();
  void ChangeEnc();

 private:
  //std::string name;
  int enc_point_;  // encourage_point
  int health_;
};
