// JRPG C++ Starter — reorganized to requested file layout
// ------------------------------------------------------------
// This single canvas document now contains the contents for each file
// mapped to the requested directory layout. Copy each section into the
// corresponding file in your project tree.
//
// Directory outline provided by you:
//
//  /core
//    BattleSystem.cpp
//    HealAction.cpp
//    WorldState.cpp
//    SaveSystem.cpp
//  /entities
//    Player.cpp
//    Shadow.cpp
//  /data
//    heal_actions.json
//    regions.json
//    memories.json
//  /ui
//    BattleUI.gd
//    DialogueUI.gd
//
// Note: For clarity and simplicity, small header contents are included
// as comments above each .cpp implementation. When converting to real files,
// split headers into .h/.hpp if you prefer. The code is intentionally
// dependency-free and minimal.
// ------------------------------------------------------------

/* ======================================================================
   core/HealAction.cpp
   ----------------------------------------------------------------------
   Header (conceptual): core/HealAction.h
   ----------------------------------------------------------------------
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

   Implementation below (core/HealAction.cpp)
   ====================================================================== */

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

/* ======================================================================
   core/BattleSystem.cpp
   ----------------------------------------------------------------------
   Header (conceptual): core/BattleSystem.h
   ----------------------------------------------------------------------
   #ifndef BATTLE_SYSTEM_H
   #define BATTLE_SYSTEM_H
   
   #include <vector>
   #include "../entities/Player.h"
   #include "../entities/Shadow.h"
   #include "core/HealAction.cpp" // conceptual include
   
   class BattleSystem {
   public:
       enum class State { Idle, PlayerTurn, ExecuteAction, Resolve, End };
       BattleSystem(Player &p, Shadow &s);
       void set_actions(const std::vector<HealAction> &actions);
       void run();
   private:
       Player &player;
       Shadow &shadow;
       State state;
       std::vector<HealAction> actions;
       void enter_state(State s);
       void on_player_turn();
       void on_execute_action(const HealAction &act);
       void on_resolve();
   };
   
   #endif // BATTLE_SYSTEM_H

   Implementation below (core/BattleSystem.cpp)
   ====================================================================== */

#include <iostream>
#include <vector>
#include <string>
#include "../entities/Player.h"
#include "../entities/Shadow.h"
// HealAction is expected to be available (see core/HealAction.cpp section above)

class BattleSystem {
public:
    enum class State { Idle, PlayerTurn, ExecuteAction, Resolve, End };
    BattleSystem(Player &p, Shadow &s) : player(p), shadow(s), state(State::Idle) {}

    void set_actions(const std::vector<HealAction> &acts) { actions = acts; }

    void run() {
        enter_state(State::PlayerTurn);
        while (state != State::End) {
            switch (state) {
                case State::PlayerTurn: on_player_turn(); break;
                case State::ExecuteAction: /* handled inline */ break;
                case State::Resolve: on_resolve(); break;
                default: enter_state(State::End); break;
            }
        }
    }

private:
    Player &player;
    Shadow &shadow;
    State state;
    std::vector<HealAction> actions;

    void enter_state(State s) { state = s; }

    void on_player_turn() {
        std::cout << "Player MP: " << player.mp << " / " << player.max_mp << "
";
        int idx = -1;
        for (size_t i = 0; i < actions.size(); ++i) {
            const auto &a = actions[i];
            std::cout << i << ") " << a.name << " (MP " << a.mp_cost << ")
";
            if (idx == -1 && player.mp >= a.mp_cost) idx = static_cast<int>(i);
        }
        if (idx == -1) {
            std::cout << "No usable actions. Passing turn.
";
            enter_state(State::Resolve);
            return;
        }
        std::cout << "Using action: " << actions[idx].name << "
";
        enter_state(State::ExecuteAction);
        on_execute_action(actions[idx]);
    }

    void on_execute_action(const HealAction &act) {
        auto res = act.execute(shadow, player);
        std::cout << res.second << "
";
        enter_state(State::Resolve);
    }

