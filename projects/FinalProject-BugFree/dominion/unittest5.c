// Thomas Sugimoto

#include "dominion.h"
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>


int discardCreate(struct gameState*, int, int, int);

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
        int realScore = discardCreate(&G, 4, 8, 3);
        
        if(realScore != scoreFor(p1, &G)) {
            printf("-Error: Bug #5 Expected:%d Actual:%d Num of cards=%d\n", 
                    realScore, scoreFor(p1, &G), G.handCount[p1]);
        }
    }
    printf("Test completed!\n\n");
    return 0;
}

int discardCreate(struct gameState *G, int handMax, int discardMax, int deckMax) {
    enum CARD deck[] = {gardens, silver, great_hall, gold, copper, village, copper, 
                        curse, duchy, province, estate};
    int score = 0;
    int temp;
    for (int i = 0; i < 1; i++) {
        G->handCount[i] = 0;
        for (int j = 0; j < handMax; j++) {
            temp = deck[rand() % 11];
            G->hand[i][j] = temp;
            G->handCount[i]++;
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

        G->discardCount[i] = 0;
        for (int j = 0; j < discardMax; j++) {
            temp = deck[rand() % 11];
            G->discard[i][j] = temp;
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
            temp = deck[rand() % 11];
            G->deck[i][j] = temp;
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