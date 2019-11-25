// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// random test generator- minion card

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char* argv[]) {
    printf("Begin random testing of minion card:\n");

    srand(time(NULL));
    
    // declare variables
    int choice1, choice2, currentPlayer, numPlayers, 
        preCoins, postCoins, preActions, postActions;
    int wrongActions = 0;
    int wrongCoins = 0;
    int wrongHandCount = 0;
    struct gameState g0, g;
    int k[10] = {minion, council_room, feast, gardens, mine,
                 remodel, smithy, village, adventurer, great_hall};
    for(int i = 0; i < 1000; i++) {
        memcpy(&g, &g0, sizeof(struct gameState));
    
        numPlayers = 2 + rand() % 3;
        initializeGame(numPlayers, k, 500, &g);
        currentPlayer = rand() % numPlayers;

        if(rand() % 100 < 50) {
            choice1 = 1;
            choice2 = 0;
        } else {
            choice1 = 0;
            choice2 = 1;
        }

        gainCard(minion, &g, 2, currentPlayer);

        preCoins = g.coins;
        preActions = g.numActions;

        for(int j = 0; j < 5; j++) {
            drawCard(currentPlayer, &g);
        }

        minionRefactor(choice1, choice2, currentPlayer, &g, 0);

        postCoins = g.coins;
        postActions = g.numActions;
        
        if(preActions + 1 != postActions) {
            wrongActions++;
        }

        if(choice1) {
            if(preCoins + 2 != postCoins) {
                wrongCoins++;
            }
        } else {
            if(preCoins != postCoins) {
                wrongCoins++;
            }
            if(g.handCount[currentPlayer] != 4) {
                wrongHandCount++;
            }
        }
    }

    printf("In 1000 iterations:\n");
    printf("%d iterations had an inappropriate change in actions.\n", wrongActions);
    printf("%d iterations had an inappropriate change in coins.\n", wrongCoins);
    printf("%d iterations had an inappropriate number of card draws for the current player.\n", wrongHandCount);
    printf("End random testing of minion card.\n\n");
    return 0;
}