#include "item_factory.h"

#include <fstream>
#include <iostream>
#include <memory>

#include "item.h"
ItemFactory::ItemFactory(const std::string& file_name) {
  std::ifstream file(file_name, std::ios::binary);
  file >> data_;
}

std::shared_ptr<Item> ItemFactory::GenerateItem(ItemID id) {
  std::string name = ItemIDToString(id);

  nlohmann::json item_data = data_[name];
  std::variant<std::monostate, Food, Weapon, Flower> stats;

  std::string type = item_data["type"];
  std::string display_name = item_data["display_name"];
  if (type == "food") {
    stats = Food{item_data["heal_point"], item_data["encourage_point"]};
  } else if (type == "weapon") {
    stats = Weapon{item_data["damage"], item_data["durability"],
                   item_data["light_point"]};
  } else if (type == "flower") {
    stats = Flower{item_data["light_point"], item_data["encourage_point"]};
  }

  return std::make_shared<Item>(id, type, display_name, stats);
}

const std::string ItemFactory::ItemIDToString(ItemID id) {
  switch (id) {
    case ItemID::kKhife: {
      return "knife";
      break;
    }
    case ItemID::kBoarMeat: {
      return "boar_meat";
      break;
    }
    case ItemID::kHoneySuckle: {
      return "honeysuckle";
      break;
    }
    case ItemID::kSunFlower: {
      return "sunflower";
      break;
    }
    default: {
      return "";
      break;
    }
  }
}
