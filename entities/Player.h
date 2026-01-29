#pragma once
#include <string>
#include <cstdint>

struct Player {
    std::string name;
    int32_t max_mp;
    int32_t mp;

    Player(const std::string& name, int32_t max_mp);

    bool consume_mp(int32_t amount);
    void restore_mp(int32_t amount);
};
