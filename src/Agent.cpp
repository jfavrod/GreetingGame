#include <stdlib.h>
#include <string>
#include <time.h>
#include "../inc/Agent.h"

Agent::Agent(int id) {
    srand(time(0));

    this->id = id;
    this->greeting = Greeting(rand() % 3);
    this->klout = std::rand();
}

Agent::Agent(int id, Greeting greeting) {
    srand(time(0));
    this->id = id;
    this->greeting = greeting;
    this->klout = std::rand();
}

Agent::Agent(int id, Greeting greeting, int klout) {
    srand(time(0));
    this->id = id;
    this->greeting = greeting;
    this->klout = klout;
}

void Agent::connect(Agent *agent) {
    this->connections.push_back(agent);
}

Greeting Agent::get_greeting() {
    return this->greeting;
}

int Agent::get_id() {
    return this->id;
}

void Agent::greet(Agent agent) {
    return;
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
