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