#include <iostream>
#include <vector>

#include "entities/Player.h"
#include "entities/Shadow.h"
#include "core/HealAction.h"
#include "core/BattleSystem.h"
#include "core/WorldState.h"
#include "core/SaveSystem.h"

int main() {
    // Setup world
    WorldState world;

    Memory mem{"mem_001", "A Forgotten Lullaby", "You remember the melody your mother hummed while stitching old coats."};
    Shadow shad{"shadow_001", 50, mem};
    world.add_shadow(shad);

    Player hero{"Aeris", 20};

    // Actions
    std::vector<HealAction> actions;
    actions.emplace_back("heal_01", "Mend", 5, 20);
    actions.emplace_back("heal_02", "Soothing Hymn", 8, 35);

    // Run battle demo
    std::cout << "---- Battle demo: Heal the shadow ----\n";
    std::cout << "Shadow corruption: " << world.shadows["shadow_001"].corruption << "\n";

    BattleSystem battle(hero, world.shadows["shadow_001"]);
    battle.set_actions(actions);
    battle.run();

    // If healed, register and save
    if (world.shadows["shadow_001"].healed) {
        world.on_shadow_healed("shadow_001");
        bool ok = SaveSystem::save_world(world, "save_demo.json");
        std::cout << "Saved world to save_demo.json (ok=" << (ok ? "true" : "false") << ")\n";
    }

    for (const auto& id : world.recovered_memories) {
        std::cout << "Recovered memory id: " << id << "\n";
    }

    std::cout << "Demo finished.\n";
    return 0;
}
