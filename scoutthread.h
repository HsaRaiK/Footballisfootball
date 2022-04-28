// this goes in global
pthread_mutex_t scoutlock;

//this is the method 

//the errors are because of the missing libraries and other stuff

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
                case '0':
                    switch(priceStrat)
                    {
                        case '0':
                            AgentArr[newPlayerChance-4].forward[0] -= 0.5;
                        case '1':
                            AgentArr[newPlayerChance-4].forward[0] += 1;
                    }
                case '1':
                    switch(priceStrat)
                    {
                        case '0':
                            AgentArr[newPlayerChance-4].midfielder[0] -= 0.5;
                        case '1':
                            AgentArr[newPlayerChance-4].midfielder[0] += 1;
                    }
                case '2':
                    switch(priceStrat)
                    {
                        case '0':
                            AgentArr[newPlayerChance-4].defender[0] -= 0.5;
                        case '1':
                            AgentArr[newPlayerChance-4].defender[0] += 1;
                    }
                case '3':
                    switch(priceStrat)
                    {
                        case '0':
                            AgentArr[newPlayerChance-4].goalkeeper[0] -= 0.5;
                        case '1':
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
