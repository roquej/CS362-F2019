// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// Unit Test 3

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <string.h>

/*
In the remodel case within the cardEffect function,
the if statement that compares the two choice statements needs to be switched (around Line #846).
*/

int main(int argc, char *argv[]) {
    int k[10] = {remodel, tribute, feast, gardens, mine, baron, smithy, village, adventurer, great_hall};
    int b[1] = {0};
    int countCopper, countSilver, countGold, countRemodel, num;

    printf("Begin Unit Test for Bug #3:\n");
    struct gameState G0, G;

    // testing trashing a copper for a gold
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = copper;
    G.hand[0][1] = remodel;
    G.handCount[0] = 2;

    // assert copper and remodel cards are in first player's hand
    countCopper = 0;
    countRemodel = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == copper) {
            countCopper++;
        } else if(G.hand[0][i] == remodel) {
            countRemodel++;
        }
    }
    if(countCopper == 0) {
        printf("Testing error: copper card was never added to first player's hand.\n");
    }
    if(countRemodel == 0) {
        printf("Testing error: remodel card was never added to first player's hand.\n");
    }

    // call remodel case of cardEffect
    num = cardEffect(remodel, 0, gold, 0, &G, 1, b);
    
    // assertion
    if(num != -1) {
        printf("Bug found: -1 was not returned when attempting to trash a copper for a gold.\n");
    } else {
        printf("Success: -1 was returned when attempting to trash a copper for a gold.\n");
    }

    // testing trashing a silver for a gold
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = remodel;
    G.handCount[0] = 2;

    // assert silver and remodel cards are in first player's hand
    countSilver = 0;
    countRemodel = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == silver) {
            countSilver++;
        } else if(G.hand[0][i] == remodel) {
            countRemodel++;
        }
    }
    if(countSilver == 0) {
        printf("Testing error: silver card was never added to first player's hand.\n");
    }
    if(countRemodel == 0) {
        printf("Testing error: remodel card was never added to first player's hand.\n");
    }

    // call remodel case of cardEffect
    num = cardEffect(remodel, 0, gold, 0, &G, 1, b);
    
    // assertion
    if(num != -1) {
        printf("Bug found: -1 was not returned when attempting to trash a silver for a gold.\n");
    } else {
        printf("Success: -1 was returned when attempting to trash a silver for a gold.\n");
    }

    // testing trashing a silver for a copper
    memcpy(&G, &G0, sizeof(struct gameState));
    initializeGame(2, k, 1000, &G);
    G.hand[0][0] = silver;
    G.hand[0][1] = remodel;
    G.handCount[0] = 2;
    // assert silver and remodel cards are in first player's hand
    countSilver = 0;
    countRemodel = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == silver) {
            countSilver++;
        } else if(G.hand[0][i] == remodel) {
            countRemodel++;
        }
    }
    if(countSilver == 0) {
        printf("Testing error: silver card was never added to first player's hand.\n");
    }
    if(countRemodel == 0) {
        printf("Testing error: remodel card was never added to first player's hand.\n");
    }

    // call remodel case of cardEffect
    num = cardEffect(remodel, 0, copper, 0, &G, 1, b);
    
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
    G.hand[0][1] = remodel;
    G.handCount[0] = 2;
    // assert gold and remodel cards are in first player's hand
    countGold = 0;
    countRemodel = 0;
    for(int i = 0; i < G.handCount[0]; i++) {
        if(G.hand[0][i] == gold) {
            countGold++;
        } else if(G.hand[0][i] == remodel) {
            countRemodel++;
        }
    }
    if(countGold == 0) {
        printf("Testing error: gold card was never added to first player's hand.\n");
    }
    if(countRemodel == 0) {
        printf("Testing error: remodel card was never added to first player's hand.\n");
    }

    // call remodel case of cardEffect
    num = cardEffect(remodel, 0, silver, 0, &G, 1, b);
    
    // assertion
    if(num == -1) {
        printf("Bug found: -1 was incorrectly returned when attempting to trash a gold for a silver.\n");
    } else {
        printf("Success: -1 was correctly returned when attempting to trash a gold for a silver.\n");
    }

    printf("Bug #3 Unit Test completed.\n\n");
    return 0;
}