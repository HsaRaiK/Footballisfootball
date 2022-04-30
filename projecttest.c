#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdint.h>
struct Clubs{
    char name;
    double budget;
    int transferList[5][3];
};
struct Agents{
    double forward[10];
    double midfielder[10];
    double defender[10];
    double goalkeeper[10];
};

struct Agents AgentArr[4];
int agentIndx = 0;
struct Clubs ClubArr[5]; 
int clubIndx = 0;

double getTeamBudget(){
    int budgets[5] = {10,20,30,40,50} ;
    int budgetindx = (int)(rand() % (5)); // Random budget of either 10,20,30,40,50
    return (double)budgets[budgetindx];
}
int minCost( double players[10]){
    double min = 1000000;
    int minIndex;
    for (int i = 0; i < 10; i++)
    {
        if(players[i] != 0 && players[i] < min){
            min = players[i];
            minIndex = i;
        }
    }
    return minIndex;
}
int transfer(int p , int clubIndex, int agentNum, int playerCount){
    //call scout here...
    int playerPos = p; // position of the wanted player
    int minIndex;
    switch(playerPos){    
        case 1://forward    
            printf("looking for forward - agent %d\n", agentNum);
            minIndex = minCost(AgentArr[agentNum].forward); // finding and returning the index of cheapest player
            printf("Agent %d , forward, Min Index: %d\n", agentNum, minIndex);  
            // Check if club has enough budget, if it has, remove player from agent list 
            // update budget and set transfer value to 1
            // i update the transfer value twice, because i thought i would write the code differently
            // but now i'm too lazy to change it, and the code works so...
            if(ClubArr[clubIndex].budget >= AgentArr[agentNum].forward[minIndex]){
                ClubArr[clubIndex].budget -= AgentArr[agentNum].forward[minIndex];
                AgentArr[agentNum].forward[minIndex] = 0;
                ClubArr[clubIndex].transferList[playerCount][2] = 1;
                printf("forward transferred!, budget : %.2f\n", ClubArr[clubIndex].budget);
                return 1;
            }
            break;    
        case 2://midfielder     
            printf("looking for Midfielder - agent %d\n", agentNum);
            minIndex = minCost(AgentArr[agentNum].midfielder);
            printf("Agent %d , Midfielder, Min Index: %d\n", agentNum, minIndex);    
            if(ClubArr[clubIndex].budget >= AgentArr[agentNum].midfielder[minIndex]){
                ClubArr[clubIndex].budget -= AgentArr[agentNum].midfielder[minIndex];
                AgentArr[agentNum].midfielder[minIndex] = 0;
                ClubArr[clubIndex].transferList[playerCount][2] = 1;
                printf("midfielder transferred!, budget : %.2f\n", ClubArr[clubIndex].budget);
                return 1;
            }
            break;    
        case 3://defender    
            printf("looking for Defender - agent %d\n", agentNum);
            minIndex = minCost(AgentArr[agentNum].defender); 
            printf("Agent %d , Midfielder, Min Index: %d\n", agentNum, minIndex);  
            if(ClubArr[clubIndex].budget >= AgentArr[agentNum].defender[minIndex]){
                ClubArr[clubIndex].budget -= AgentArr[agentNum].defender[minIndex];
                AgentArr[agentNum].defender[minIndex] = 0;
                ClubArr[clubIndex].transferList[playerCount][2] = 1;
                printf("defender transferred!, budget : %.2f\n", ClubArr[clubIndex].budget);
                return 1;
            }     
            break;  
        case 4://goalkeeper  
            printf("looking for Goalkeeper - agent %d\n", agentNum);
            minIndex = minCost(AgentArr[agentNum].goalkeeper);
            printf("Agent %d , goalkeeper, Min Index: %d\n", agentNum, minIndex);   
            if(ClubArr[clubIndex].budget >= AgentArr[agentNum].goalkeeper[minIndex]){
                ClubArr[clubIndex].budget -= AgentArr[agentNum].goalkeeper[minIndex];
                AgentArr[agentNum].goalkeeper[minIndex] = 0;
                ClubArr[clubIndex].transferList[playerCount][2] = 1;
                printf("goalkeeper transferred!, budget : %.2f\n", ClubArr[clubIndex].budget);
                return 1;
            }  
            break;  
        default:    
            break;
    }    
    return 0; 
}

