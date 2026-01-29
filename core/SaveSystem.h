#pragma once
#include <string>

#include "WorldState.h"

struct SaveSystem {
    // Save to a simple JSON-like file (dependency-free). Use a proper JSON lib later.
    static bool save_world(const WorldState& world, const std::string& path);
};
