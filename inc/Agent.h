#ifndef AGENT_H
#define AGENT_H
#include <string>
#include <vector>

int static count = 0;

enum Greeting {
    bow,
    kiss,
    shake
};

class Agent {
    protected:
    std::vector<Agent *> connections;
    Greeting greeting;
    int id;
    int klout;

    public:
    Agent(int id);
    Agent(int id, Greeting greeting);
    Agent(int id, Greeting greeting, int klout);
    void connect(Agent *agent);
    Greeting get_greeting();
    int get_id();
    int get_klout();
    void greet(Agent agent);
    bool is_connected();
    std::string to_string();
};

#endif
