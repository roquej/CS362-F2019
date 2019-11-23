// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Baron Unit Test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int seed = 1000;

    // set card array
    int k[10] = {baron, council_room, feast, gardens, mine, remodel, smithy, village, adventurer, great_hall};

    // declare the coin arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
    printf("Begin Unit Test for playBaron:\n");

    // testing choice to gain an estate
    struct gameState G;
    initializeGame(2, k, seed, &G); // initialize game
    gainCard(baron, &G, 2, 0);
    int preEstateCount = G.supplyCount[estate];
    int preNumBuys = G.numBuys;
    playBaron(0, 0, &G);
    int postEstateCount = G.supplyCount[estate];
    int postNumBuys = G.numBuys;
    // assertions
    if(preEstateCount != postEstateCount + 1) {
        printf("Error- supply count of estate is not decremented properly when choosing to gain an estate.\n");
    }
    if(preNumBuys + 1 != postNumBuys) {
        printf("Error- Buys is not increased by 1 when choosing to gain an estate.\n");
    }

    // testing choice to discard an estate when estate is second card in hand
    struct gameState F;
    initializeGame(2, k, seed, &F); // initialize game
    gainCard(estate, &F, 2, 0);
    gainCard(baron, &F, 2, 0);
    int preCoins = F.coins;
    while(F.handCount[0] > 0) { // empty first player's hand
        discardCard(0, 0, &F, 0);
    }
    gainCard(baron, &F, 2, 0); // add baron card to first player's hand
    gainCard(estate, &F, 2, 0); // add estate card to first player's hand
    playBaron(1, 0, &F);
    int postCoins = F.coins;
    // assertions
    if(preCoins + 4 != postCoins) {
        printf("Error- coins is not increased by 4 when choosing to discard an estate and estate is second card in hand.\n");
    }
    for(int i = 0; i < F.handCount[0]; i++) {
        if(F.hand[0][i] == estate) {
            printf("Error- estate card not discarded when choosing to discard an estate and estate is second card in hand.\n");       
        }
    }

    // testing choice to discard an estate with no estate card in hand
    struct gameState H;
    initializeGame(2, k, seed, &H); // initialize game
    while(H.handCount[0] > 0) { // empty first player's hand
        discardCard(0, 0, &H, 0);
    }
    gainCard(baron, &H, 2, 0); // add baron card to first player's hand
    playBaron(1, 0, &H);

    // assertions
    int count = 0;
    for(int i = 0; i < H.discardCount[0]; i++) {
        if(H.discard[0][i] == estate) {
            count++;
        }
    }
    if(count == 0) {
        printf("Error- estate card not added to discard pile when choosing to discard an estate with no estate card in hand.\n");       
    }

    printf("playBaron Unit Test completed.\n\n");
    return 0;
}