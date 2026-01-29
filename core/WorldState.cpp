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