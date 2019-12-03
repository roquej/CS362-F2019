// Thomas Sugimoto

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int handCreate(struct gameState*, int, int);

// Bug # 8 bonus coins incorrectly used

int main (int argc, char** argv) {

    printf("Begin Testing for Bug #8\n");

    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall };
    struct gameState G;
    int numPlayers = 2;
    int p1 = 0;
    //int p2 = 1;
    int r = initializeGame(numPlayers, k, 4, &G); // initialize a new game
    G.whoseTurn = p1;
    if(r == -1)
        printf("-Error: Can't initialize Game\n");    
    else {
        int numHand = 5;
        handCreate(&G, numHand, 7);
        int bonus = 0;
        int numCoins = G.coins; 

         // Check for tribute
        bonus = 0;
        G.coins = 0;
        updateCoins(G.whoseTurn, &G, bonus);
        numCoins = G.coins;
        cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
        if(G.coins != numCoins + 4)
            printf("-Error: Bug #8 tribute's bonus coin count is incorrect(expected: %d, actual:%d,bonus:%d)\n", numCoins + 4, G.coins, bonus);

        // Check for Baron
        bonus = 0;
        G.coins = 0;
        G.hand[p1][0] = estate;
        updateCoins(G.whoseTurn, &G, bonus);
        numCoins = G.coins;
        cardEffect(baron, 1, 0, 0, &G, 0, &bonus);
        if(G.coins != numCoins + 4)
            printf("-Error: Bug #8 baron's bonus coin count is incorrect(expected: %d, actual:%d,bonus:%d)\n", numCoins + 4, G.coins, bonus);

        // Check for minion
        bonus = 0;
        G.coins = 0;
        G.hand[p1][0] = minion;
        updateCoins(G.whoseTurn, &G, bonus);
        numCoins = G.coins;
        cardEffect(minion, 1, 0, 0, &G, 0, &bonus);
        if(G.coins != numCoins + 2)
            printf("-Error: Bug #8 minion's bonus coin count is incorrect(expected: %d, actual:%d,bonus:%d)\n", numCoins + 2, G.coins, bonus);

        
        // Check for embargo
        bonus = 0;
        G.coins = 0;
        updateCoins(G.whoseTurn, &G, bonus);
        numCoins = G.coins;
        cardEffect(embargo, 0, 0, 0, &G, 0, &bonus);
        if(G.coins != numCoins + 2)
            printf("-Error: Bug #8 embargo's bonus coin count is incorrect(expected: %d, actual:%d,bonus:%d)\n", numCoins + 2, G.coins, bonus);

        // Check for cutpurse
        bonus = 0;
        G.coins = 0;
        updateCoins(G.whoseTurn, &G, bonus);
        numCoins = G.coins;
        cardEffect(cutpurse, 0, 0, 0, &G, 0, &bonus);
        if(G.coins != numCoins + 2)
            printf("-Error: Bug #8 cutpurse's bonus coin count is incorrect(expected: %d, actual:%d,bonus:%d)\n", numCoins + 2, G.coins, bonus);
        
    }
    printf("Test completed!\n\n");
    return 0;
}

int handCreate(struct gameState *G, int handMax, int deckMax) {
    enum CARD deck[] = {silver, copper, gold};
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
            temp = j % 3;
            G->deck[i][j] = deck[temp];
            G->deckCount[i]++;
        }
    }
    return 0;
}