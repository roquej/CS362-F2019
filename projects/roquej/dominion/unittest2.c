// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Minion Unit Test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int seed = 1000;

    // set card array
    int k[10] = {minion, council_room, feast, gardens, mine, remodel, smithy, village, adventurer, great_hall};

    // declare the coin arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
    printf("Begin Unit Test for playMinion:\n");

    // testing choice to gain 2 coins
    struct gameState G;
    initializeGame(2, k, seed, &G); // initialize game
    while(G.handCount[0] > 0) { // empty first player's hand
        discardCard(0, 0, &G, 0);
    }
    gainCard(minion, &G, 2, 0); // add minion card to first player's hand
    int preCoins = G.coins;
    int preNumActions = G.numActions;
    playMinion(1, 0, 0, 0, &G); // play the refactored function
    int postCoins = G.coins;
    int postNumActions = G.numActions;
    if(preCoins + 2 != postCoins) { // assertion for number of coins added
        printf("Error- when choosing to add 2 coins, number of coins added was incorrect.\n");
    }
    if(preNumActions + 1 != postNumActions) { // assertion for number of actions added
       printf("Error- number of actions added was incorrect.\n"); 
    }

    // testing choice to discard hand and draw 4 cards
    struct gameState H;
    initializeGame(2, k, seed, &H); // initialize game
    while(H.handCount[0] > 0) { // empty first player's hand
        discardCard(0, 0, &G, 0);
    }
    while(H.handCount[1] < 5) { // get second player's hand size to 5 cards
        gainCard(0, &H, 2, 1);
    }
    gainCard(minion, &H, 2, 0); // add minion card to first player's hand
    playMinion(0, 1, 0, 0, &H);
    if(H.handCount[1] != 4) { // check second player redraws 4 cards
        printf("Error- when first player chooses to discard hand, second player did not redraw 4 cards.\n");
    }

    printf("playMinion Unit Test completed.\n\n");
    return 0;
}