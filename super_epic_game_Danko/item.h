#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <variant>
// enum class ItemType { kFood, kWeapon, kFlower, kLightItem };

enum class ItemID { kKhife, kWolfMeat, kHoneySuckle, kSunFlower };

struct Food {
  int heal_point;
  int encourage_point;
};

struct Weapon {
  int damage;
  int durability;
  int light_point;
};

struct Flower {
  int light_point;
  int encourage_point;
};

class Item {
 public:
  Item(ItemID id, std::string& type, std::string& name,
       std::variant<std::monostate, Food, Weapon, Flower> stats);

  ItemID GetID();
  std::string GetName() const;
  void SetID(ItemID new_id);
  void SetName(std::string new_name);
  void SetStats(std::variant<std::monostate, Food, Weapon, Flower> stats);

 private:
  ItemID id_;
  std::string type_;
  std::string name_;
  std::variant<std::monostate, Food, Weapon, Flower> stats_;
};

#endif
