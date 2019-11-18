// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// random test generator- baron card

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char* argv[]) {
    printf("Begin random testing of baron card:\n");

    srand(time(NULL));
    
    // declare variables
    int choice1, currentPlayer, numPlayers,
        preBuys, preCoins, postBuys, postCoins;
    int wrongBuys = 0;
    int wrongCoins = 0;
    struct gameState g0, g;
    int k[10] = {baron, council_room, feast, gardens, mine,
                 remodel, smithy, village, adventurer, great_hall};

    for(int i = 0; i < 10000; i++) {
        memcpy(&g, &g0, sizeof(struct gameState));
        numPlayers = 2 + rand() % 3;
        initializeGame(numPlayers, k, 1000, &g);
        currentPlayer = rand() % numPlayers;
        choice1 = rand() % 100;
        if(choice1 < 50) {
            choice1 = 0;
        } else choice1 = 1;
        gainCard(baron, &g, 2, currentPlayer);

        if(rand() % 100 < 50) {
            g.supplyCount[estate] = 0;
        }

        preBuys = g.numBuys;
        preCoins = g.coins;

        playBaron(choice1, currentPlayer, &g);

        postCoins = g.coins;
        postBuys = g.numBuys;
        if(preBuys + 1 != postBuys) {
            wrongBuys++;
        }

        if(choice1 == 1) {
            if(preCoins + 4 != postCoins) {
                wrongCoins++;
            }
        } else {
            if(preCoins != postCoins) {
                wrongCoins++;
            }
        }
    }

    printf("In 10000 iterations:\n");
    printf("%d iterations had an inappropriate change in buys.\n", wrongBuys);
    printf("%d iterations had an inappropriate change in coins.\n", wrongCoins);
    printf("End random testing of baron card.\n\n");
    return 0;
}