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

void Agent::connect(Agent *agent) {
    if (agent->get_id() != this->id) {
        this->connections.push(agent);
    }

    this->connection_count++;
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
