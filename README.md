# Footballisfootball
I) Description:
    What can I do, sometimes? It is the football, that is the football !!!!
    During the transfer window, all football clubs are eager to transfer talented players into their clubs.
    There are four well-known famous football agents worldwide, who are responsible for managing
    contracts on behalf of players. Each agent manages players who play at four different positions:
    Forward, Midfielder, Defender, Goalkeeper. The current number of players and their positions for each
    agent are given below:
            Forward Midfielder Defender Goalkeeper
    Agent-1 2       2          2        1
    Agent-2 2       2          1        1
    Agent-3 2       1          1        2
    Agent-4 1       1          1        1

• During the transfer window of 2022-2023 season, 5 famous football clubs in Turkey (i.e., Club-A,
Club-B, Club-C, Club-D, Club-E) contact with these agents for their transfer lists.

• Each football club has a budget limit that can be used for the transfers: 10M, 20M, 30M, 40M, or
50M euros. The budget of each club is randomly assigned, and all or some portion of this budget
can be used to transfer players (but not more than the budget).

• Each football club has a transfer list of five players and the order of these players is important. For
instance, assume that the Club-C has the list: Agent-1: Forward, Agent-1: Midfielder, Agent-3:
Defender, Agent-2: Defender, and Agent-4: Goalkeeper. The football club first tries to transfer a
forward from Agent-1, then a midfielder from Agent-1, and then a defender from Agent-3 before
moving to the fourth and fifth players in its list.

• Each club negotiates with an agent for the position in focus and transfers the cheapest player among
all alternatives managed by the agent. In the first round, if the club does not have enough budget, it
waits for a period and negotiates with the agent one last time. If the transfer is completed in the first
or second round and the club has budget left, it moves to the next player in the list.

• A football club might transfer zero or more players, or complete its transfer list after the negotiations
made during the transfer window.

• The initial transfer cost of a player is in between 4M-20M euros. The cost cannot be more than 22M
euros or less than 3M euros.

• Each agent works with a scout who is responsible for searching new talents. At random periods, the
scout adds new players to the agent's management list by determining their transfer costs.

• At random periods, the scout also updates the costs of all players managed by the agent. The transfer
costs of a player can be increased by 1M euros or decreased by 500,000 euros or kept the same in a
single period. The kind and amount of update for each player is random. Once the update period
comes, the scout performs updates on all players.

• An agent can negotiate with at most two football clubs at a time (not more than that). During the
period when the scout is updating the player costs, the agent cannot negotiate with any club