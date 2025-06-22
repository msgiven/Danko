#include "item.h"

Item::Item(ItemID id, std::string& type, std::string& name,
           std::variant<std::monostate, Food, Weapon, Flower> stats)
    : id_(id), type_(type), name_(name), stats_(std::move(stats)) {};

ItemID Item::GetID() { return id_; }
std::string Item::GetName() const { return name_; }
std::string Item::GetType() const { return type_; }
std::variant<std::monostate, Food, Weapon, Flower> Item::GetStats() { return stats_; }
