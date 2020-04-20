#include <iostream>
#include <unistd.h>
#include "../inc/Game.h"
#include "../inc/Agent.h"

Game::Game() {
    this->num_agents = 3;

    for (int i = 0; i < this->num_agents;) {
        Agent agent = Agent(++i);
        std::cout << agent.to_string() << std::endl;
        sleep(1);
    }
}
