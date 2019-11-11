// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Tribute Unit Test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int seed = 1000;

    // set card array
    int k[10] = {tribute, council_room, feast, gardens, mine, remodel, smithy, village, adventurer, great_hall};

    // declare the coin arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
    printf("Begin Unit Test for playTribute:\n");

    // testing....
    struct gameState G;
    initializeGame(2, k, seed, &G); // initialize game


    printf("playTribute Unit Test completed.\n\n");
    return 0;
}