    void on_resolve() {
        if (shadow.healed) {
            enter_state(State::End);
            std::cout << "Battle ended: shadow healed.
";
        } else {
            enter_state(State::PlayerTurn);
        }
    }
};

/* ======================================================================
   core/WorldState.cpp
   ----------------------------------------------------------------------
   Implementation of a tiny world registry that holds shadows and recovered
   memory order. This file corresponds to core/WorldState.cpp and its
   conceptual header core/WorldState.h.
   ====================================================================== */

#include <unordered_map>
#include <vector>
#include <string>

struct Memory {
    std::string id;
    std::string title;
    std::string text;
};

struct Shadow {
    std::string id;
    int32_t corruption;
    Memory memory;
    bool healed;
    Shadow() = default;
    Shadow(const std::string &i, int32_t c, const Memory &m)
        : id(i), corruption(c), memory(m), healed(false) {}
    bool apply_heal(int32_t amount) {
        if (healed) return false;
        int32_t old = corruption;
        corruption -= amount;
        if (corruption <= 0) { corruption = 0; healed = true; }
        return corruption != old;
    }
};

struct WorldState {
    std::unordered_map<std::string, Shadow> shadows;
    std::vector<std::string> recovered_memories;

    void add_shadow(const Shadow &s) { shadows.emplace(s.id, s); }

    bool on_shadow_healed(const std::string &shadow_id) {
        auto it = shadows.find(shadow_id);
        if (it == shadows.end()) return false;
        if (it->second.healed) {
            recovered_memories.push_back(it->second.memory.id);
            return true;
        }
        return false;
    }
};

/* ======================================================================
   core/SaveSystem.cpp
   ----------------------------------------------------------------------
   Small, dependency-free save implementation: core/SaveSystem.cpp
   ====================================================================== */

#include <string>
#include <fstream>
#include <sstream>

struct SaveSystem {
    static bool save_world(const WorldState &world, const std::string &path) {
        std::ofstream f(path, std::ios::out | std::ios::trunc);
        if (!f.is_open()) return false;
        f << "{
";
        f << "  \"recovered_memories\": [";
        for (size_t i = 0; i < world.recovered_memories.size(); ++i) {
            f << '"' << escape(world.recovered_memories[i]) << '"';
            if (i + 1 < world.recovered_memories.size()) f << ", ";
        }
        f << "],
";
        f << "  \"shadows\": {
";
        size_t cnt = 0;
        for (const auto &kv : world.shadows) {
            const Shadow &s = kv.second;
            f << "    \"" << escape(s.id) << "\": {
";
            f << "      \"corruption\": " << s.corruption << ",
";
            f << "      \"healed\": " << (s.healed ? "true" : "false") << ",
";
            f << "      \"memory\": {
";
            f << "        \"id\": \"" << escape(s.memory.id) << "\",
";
            f << "        \"title\": \"" << escape(s.memory.title) << "\",
";
            f << "        \"text\": \"" << escape(s.memory.text) << "\"
";
            f << "      }
";
            f << "    }";
            ++cnt;
            if (cnt < world.shadows.size()) f << ",
"; else f << "
";
        }
        f << "  }
";
        f << "}
";
        f.close();
        return true;
    }
private:
    static std::string escape(const std::string &in) {
        std::ostringstream o;
        for (char c : in) {
            switch (c) {
                case '\': o << "\\"; break;
                case '"': o << "\\""; break;
                case '
': o << "\n"; break;
                default: o << c; break;
            }
        }
        return o.str();
    }
};

/* ======================================================================
   entities/Player.cpp
   ----------------------------------------------------------------------
   A small player resource struct. Put in entities/Player.cpp or split header/cpp.
   ====================================================================== */

#include <string>
#include <cstdint>

struct Player {
    std::string name;
    int32_t max_mp;
    int32_t mp;

    Player() = default;
    Player(const std::string &n, int32_t m) : name(n), max_mp(m), mp(m) {}

    bool consume_mp(int32_t amount) {
        if (mp >= amount) { mp -= amount; return true; }
        return false;
    }

    void restore_mp(int32_t amount) {
        mp += amount;
        if (mp > max_mp) mp = max_mp;
    }
};

