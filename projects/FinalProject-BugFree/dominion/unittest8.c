#include "dominion.h"
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
    int p2 = 1;
    int r = initializeGame(numPlayers, k, 4, &G); // initialize a new game
    G.whoseTurn = p1;
    if(r == -1)
        printf("-Error: Can't initialize Game\n");    
    else {
        int numHand = 5;
        handCreate(&G, numHand, 7);

        int numCoins = G.coins;        
        // Check for Baron
        G.hand[p1][0] = estate;
        cardEffect(baron, 1, 0, 0, &G, 0, 0);
        if(G.coins != numCoins + 4)
            printf("-Error: Bug #8 baron's bonus coin count is incorrect (expected: %d, actual:%d)-\n", numCoins + 4, G.coins);

        // Check for minion
        numCoins = G.coins;
        cardEffect(minion, 1, 0, 0, &G, 0, 0);
        if(G.coins != numCoins + 2)
            printf("-Error: Bug #8 minion's bonus coin count is incorrect (expected: %d, actual:%d)\n", numCoins + 2, G.coins);

        // Check for tribute
        numCoins = G.coins;
        G.deck[p2][7] = copper;
        G.deck[p2][6] = gold;
        G.deck[p2][8] = silver;
        cardEffect(tribute, 0, 0, 0, &G, 0, 0);
        if(G.coins != numCoins + 4)
            printf("-Error: Bug #8 tribute's bonus coin count is incorrect(expected: %d, actual:%d)\n", numCoins + 4, G.coins);
        
        // Check for embargo
        numCoins = G.coins;
        cardEffect(embargo, 0, 0, 0, &G, 0, 0);
        if(G.coins != numCoins + 2)
            printf("-Error: Bug #8 embargo1's bonus coin count is incorrect(expected: %d, actual:%d)\n", numCoins + 2, G.coins);

        // Check for cutpurse
        numCoins = G.coins;
        cardEffect(cutpurse, 0, 0, 0, &G, 0, 0);
        if(G.coins != numCoins + 2)
            printf("-Error: Bug #8 embargo2's bonus coin count is incorrect(expected: %d, actual:%d)\n", numCoins + 2, G.coins);
        
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