#include "item.h"

Item::Item(ItemID id, std::string& type, std::string& name,
           std::variant<std::monostate, Food, Weapon, Flower> stats)
    : id_(id), type_(type), name_(name), stats_(std::move(stats)) {};

ItemID Item::GetID() { return id_; }
std::string Item::GetName() const { return name_; }
void Item::SetID(ItemID new_id) { id_ = new_id; }
void Item::SetName(std::string new_name) { name_ = new_name; }
void Item::SetStats(std::variant<std::monostate, Food, Weapon, Flower> stats) {
  stats_ = std::move(stats);
}