/* ======================================================================
   entities/Shadow.cpp
   ----------------------------------------------------------------------
   Shadow entity implementation (entities/Shadow.cpp). Note: a Shadow holds
   a Memory struct for the recovered memory.
   ====================================================================== */

#include <string>
#include <cstdint>

struct Memory {
    std::string id;
    std::string title;
    std::string text;
};

struct Shadow {
    std::string id;
    int32_t corruption; // 0..100
    Memory memory;
    bool healed;

    Shadow() = default;
    Shadow(const std::string &i, int32_t c, const Memory &m)
        : id(i), corruption(c), memory(m), healed(false) {}

    bool apply_heal(int32_t amount) {
        if (healed) return false;
        int32_t old = corruption;
        corruption -= amount;
        if (corruption <= 0) { corruption = 0; healed = true; }
        return corruption != old;
    }
};

/* ======================================================================
   data/heal_actions.json
   ----------------------------------------------------------------------
   Minimal JSON file describing heal actions. Import into your engine or
   parse with a JSON library when ready. Kept compact so you can read it.
   ====================================================================== */

// data/heal_actions.json (text file)
{
  "actions": [
    { "id": "heal_01", "name": "Mend", "mp_cost": 5, "heal_amount": 20 },
    { "id": "heal_02", "name": "Soothing Hymn", "mp_cost": 8, "heal_amount": 35 }
  ]
}

/* ======================================================================
   data/regions.json
   ----------------------------------------------------------------------
   Example region metadata: used by world loader to know which shadows live where.
   ====================================================================== */

// data/regions.json
{
  "regions": [
    {
      "id": "isle_001",
      "name": "Whispering Shallows",
      "shadows": [ "shadow_001" ]
    }
  ]
}

/* ======================================================================
   data/memories.json
   ----------------------------------------------------------------------
   Central store of memory text used by shadows.
   ====================================================================== */

// data/memories.json
{
  "memories": [
    {
      "id": "mem_001",
      "title": "A Forgotten Lullaby",
      "text": "You remember the melody your mother hummed while stitching old coats."
    }
  ]
}

/* ======================================================================
   ui/BattleUI.gd
   ----------------------------------------------------------------------
   Skeleton Godot GDScript UI that would call into your C++ core through
   GDExtension bindings. This is intentionally minimal — it shows where
   to call into the exposed API and how to update visuals.
   ====================================================================== */

# ui/BattleUI.gd
# extends Control
#
# var world_api
# var current_shadow_id = ""
#
# func _ready():
#     world_api = Engine.get_singleton("WorldAPI") # example binding
#
# func start_battle(player_id, shadow_id):
#     current_shadow_id = shadow_id
#     var actions = world_api.get_available_actions()
#     update_action_buttons(actions)
#     update_shadow_ui()
#
# func on_action_pressed(action_id):
#     var result = world_api.perform_action(action_id, current_shadow_id)
#     $MessageLabel.text = result.message
#     if result.healed:
#         show_memory(world_api.get_memory_for_shadow(current_shadow_id))

/* ======================================================================
   ui/DialogueUI.gd
   ----------------------------------------------------------------------
   Minimal dialogue UI skeleton for showing recovered memories.
   ====================================================================== */

# ui/DialogueUI.gd
# extends Control
#
# func show_memory(memory_dict):
#     $Title.text = memory_dict.title
#     $Body.text = memory_dict.text
#     visible = true

/* ======================================================================
   Notes & next steps
   ----------------------------------------------------------------------
   - The code is intentionally organized so each "section" maps to a file
     path in your requested structure. When moving to a real repo, split the
     structs and implementations into .h/.cpp files and include them with
     correct relative includes.

   - For Godot GDExtension: keep most core logic in these plain C++ structs
     and write thin wrapper classes (godot::Object) that forward calls.

   - If you want, I can now:
     1) Produce separate files ready to paste (one file per code block), or
     2) Generate a CMakeLists.txt that builds this project as a single
        demonstration executable, or
     3) Create the GDExtension wrapper files and example .gd scripts wired to
        call them.

   Tell me which next step and I will generate those files directly.
   ====================================================================== */
