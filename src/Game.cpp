#include <iostream>
#include <random>
#include <sqlite3.h>
#include <string>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../inc/Game.h"
#include "../inc/Greeting.h"
#include "../inc/Agent.h"

Game::Game() {
    // Seed random.
    srand(time(0));

    // Initialization Parameters
    this->db_string = "db/sqlite3.db";
    this->equilibrium = 0.85;
    this->num_agents = 10;
    this->num_connection = 3;

    std::cout << "Initializing... ";
    this->validate_initialization_params();
    std::cout << "done." << std::endl;

    std::cout << "Recording game start... ";
    this->record_game_start();
    std::cout << "done." << std::endl;

    std::cout << "Creating Agents... ";
    this->create_and_store_agents();
    std::cout << "done." << std::endl;

    std::cout << "Connecting Agents... ";
    this->connect_agents();
    std::cout << "done." << std::endl;

    std::cout << "Recording connections... ";
    this->record_connections();
    std::cout << "done." << std::endl;

    this->is_equilibrium();

    // Possibly use later.
    // this->greeting_rank.insert(std::pair<Greeting, int>(Greeting::BOW, 2));
    // this->greeting_rank.insert(std::pair<Greeting, int>(Greeting::KISS, 0));
    // this->greeting_rank.insert(std::pair<Greeting, int>(Greeting::SHAKE, 1));

    // this->greeting_prevalence.insert(std::pair<Greeting, int>(Greeting::BOW, 1));
    // this->greeting_prevalence.insert(std::pair<Greeting, int>(Greeting::KISS, 0));
    // this->greeting_prevalence.insert(std::pair<Greeting, int>(Greeting::SHAKE, 3));
}

void Game::connect_agents() {
    for (int i = 0; i < this->agents.length(); i++) {
        Agent *agent = &(this->agents[i]);

        for (int j = 0; j < this->num_connection;) {
            Agent *rand_agent = this->get_rand_agent();
            bool added = agent->connect(rand_agent);
            if (added) ++j;
        }
    }
}

void Game::create_and_store_agents() {
    // Create and store Agents.
    for (int i = 0; i < this->num_agents;) {
        Agent agent = Agent(++i);
        this->agents.push(agent);
    }
}

Agent *Game::get_rand_agent() {
    return &(this->agents[ rand() % this->num_agents ]);
}

// Check each greeting. If anyone has a ratio greater than or
// equal to equalibrium, return true.
bool Game::is_equilibrium() {
    int greeting_sum = 0;
    double greeting_ratio = 0;
    Agent *agent;

    for (int greeting = BOW; greeting <= SHAKE; greeting++) {
        greeting_sum = 0;

        for (int i = 0; i < this->agents.length(); i++) {
            agent = &(this->agents[i]);

            if (agent->get_greeting() == greeting) {
                greeting_sum++;
            }
        }

        greeting_ratio = greeting_sum/(double)this->num_agents;
        if (greeting_ratio >= this->equilibrium) return true;
    }

    return false;
}

void Game::record_connections() {
    Agent *agent;
    sqlite3 *conn;
    sqlite3_stmt *stmt;
    int rc;
    Array<int> id_arr;
    std::string ids;

    try {
        rc = sqlite3_open(this->db_string, &conn);

        if (rc) {
            exit(rc);
        }

        const char *sql = "INSERT INTO agent_connections (agent, connections, game) " \
            "VALUES (?, ?, (SELECT MAX(rowid) FROM games))";

        for (int i = 0; i < this->agents.length(); i++) {
            sqlite3_prepare_v2(conn, sql, -1, &stmt, 0);
            sqlite3_exec( conn, "BEGIN TRANSACTION", 0, 0, 0 );
            agent = &(this->agents[i]);
            id_arr = agent->get_connected_ids();
            ids = "";

            for (int j = 0; j < id_arr.length(); j++) {
                ids = ids + std::to_string(id_arr[j]) + ",";
            }

            sqlite3_bind_int(stmt, 1, agent->get_id());
            // String length less one to remove the trailing comma.
            sqlite3_bind_text(stmt, 2, ids.c_str(), strlen(ids.c_str()) - 1, 0);
            sqlite3_step(stmt);
            sqlite3_exec(conn, "END TRANSACTION", 0, 0, 0);
            sqlite3_finalize(stmt);
        }

        sqlite3_close(conn);
    }
    catch (int err) {
        std::cout << "Game::record_game_start Exception: " << err << std::endl;
    }
}

void Game::record_game_start() {
    sqlite3 *conn;
    int rc;
    sqlite3_stmt *stmt;

    const char *sql =
        "INSERT INTO games (num_agents, num_connections, start) " \
        "VALUES (?, ?, ?);"
    ;

    try {
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
    catch (int err) {
        std::cout << "Game::record_game_start Exception: " << err << std::endl;
    }
}

void Game::validate_initialization_params() {
    return;
}
