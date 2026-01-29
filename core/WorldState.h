#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "../entities/Shadow.h"

struct WorldState {
    // Shadows stored by id
    std::unordered_map<std::string, Shadow> shadows;

    // Collected memory ids (in order)
    std::vector<std::string> recovered_memories;

    WorldState() = default;

    // Add a shadow to the world registry
    void add_shadow(const Shadow& s);

    // If the shadow is healed, push the memory id and return true
    bool on_shadow_healed(const std::string& shadow_id);
};