void* clubThread(){
    int curIndx = clubIndx++;
    ClubArr[curIndx].budget = getTeamBudget();
    ClubArr[curIndx].name = 'A' + curIndx;
    int max = 0;
    printf("Team %c: %.1fM $\n",ClubArr[curIndx].name, ClubArr[curIndx].budget);
    // tansferlist = 5 players [0-5], agent number and player position [2] = {agentnum, playerpos}
    for (int i = 0; i < 5; i++)
    {
        ClubArr[curIndx].transferList[i][0] = (rand() % (3 + 1)); // 0-3
        ClubArr[curIndx].transferList[i][1] = (rand() % (4 + 1 - 1) + 1); // 1-4
        ClubArr[curIndx].transferList[i][2] = 0; // 0 -> not transferred, 1 -> transferred
        printf(" | Agent: %d, Player: %d |",ClubArr[curIndx].transferList[i][0],ClubArr[curIndx].transferList[i][1] );
    }
    printf("\n");
    int playerPos;
    for (int i = 0; i < 5; i++)
    {
        // call agent, if no transfer is made, wait a bit and try again.
        if( ClubArr[curIndx].transferList[i][0] == 0){
            //call agent 0
            playerPos = ClubArr[curIndx].transferList[i][1];
            printf("agent 0\n");
            ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i); 
            if(ClubArr[curIndx].transferList[i][2] == 0){
                //wait();
                ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
                if(ClubArr[curIndx].transferList[i][2] == 0){
                    break; // if can't make the transfer, end transfer period
                }
            }
        }
        if( ClubArr[curIndx].transferList[i][0] == 1){
            playerPos = ClubArr[curIndx].transferList[i][1];
            printf("agent 1\n");
            ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
            if(ClubArr[curIndx].transferList[i][2] == 0){
                //wait();
                ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
                if(ClubArr[curIndx].transferList[i][2] == 0){
                    break; // if can't make the transfer, end transfer period
                }
            }
        }
        if( ClubArr[curIndx].transferList[i][0] == 2){
            playerPos = ClubArr[curIndx].transferList[i][1];
            printf("agent 2\n");
            ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
            if(ClubArr[curIndx].transferList[i][2] == 0){
                //wait();
                ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
                if(ClubArr[curIndx].transferList[i][2] == 0){
                    break; // if can't make the transfer, end transfer period
                }
            }
        }
        if( ClubArr[curIndx].transferList[i][0] == 3){
            playerPos = ClubArr[curIndx].transferList[i][1];
            printf("agent 3\n");
            ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
            if(ClubArr[curIndx].transferList[i][2] == 0){
                //wait();
                ClubArr[curIndx].transferList[i][2] = transfer(playerPos,curIndx,ClubArr[curIndx].transferList[i][0], i);
                if(ClubArr[curIndx].transferList[i][2] == 0){
                    break; // if can't make the transfer, end transfer period
                }
            }
        }
    }
}



void* initialAgentList(){
    
    int curIndx = agentIndx++;
    //Random initial amount of players 1-5 for each position
    int forwardAmount = (rand() % (5 + 1 - 1) + 1);
    int midfielderAmount = (rand() % (5 + 1 - 1) + 1);
    int defenderAmount = (rand() % (5 + 1 - 1) + 1);
    int goalkeeperAmount = (rand() % (5 + 1 - 1) + 1);
    for (int i = 0; i <= forwardAmount; i++)
    {
        AgentArr[curIndx].forward[i] = (double)(rand() % (20 + 1 - 4) + 4);
    }
    for (int i = 0; i <= midfielderAmount; i++)
    {
        AgentArr[curIndx].midfielder[i] = (double)(rand() % (20 + 1 - 4) + 4);
    }
    for (int i = 0; i <= defenderAmount; i++)
    {
        AgentArr[curIndx].defender[i] = (double)(rand() % (20 + 1 - 4) + 4);
    }
    for (int i = 0; i <= goalkeeperAmount; i++)
    {
        AgentArr[curIndx].goalkeeper[i] = (double)(rand() % (20 + 1 - 4) + 4);
    }
}

void* printagents()
{
    printf(" ============ \t ============ \t ============ \t ============ \n");
    for (int i = 0; i < 4; i++)
    {
        printf("Agent %d\n", i);
        printf("Forward[ ");
        for (int j = 0; j < 10; j++)
        {
            printf("%0.1f - ",AgentArr[i].forward[j]);
        }
        printf("]\nmidfielder[ ");
        for (int k = 0; k < 10; k++)
        {
            printf("%0.1f - ",AgentArr[i].midfielder[k]);
        }
        printf("]\ndefender[ ");
        for (int g = 0; g < 10; g++)
        {
            printf("%0.1f - ",AgentArr[i].defender[g]);
        }
        printf("]\ngoalkeeper[ ");
        for (int h = 0; h < 10; h++)
        {
            printf("%0.1f - ",AgentArr[i].goalkeeper[h]);
        }
        printf("]\n\n");
        
    }
    printf(" ============ \t ============ \t ============ \t ============ \n");
}

int main(){

    time_t t;
    srand((unsigned) time(&t));
    pthread_t clubsTid[5];
    pthread_t agentsTid[4];
    //create the player lists for each agent on their own thread
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&agentsTid[i], NULL, initialAgentList, NULL);
    }
    //wait for the agents to make their initial list
    for (int i = 0; i < 4; i++)
    {
        pthread_join(agentsTid[i], NULL);
    }
    printagents();
    //each clubs lists and budgets are randomly generated and their transfer process
    for (int i = 0; i < 1; i++)
    {
        pthread_create(&clubsTid[i], NULL, clubThread, NULL);
    }
     for (int i = 0; i < 1; i++)
    {
        pthread_join(clubsTid[i], NULL);
    }
    printagents();
}