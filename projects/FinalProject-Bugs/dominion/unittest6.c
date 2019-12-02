#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int handCreate(struct gameState*, int, int);

// Bug # 6 feast coin update bug

int main (int argc, char** argv) {

    printf("Begin Testing for Bug #6\n");

    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall };
    struct gameState G;
    int numPlayers = 2;
    int p1 = 0;
    int r = initializeGame(numPlayers, k, 4, &G); // initialize a new game
    if(r == -1)
        printf("-Error: Can't initialize Game\n");    
    else {
        int numHand = 2;
        handCreate(&G, numHand, 3);
        G.coins = updateCoins(p1, &G, 0);
        int coins = G.coins;
        cardEffect(feast, mine, 0, 0, &G, 0, 0);

        if(coins != G.coins) {
            printf("-Error: Bug #6 Wrong number of coins\n");
        }
        if(numHand >= G.handCount[p1])
            printf("-Error: Bug #6 didn't draw card\n");
    }
    printf("Test completed!\n\n");
    return 0;
}

int handCreate(struct gameState *G, int handMax, int deckMax) {
    enum CARD deck[] = {smithy, copper, village};
    int temp;
    for (int i = 0; i < G->numPlayers; i++) {
        G->handCount[i] = 0;
        for (int j = 0; j < handMax; j++) {
            temp = rand() % 3;
            G->hand[i][j] = deck[temp];
            G->handCount[i]++; 
        }

        G->deckCount[i] = 0;
        for (int j = 0; j < deckMax; j++) {
            temp = rand() % 3;
            G->deck[i][j] = deck[temp];
            G->deckCount[i]++;
        }
    }
    return 0;
}