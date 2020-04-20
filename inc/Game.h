#ifndef GAME_H
#define GAME_H
#include <vector>
#include "./Agent.h"

class Game {
    private:
    std::vector<Agent> agents;
    int num_agents;

    public:
    Game();
};

#endif
