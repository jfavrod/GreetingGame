#ifndef AGENT_H
#define AGENT_H
#include <string>
#include "../inc/Array/Array.h"
#include "../inc/Greeting.h"

int static count = 0;

class Agent {
    protected:
    int connection_count;
    Array<Agent*> connections;
    Greeting greeting;
    int id;
    int klout;

    public:
    Agent(int id);
    Agent(int id, Greeting greeting);
    Agent(int id, Greeting greeting, int klout);
    bool connect(Agent *agent);
    Greeting get_greeting();
    int get_id();
    int get_klout();
    void greet(Agent agent);
    /** Check if given agent is connected to this agent. */
    bool is_connected(Agent *);
    std::string to_string();
};

#endif
