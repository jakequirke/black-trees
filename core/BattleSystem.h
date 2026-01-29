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