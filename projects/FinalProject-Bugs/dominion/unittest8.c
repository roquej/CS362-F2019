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
    if(r == -1)
        printf("-Error: Can't initialize Game\n");    
    else {
        int numHand = 5;
        handCreate(&G, numHand, 7);
        
        int bonus = 5;
        // Check for Baron
        G.hand[p1][0] = estate;
        cardEffect(baron, 1, 0, 0, &G, 0, &bonus);
        if(bonus != 9)
            printf("-Error: Bug #8 baron's bonus coin count is incorrect\n");

        // Check for minion
        bonus = 5;
        cardEffect(minion, 1, 0, 0, &G, 0, &bonus);
        if(bonus != 7)
            printf("-Error: Bug #8 minion's bonus coin count is incorrect\n");

        // Check for tribute
        bonus = 5;
        G.deck[p2][0] = copper;
        G.deck[p2][1] = gold;
        cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
        if(bonus != 9)
            printf("-Error: Bug #8 tribute's bonus coin count is incorrect\n");
        
        // Check for embargo
        bonus = 5;
        cardEffect(embargo, 0, 0, 0, &G, 0, &bonus);
        if(bonus != 7)
            printf("-Error: Bug #8 embargo's bonus coin count is incorrect\n");

        // Check for cutpurse
        bonus = 5;
        cardEffect(cutpurse, 0, 0, 0, &G, 0, &bonus);
        if(bonus != 7)
            printf("-Error: Bug #8 embargo's bonus coin count is incorrect\n");
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