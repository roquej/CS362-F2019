// Thomas Sugimoto
// sugimoth@oregonstate.edu
// CS362-F2019
// Unit Test

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int handCreate(struct gameState*, int, int);

// Bug # 7 tribute loop overruns the array

int main (int argc, char** argv) {

    printf("Begin Testing for Bug #7\n");

    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall };
    struct gameState G;
    int numPlayers = 2;
    int p1 = 0;
    int r = initializeGame(numPlayers, k, 4, &G); // initialize a new game
    if(r == -1)
        printf("-Error: Can't initialize Game\n");    
    else{
        int numHand = 5;
        int bonus = 0;
        int numActions = G.numActions;
        handCreate(&G, numHand, 7);
        
        int out = cardEffect(tribute, 0, 0, 0, &G, 0, &bonus);
        if(out != 0) {
            printf("-Error: Bug #7 tribute didn't finish\n");
        }
        
        if(numActions != G.numActions) {
            printf("-Error: Bug #7 tribute has the wrong numActions (expected:%d, actual:%d)\n",
                    numActions, G.numActions);
            printf("        hand (expected:%d, actual:%d)\n", numHand, G.handCount[p1]);
            //printf("        coins (expected:%d, actual:%d)\n", numCoins, G.coins);
        }
        
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
            temp = rand() % 3;
            G->deck[i][j] = deck[temp];
            G->deckCount[i]++;
        }
    }
    return 0;
}