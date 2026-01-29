#pragma once

#include <string>
#include <cstdint>

struct Memory {
    std::string id;
    std::string title;
    std::string text;
};

struct Shadow {
    std::string id;
    int32_t corruption;   // 0 = healed
    Memory memory;
    bool healed;

    Shadow(const std::string& id, int32_t corruption, const Memory& memory);

    // Returns true if corruption changed
    bool apply_heal(int32_t amount);
};
