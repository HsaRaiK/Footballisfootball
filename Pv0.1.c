#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
pthread_mutex_t scoutlock;


double getTeamBudget(){
    int budgets[5] = {10,20,30,40,50} ;
    int budgetindx = (int)(rand() % (5)); // Random budget of either 10,20,30,40,50
    return (double)budgets[budgetindx];
}



void* scout()
{
    pthread_mutex_lock(&scoutlock);
    int newPlayerChance = (rand() % (10));
    int newPlayerPos    = (rand() %  (4));
    int positioner = 0;
    if (newPlayerChance < 4)
    {
        if(newPlayerPos == 0)
        {
            for (int i=0 ; i<10; i++)
            {
                if(AgentArr[newPlayerChance].forward != 0)
                {
                    positioner++;
                }
            }
            AgentArr[newPlayerChance].forward[positioner+1] = (double)(rand() % (20 + 1 - 4) + 4);
            positioner = 0;
        }
         if(newPlayerPos == 1)
        {
            for (int i=0 ; i<10; i++)
            {
                if(AgentArr[newPlayerChance].midfielder != 0)
                {
                    positioner++;
                }
            }
            AgentArr[newPlayerChance].midfielder[positioner+1] = (double)(rand() % (20 + 1 - 4) + 4);
            positioner = 0;
        }
         if(newPlayerPos == 2)
        {
            for (int i=0 ; i<10; i++)
            {
                if(AgentArr[newPlayerChance].defender != 0)
                {
                    positioner++;
                }
            }
            AgentArr[newPlayerChance].defender[positioner+1] = (double)(rand() % (20 + 1 - 4) + 4);
            positioner = 0;
        }
         if(newPlayerPos == 3)
        {
            for (int i=0 ; i<10; i++)
            {
                if(AgentArr[newPlayerChance].goalkeeper != 0)
                {
                    positioner++;
                }
            }
            AgentArr[newPlayerChance].goalkeeper[positioner+1] = (double)(rand() % (20 + 1 - 4) + 4);
            positioner = 0;
        }
    }
    else if( newPlayerChance<8 && newPlayerChance >3)
    {
        int priceStrat = rand() % 2;
        switch(newPlayerPos)
            {
                case 0:
                    switch(priceStrat)
                    {
                        case 0:
                            AgentArr[newPlayerChance-4].forward[0] -= 0.5;
                        case 1:
                            AgentArr[newPlayerChance-4].forward[0] += 1;
                    }
                case 1:
                    switch(priceStrat)
                    {
                        case 0:
                            AgentArr[newPlayerChance-4].midfielder[0] -= 0.5;
                        case 1:
                            AgentArr[newPlayerChance-4].midfielder[0] += 1;
                    }
                case 2:
                    switch(priceStrat)
                    {
                        case 0:
                            AgentArr[newPlayerChance-4].defender[0] -= 0.5;
                        case 1:
                            AgentArr[newPlayerChance-4].defender[0] += 1;
                    }
                case 3:
                    switch(priceStrat)
                    {
                        case 0:
                            AgentArr[newPlayerChance-4].goalkeeper[0] -= 0.5;
                        case 1:
                            AgentArr[newPlayerChance-4].goalkeeper[0] += 1;
                    }    
                
            }
    }
    else
    {
        printf("No pricechange, no playeradded\n");
    }
    pthread_mutex_unlock(&scoutlock);
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
        ClubArr[curIndx].transferList[i][0] = (rand() % (4 + 1)); // 0-4
        ClubArr[curIndx].transferList[i][1] = (rand() % (4 + 1 - 1) + 1); // 1-4
        ClubArr[curIndx].transferList[i][2] = 0; // 0 -> not transferred, 1 -> transferred
        printf(" | Agent: %d, Player: %d |",ClubArr[curIndx].transferList[i][0],ClubArr[curIndx].transferList[i][1] );
    }
    printf("\n");
    for (int i = 0; i < 5; i++)
    {
        if( ClubArr[curIndx].transferList[i][0] == 0){
            //call agent 0
        }
        if( ClubArr[curIndx].transferList[i][0] == 1){

        }
        if( ClubArr[curIndx].transferList[i][0] == 2){

        }
        if( ClubArr[curIndx].transferList[i][0] == 3){

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
    for (int i=0; i<4; i++)
    {
        //int F_size = sizeof(AgentArr[i].forward);
        int ordergiver = 0;
        printf("Agent %d :  Forward players : \n",i+1);
        for (int j=0; j<10; j++)
        {
            if (AgentArr[i].forward[j] != 0)
            {
                printf("- pl %d : %.2lf M -",j-ordergiver+1,AgentArr[i].forward[j] );
            }
            else
            {
                ordergiver++;
            }    
        }
        printf("\n \n");
        ordergiver = 0;
        printf("Agent %d :  Midfielder players : \n",i+1 );
        for (int j=0; j<10; j++)
        {
            if (AgentArr[i].midfielder[j] != 0)
            {
                printf("- pl %d : %.2lf M -",j-ordergiver+1,AgentArr[i].midfielder[j] );
            }
            else
            {
                ordergiver++;
            }
        }
        printf("\n \n");
        ordergiver = 0;
        printf("Agent %d :  Defender Players : \n", i+1);
        for (int j=0; j<10; j++)
        {
            if (AgentArr[i].defender[j] != 0)
            {
                printf("- pl %d : %.2lf M -",j-ordergiver+1,AgentArr[i].defender[j] );
            }
            else
            {
                ordergiver++;
            }
        }
        printf("\n \n");
        ordergiver = 0;
        printf("Agent %d :  Goal keepers : \n", i+1);
        for (int j=0; j<10; j++)
        {
            if (AgentArr[i].goalkeeper[j] != 0)
            {
                printf("- pl %d : %.2lf M -",j-ordergiver+1,AgentArr[i].goalkeeper[j] );
            }
            else
            {
                ordergiver++;
            }
        }
        printf("\n \n");
        ordergiver = 0;
        printf(" --- \n");
    }
    printf(" ============ \t ============ \t ============ \t ============ \n");
}

int main(){

    time_t t;
    srand((unsigned) time(&t));
    pthread_t clubsTid[5];
    pthread_t agentsTid[4];
    pthread_t scouts;

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
    printagents(AgentArr);
    
    //each clubs lists and budgets are randomly generated and their transfer process
    for (int i = 0; i < 5; i++)
    {
        pthread_create(&clubsTid[i], NULL, clubThread, NULL);
    }
     for (int i = 0; i < 5; i++)
    {
        pthread_join(clubsTid[i], NULL);
    }
    pthread_create(&scouts, NULL, scout, NULL );


}