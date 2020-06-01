#ifndef GAME_H
#define GAME_H
#include <map>
#include "./Agent.h"
#include "../inc/Array/Array.h"
#include "../inc/Greeting.h"

class Game {
    private:
    const char * db_string;
    double equilibrium;
    int id;
    int num_agents;
    int num_connection;
    Array<Agent> agents;

    // Possibly use later.
    // std::map<Greeting, int> greeting_rank;
    // std::map<Greeting, int> greeting_prevalence;

    void connect_agents();
    void create_and_store_agents();
    /**
     * Pick an agent at random from the agents collection.
     */
    Agent *get_rand_agent();
    bool is_equilibrium();
    void record_connections();
    void record_game_start();
    void validate_initialization_params();

    public:
    Game();
};

#endif
