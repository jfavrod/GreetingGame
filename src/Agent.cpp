#include <stdlib.h>
#include <string>
#include <time.h>
#include "../inc/Agent.h"

Agent::Agent(int id) {
    this->id = id;
    this->greeting = Greeting(rand() % 3);
    this->klout = std::rand();
}

Agent::Agent(int id, Greeting greeting) {
    this->id = id;
    this->greeting = greeting;
    this->klout = std::rand();
}

Agent::Agent(int id, Greeting greeting, int klout) {
    this->id = id;
    this->greeting = greeting;
    this->klout = klout;
}

bool Agent::connect(Agent *agent) {
    if (agent->get_id() != this->id && !this->is_connected(agent)) {
        this->connections.push(agent);
        this->connection_count++;
        return true;
    }

    return false;
}

Greeting Agent::get_greeting() {
    return this->greeting;
}

int Agent::get_id() {
    return this->id;
}

int Agent::get_klout() {
    return this->klout;
}

void Agent::greet(Agent agent) {
    if (agent.get_klout() > this->klout) {
        this->greeting = agent.get_greeting();
    }
}

bool Agent::is_connected(Agent *agent) {
    for (int i = 0; i < this->connections.length(); i++) {
        if (this->connections[i]->get_id() == agent->get_id()) {
            return true;
        }
    }

    return false;
}

std::string Agent::to_string() {
    std::string str = "Agent:\n";
    str = str + "  id: " + std::to_string(this->id);
    str = str + "\n";
    str = str + "  greeting: " + std::to_string(this->greeting);
    str = str + "\n";
    str = str + "  klout: " += std::to_string(this->klout);
    str = str + "\n";
    return str;
}
