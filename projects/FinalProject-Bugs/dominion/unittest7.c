#include "dominion.h"
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
    int p2 = 1;
    int r = initializeGame(numPlayers, k, 4, &G); // initialize a new game
    if(r == -1)
        printf("-Error: Can't initialize Game\n");    
    else{
        int numHand = 5;
        int numActions = G.numActions;
        handCreate(&G, numHand, 7);
        G.deck[p2][0] = copper;
        G.deck[p2][1] = gold;
        int out = cardEffect(tribute, 0, 0, 0, &G, 0, 0);
        if(out != 0) {
            printf("-Error: Bug #7 tribute didn't finish\n");
        }
        if(numActions != G.numActions) {
            printf("-Error: Bug #7 tribute has the incorrecct number of actions\n");
        }
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