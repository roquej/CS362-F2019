// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Unit Test 4

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int k[10] = {remodel, tribute, feast, gardens, mine, baron, smithy, salvager, sea_hag, treasure_map};
    int gameOver;
    
    printf("Begin Unit Test for Bug #4:\n");
    struct gameState G0, G;

    // testing when sea_hag supply count is 0
    initializeGame(2, k, 1000, &G);
    // set curse and estate supply counts to 0
    G.supplyCount[curse] = 0;
    G.supplyCount[estate] = 0;
    // set sea_hag supply count to 0
    G.supplyCount[sea_hag] = 0;
    // call isGameOver
    gameOver = isGameOver(&G);
    if(!gameOver) {
        printf("Bug error: 1 was not returned when sea_hag supply is empty along with two other card supplies.\n");
    } else {
        printf("Success: 1 was returned with sea_hag supply empty along with two other card supplies.\n");
    }

    // testing when treasure_map supply count is 0
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    // set curse and estate supply counts to 0
    G.supplyCount[curse] = 0;
    G.supplyCount[estate] = 0;
    // set treasure_map supply count to 0
    G.supplyCount[treasure_map] = 0;
    // call isGameOver
    gameOver = isGameOver(&G);
    if(!gameOver) {
        printf("Bug error: 1 was not returned when treasure_map supply is empty along with two other card supplies.\n");
    } else {
        printf("Success: 1 was returned with treasure_map supply empty along with two other card supplies.\n");
    }

    // testing when supply count for sea_hag and treasure_map are all 0
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    G.supplyCount[curse] = 0;
    G.supplyCount[sea_hag] = 0;
    G.supplyCount[treasure_map] = 0;
    // call isGameOver
    gameOver = isGameOver(&G);
    if(!gameOver) {
        printf("Bug error: 1 was not returned when sea_hag and treasure_map supplies are empty along with another card's supply.\n");
    } else {
        printf("Success: 1 was returned when sea_hag and treasure_map supplies are empty along with another card's supply.\n");
    }

    printf("Bug #4 Unit Test completed.\n\n");
    return 0;
}