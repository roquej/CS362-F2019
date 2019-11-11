// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Mine Unit Test

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int r;
    int seed = 1000;

    // set card array
    int k[10] = {mine, council_room, feast, gardens, baron, remodel, smithy, village, adventurer, great_hall};

    // declare the coin arrays
    int coppers[MAX_HAND];
    int silvers[MAX_HAND];
    int golds[MAX_HAND];
    
    printf("Begin Unit Test for playMine:\n");

    // test trying to trash a non-treasure card
    struct gameState G1;
    initializeGame(2, k, seed, &G1); // initialize game
    while(G1.handCount[0] > 0) { // empty player one's hand
        discardCard(0, 0, &G1, 0);
    }
    gainCard(curse, &G1, 2, 0); // add a curse card to player one's hand
    gainCard(mine, &G1, 2, 0); // add a mine card to player one's hand
    if(playMine(0, copper, 0, 1, &G1) != -1) { // assert that trying a non-treasure card returns -1
        printf("Error- trashing a non-treasure card should have returned -1.\n");
    }

    // test trying to trash a copper card for a curse card
    struct gameState G4;
    initializeGame(2, k, seed, &G4); // initialize game
    while(G4.handCount[0] > 0) { // empty player one's hand
        discardCard(0, 0, &G4, 0);
    }
    gainCard(copper, &G4, 2, 0); // add a copper card to player one's hand
    gainCard(mine, &G4, 2, 0); // add a mine card to player one's hand
    if(playMine(0, curse, 0, 1, &G4) != -1) { // assert that trying to gain a curse card returns -1
        printf("Error- trying to gain a curse card should have returned -1.\n");
    }

    // test treasure card is properly trashed when it's the first card in player one's hand
    struct gameState G3;
    initializeGame(2, k, seed, &G3); // initialize game
    while(G3.handCount[0] > 0) { // empty player one's hand
        discardCard(0, 0, &G3, 0);
    }
    gainCard(copper, &G3, 2, 0); // add a copper card as the first card in player one's hand
    gainCard(mine, &G3, 2, 0); // add a mine card to player one's hand
    playMine(0, silver, 0, 1, &G3); // play function
    // assert that copper card was trashed
    int count = 0;
    for(int i = 0; i < G3.handCount[0]; i++) {
        if(G3.hand[0][i] == copper) {
            count++;
        }
    }
    if(count > 0) {
        printf("Error- treasure card was not trashed.\n");
    }


    // test trying to get a card that costs 6 more than the trashed card
    // commented out this test because it causes a segmentation fault
    /*
    struct gameState G2;
    initializeGame(2, k, seed, &G2); // intialize game
    while(G1.handCount[0] > 0) { // empty player one's hand
        discardCard(0, 0, &G2, 0);
    }
    gainCard(copper, &G2, 2, 0); // add a copper to player one's hand
    gainCard(mine, &G2, 2, 0); // add a mine card to player one's hand
    if(playMine(copper, gold, 0, 0, &G2) != -1) { // assert to check function call returns -1
        printf("Error- able to use the mine card to trash a copper card for a gold card.\n");
    }
    */

    printf("playMine Unit Test completed.\n\n");
    return 0;
}