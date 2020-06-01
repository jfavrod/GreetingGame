CREATE TABLE games (
    -- rowid uniquely ids game.
    end INTEGER,
    num_agents INTEGER,
    num_connections INTEGER,
    start INTEGER
);

CREATE TABLE agent_connections (
    agent INTEGER,
    connections TEXT,
    game INTEGER
);
