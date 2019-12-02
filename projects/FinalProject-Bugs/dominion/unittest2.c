// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Unit Test 

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int k[10] = {mine, tribute, feast, gardens, baron, remodel, smithy, village, adventurer, great_hall};
    int b[1] = {0};
    int countCopper, countSilver, countGold, countMine, num;

    printf("Begin Unit Test for Bug #2:\n");
    struct gameState G0, G;

    // testing trashing a copper for a gold
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = mine;
    G.handCount[0] = 2;

    // assert copper and mine cards are in first player's hand
    countCopper = 0;
    countMine = 0;
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
    num = cardEffect(mine, 0, gold, 0, &G, 1, b);
    
    // assertion
    if(num != -1) {
        printf("Bug found: -1 was not returned when attempting to trash a copper for a gold.\n");
    } else {
        printf("Success: -1 was returned when attempting to trash a copper for a gold.\n");
    }
    
    // testing trashing a silver for a copper
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = mine;
    G.handCount[0] = 2;
    // assert silver and mine cards are in first player's hand
    countSilver = 0;
    countMine = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == silver) {
            countSilver++;
        } else if(G.hand[0][i] == mine) {
            countMine++;
        }
    }
    if(countSilver == 0) {
        printf("Testing error: silver card was never added to first player's hand.\n");
    }
    if(countMine == 0) {
        printf("Testing error: mine card was never added to first player's hand.\n");
    }

    // call mine case of cardEffect
    num = cardEffect(mine, 0, copper, 0, &G, 1, b);
    
    // assertion
    if(num == -1) {
        printf("Bug found: -1 was incorrectly returned when attempting to trash a silver for a copper.\n");
    } else {
        printf("Success: -1 was not returned when attempting to trash a silver for a copper.\n");
    }

    // testing trashing a gold for a silver
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = gold;
    G.hand[0][1] = mine;
    G.handCount[0] = 2;
    // assert gold and mine cards are in first player's hand
    countGold = 0;
    countMine = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == gold) {
            countGold++;
        } else if(G.hand[0][i] == mine) {
            countMine++;
        }
    }
    if(countGold == 0) {
        printf("Testing error: gold card was never added to first player's hand.\n");
    }
    if(countMine == 0) {
        printf("Testing error: mine card was never added to first player's hand.\n");
    }

    // call mine case of cardEffect
    num = cardEffect(mine, 0, silver, 0, &G, 1, b);
    
    // assertion
    if(num == -1) {
        printf("Bug found: -1 was incorrectly returned when attempting to trash a gold for a silver.\n");
    } else {
        printf("Success: -1 was not returned when attempting to trash a gold for a silver.\n");
    }

    // testing trashing a gold for a copper
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = gold;
    G.hand[0][1] = mine;
    G.handCount[0] = 2;
    // assert gold and mine cards are in first player's hand
    countGold = 0;
    countMine = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == gold) {
            countGold++;
        } else if(G.hand[0][i] == mine) {
            countMine++;
        }
    }
    if(countGold == 0) {
        printf("Testing error: gold card was never added to first player's hand.\n");
    }
    if(countMine == 0) {
        printf("Testing error: mine card was never added to first player's hand.\n");
    }

    // call mine case of cardEffect
    num = cardEffect(mine, 0, copper, 0, &G, 1, b);
    
    // assertion
    if(num == -1) {
        printf("Bug found: -1 was incorrectly returned when attempting to trash a gold for a copper.\n");
    } else {
        printf("Success: -1 was not returned when attempting to trash a gold for a silver.\n");
    }

    printf("Bug #2 Unit Test completed.\n\n");
    return 0;
}