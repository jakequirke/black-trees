#ifndef HEAL_ACTION_H
#define HEAL_ACTION_H

#include <string>
#include <cstdint>
#include "../entities/Player.h"
#include "../entities/Shadow.h"

struct HealAction {
    std::string id;
    std::string name;
    int32_t mp_cost;
    int32_t heal_amount;
    HealAction() = default;
    HealAction(const std::string &i, const std::string &n, int32_t cost, int32_t h);
    std::pair<bool, std::string> execute(Shadow &target, Player &user) const;
};

#endif // HEAL_ACTION_H