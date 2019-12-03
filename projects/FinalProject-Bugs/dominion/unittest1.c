// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Unit Test 1

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    // declare arrays
    int k[10] = {mine, tribute, feast, gardens, mine, remodel, smithy, village, adventurer, great_hall};
    int b[1] = {0};
    
    printf("Begin Unit Test for Bug #1:\n");

    struct gameState G;
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.handCount[0] = 2;

    // assert copper and mine cards are in first player's hand
    int countCopper = 0;
    int countMine = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            countCopper++;
        } else if(G.hand[0][i] == mine) {
            countMine++;
        }
    }
    if(countCopper == 0) {
        printf("Testing error: copper card was never added to first player's hand.\n");
    }
    if(countMine == 0) {
        printf("Testing error: mine card was never added to first player's hand.\n");
    }
    
    // call mine case of cardEffect
    cardEffect(mine, 0, silver, 0, &G, 1, b);

    // assertion
    if(G.playedCards[1] == copper) {
        printf("Bug found: copper card was never trashed from the player's hand.\n");
    } else {
        printf("Success: copper card was correctly trashed from the player's hand.\n");
    }

    printf("Bug #1 Unit Test completed.\n\n");
    return 0;
}