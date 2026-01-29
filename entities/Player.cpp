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