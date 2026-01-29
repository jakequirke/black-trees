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