#include <string>
#include <utility>
#include "../entities/Player.h"
#include "../entities/Shadow.h"

struct HealAction {
    std::string id;
    std::string name;
    int32_t mp_cost;
    int32_t heal_amount; // how much corruption it reduces

    HealAction() = default;
    HealAction(const std::string &i, const std::string &n, int32_t cost, int32_t h)
        : id(i), name(n), mp_cost(cost), heal_amount(h) {}

    // Execute the action against a shadow using a player (who must pay mp).
    // Returns pair(success, message)
    std::pair<bool, std::string> execute(Shadow &target, Player &user) const {
        if (user.mp < mp_cost) {
            return {false, "Not enough MP."};
        }
        user.consume_mp(mp_cost);
        bool changed = target.apply_heal(heal_amount);
        if (!changed) return {false, "Target unaffected (already healed or no change)."};
        if (target.healed) {
            return {true, std::string("Healed fully — memory restored: ") + target.memory.title};
        }
        return {true, std::string("Healed ") + std::to_string(heal_amount) + " corruption."};
    }
};