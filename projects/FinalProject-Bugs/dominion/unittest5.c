#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int discardCreate(struct gameState*, int, int);

// Bug #5 Unit Test for ScoreFor

int main (int argc, char** argv) {

    printf("Begin Testing for Bug #5\n");

    // set up
    int k[10] = { adventurer, council_room, feast, gardens, mine
                , remodel, smithy, village, baron, great_hall };
    struct gameState G;
    int numPlayers = 2;
    int p1 = 0;
    int r = initializeGame(numPlayers, k, 4, &G); // initialize a new game
    if(r == -1) {
        printf("-Error: Can't initialize Game\n");
    }
    else {
        int realScore = discardCreate(&G, 5, 3);
        
        if(realScore != scoreFor(p1, &G)) {
            printf("-Error: Bug #5 \n");
        }
    }
    printf("Test completed!\n\n");
    return 0;
}

int discardCreate(struct gameState *G, int discardMax, int deckMax) {
    enum CARD deck[] = {gold, silver, smithy, gold, copper, village, copper};
    int score = 0;
    int temp;
    for (int i = 0; i < G->numPlayers; i++) {
        G->discardCount[i] = 0;
        for (int j = 0; j < discardMax; j++) {
            temp = rand() % 7;
            G->discard[i][j] = deck[temp];
            G->discardCount[i]++;
            if (temp == curse) {
                score = score - 1;
            };
            if (temp == estate) {
                score = score + 1;
            };
            if (temp == duchy) {
                score = score + 3;
            };
            if (temp == province) {
                score = score + 6;
            };
            if (temp == great_hall) {
                score = score + 1;
            };
            if (temp == gardens) {
                score = score + ( fullDeckCount(i, 0, G) / 10 );
            };
        }

        G->deckCount[i] = 0;
        for (int j = 0; j < deckMax; j++) {
            temp = rand() % 7;
            G->deck[i][j] = deck[temp];
            G->deckCount[i]++;
            if (temp == curse) {
                score = score - 1;
            };
            if (temp == estate) {
                score = score + 1;
            };
            if (temp == duchy) {
                score = score + 3;
            };
            if (temp == province) {
                score = score + 6;
            };
            if (temp == great_hall) {
                score = score + 1;
            };
            if (temp == gardens) {
                score = score + ( fullDeckCount(i, 0, G) / 10 );
            };
        }
    }
    return score;
}