#ifndef ITEM_FACTORY_H_
#define ITEM_FACTORY_H_
#include <string>

#include "item.h"
#include "json.hpp"
class ItemFactory {
 public:
  ItemFactory(const std::string& file);
  std::shared_ptr<Item> GenerateItem(ItemID id);

 private:
  nlohmann::json data_;
  const std::string ItemIDToString(ItemID id);
};
#endif
