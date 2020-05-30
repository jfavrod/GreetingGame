#include <iostream>
#include <random>
#include <sqlite3.h>
#include <time.h>
#include <unistd.h>
#include "../inc/Game.h"
#include "../inc/Greeting.h"
#include "../inc/Agent.h"

Game::Game() {
    // Seed random.
    srand(time(0));

    this->db_string = "db/sqlite3.db";
    this->num_agents = 5;
    this->num_connection = 3;

    this->validate_initialization_params();
    this->record_game_start();
    this->create_and_store_agents();

    // Possibly use later.
    // this->greeting_rank.insert(std::pair<Greeting, int>(Greeting::BOW, 2));
    // this->greeting_rank.insert(std::pair<Greeting, int>(Greeting::KISS, 0));
    // this->greeting_rank.insert(std::pair<Greeting, int>(Greeting::SHAKE, 1));

    // this->greeting_prevalence.insert(std::pair<Greeting, int>(Greeting::BOW, 1));
    // this->greeting_prevalence.insert(std::pair<Greeting, int>(Greeting::KISS, 0));
    // this->greeting_prevalence.insert(std::pair<Greeting, int>(Greeting::SHAKE, 3));

}

void Game::connect_agents() {
    // Make connections between agents.
    for (int i = 0; i < this->agents.length(); i++) {
        Agent agent = this->agents[i];

        for (int j = 0; j < this->num_connection; j++) {
            
        }
    }
}

void Game::create_and_store_agents() {
    // Create and store Agents.
    for (int i = 0; i < this->num_agents;) {
        Agent agent = Agent(++i);
        std::cout << agent.to_string() << std::endl;
        this->agents.push(agent);
    }
}

Agent *Game::get_rand_agent() {
    return &(this->agents[ rand() % this->num_agents ]);
}

void Game::record_game_start() {
    sqlite3 *conn;
    int rc;
    sqlite3_stmt *stmt;

    char * sql =
        "INSERT INTO games (num_agents, num_connections, start) " \
        "VALUES (?, ?, ?);"
    ;

    rc = sqlite3_open(this->db_string, &conn);

    if (rc) {
        exit(rc);
    }

    sqlite3_prepare_v2(conn, sql, -1, &stmt, 0);
    sqlite3_exec( conn, "BEGIN TRANSACTION", 0, 0, 0 );
    sqlite3_bind_int(stmt, 1, this->num_agents);
    sqlite3_bind_int(stmt, 2, this->num_connection);
    sqlite3_bind_int(stmt, 3, time(0));
    sqlite3_step(stmt);
    sqlite3_exec(conn, "END TRANSACTION", 0, 0, 0);
    sqlite3_finalize(stmt);

    sqlite3_close(conn);
}

void Game::validate_initialization_params() {
    return;
}
