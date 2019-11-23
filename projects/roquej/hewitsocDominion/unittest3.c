// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Ambassador Unit Test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int seed = 1000;

    // set card array
    int k[10] = {ambassador, minion, feast, gardens, mine, remodel, smithy, village, adventurer, great_hall};

    // declare the coin arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
    printf("Begin Unit Test for playAmbassador:\n");

    // testing choice to return 2 copies with 2 other players
    struct gameState G;
    initializeGame(3, k, seed, &G); // initialize game
    while(G.handCount[0] > 0) { // empty first player's hand
        discardCard(0, 0, &G, 0);
    }
    while(G.handCount[1] > 0) { // empty second player's hand
        discardCard(0, 1, &G, 0);
    }
    while(G.handCount[2] > 0) { // empty third player's hand
        discardCard(0, 2, &G, 0);
    }
    gainCard(ambassador, &G, 2, 0); // add ambassador card to first player's hand
    for(int i = 0; i < 2; i++) { // add two copies of minion card to first player's hand
        gainCard(minion, &G, 2, 0); 
    }    
    int preSupply = G.supplyCount[minion];
    playAmbassador(minion, 2, 0, 0, &G);
    int postSupply = G.supplyCount[minion];

    if(preSupply == postSupply) { // assert supply count is correctly adjusted in function
        printf("Error- The supply count of the returned card wasn't appropriately adjusted.\n");
    }
    
    // assert other players received a copy of the returned card
    int count1 = 0;
    int count2 = 0;
    for(int i = 1; i <= 2; i++) {
        count2 = 0;
        for(int j = 0; j < G.handCount[i]; j++) {
            if(G.hand[i][j] == minion) {
                count2++;
            }
        }
        if(count2 == 0) {
            count1++;
        }
    }
    if(count1 > 0) {
        printf("Error- Not all other players received a copy of the returned card when they should have.\n");
    }

    // assert copies of cards were removed from the player's hand
    count1 = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == minion) {
            count1++;
        }
    }
    if(count1 > 0) {
        printf("Error- Not all copies of the returned card was removed from the first player's hand.\n");
    }

    // testing for invalid choice2 parameter
    struct gameState G1;
    initializeGame(2, k, seed, &G1); // initialize game
    gainCard(ambassador, &G1, 2, 0); // add ambassador card to first player's hand
    for(int i = 0; i < 2; i++) { // add two copies of minion card to first player's hand
        gainCard(minion, &G1, 2, 0);
    }
    if(playAmbassador(minion, -1, 0, 0, &G1) != -1) { // assert choice2 = -1
        printf("Error- invalid choice2 = -1 parameter did not return -1.\n");
    }
    if(playAmbassador(minion, 3, 0, 0, &G1) != -1) { // assert choice2 = 3
        printf("Error- invalid choice2 = 3 parameter did not return -1.\n");
    }

    // testing for insufficient copies in player's hand
    struct gameState G2;
    initializeGame(2, k , seed, &G2); // initialize game
    while(G2.handCount[0] > 0) { // empty first player's hand
        discardCard(0, 0, &G2, 0);
    }
    gainCard(ambassador, &G2, 2, 0); // add ambassador card to first player's hand
    gainCard(minion, &G1, 2, 0);  // add minion card to first player's hand
    if(playAmbassador(minion, 2, 0, 0, &G2) != -1) { // assert -1 is thrown for insufficient quantity of chosen card
        printf("Error- insufficient quantity of chosen card to return.\n");
    }

    printf("playAmbassador Unit Test completed.\n\n");
    return 0;
}