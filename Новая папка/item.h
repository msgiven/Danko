#ifndef ITEM_H_
#define ITEM_H_
#include <string>
#include <variant>
// enum class ItemType { kFood, kWeapon, kFlower, kLightItem };

enum class ItemID { kKhife, kBoarMeat, kHoneySuckle, kSunFlower };

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
  std::string GetId() const;
  std::string GetType() const;
  std::variant<std::monostate, Food, Weapon, Flower> GetStats();

 private:
  const ItemID id_;
  const std::string type_;
  const std::string name_;
  const std::variant<std::monostate, Food, Weapon, Flower> stats_;
};

#endif
