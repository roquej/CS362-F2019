// Jonasel Roque
// roquej@oregonstate.edu
// CS362-F2019
// random test generator- tribute card

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"

int main(int argc, char* argv[]) {
    printf("Begin random testing of tribute card:\n");

    srand(time(NULL));
    
    // declare variables
    int currentPlayer, nextPlayer, numPlayers,
        preActions, postActions, preCoins, postCoins, preCards, postCards;
    int revealedCards[2];
    int hasEmptyDeck = 0;
    int numActions = 0;
    int numCoins = 0;
    int numCards = 0;
    int wrongActions = 0;
    int wrongCoins = 0;
    int wrongCards = 0;
    int firstCard;
    int secondCard;
    struct gameState g0, g;
    int k[10] = {minion, council_room, feast, gardens, mine,
                 remodel, smithy, village, adventurer, great_hall};

    for(int i = 0; i < 10000; i++) {
        memcpy(&g, &g0, sizeof(struct gameState));
        numActions = 0;
        numCoins = 0;
        numCards = 0;
        numPlayers = 2 + rand() % 3;
        initializeGame(numPlayers, k, 1000, &g);
        currentPlayer = rand() % numPlayers;
        nextPlayer = currentPlayer + 1;
        if(nextPlayer >= numPlayers) {
            nextPlayer = 0;
        }

        firstCard = rand() % 27;
        gainCard(firstCard, &g, 1, nextPlayer);
        secondCard = rand() % 27;
        gainCard(secondCard, &g, 1, nextPlayer);

        if(rand() % 100 < 10) {
            g.deckCount[nextPlayer] = 0;
            hasEmptyDeck = 1;
        }
        if(rand() % 100 < 10) {
            gainCard(rand() % 27, &g, 0, nextPlayer);
        } 

        preActions = g.numActions;
        preCoins = g.coins;
        preCards = g.handCount[currentPlayer];

        tributeRefactor(currentPlayer, nextPlayer, revealedCards, &g);

        postActions = g.numActions;
        postCoins = g.coins;
        postCards = g.handCount[currentPlayer];

        if(!hasEmptyDeck) {
            if(firstCard == copper || firstCard == silver || firstCard == gold) {
                numCoins += 2;
            } else if(firstCard == estate || firstCard == duchy || firstCard == province || firstCard == gardens || firstCard == great_hall) {
                numCards += 2;
            } else {
                numActions += 2;
            }
            if(firstCard != secondCard) {
                if(secondCard == copper || secondCard == silver || secondCard == gold) {
                    numCoins += 2;
                } else if(secondCard == estate || secondCard == duchy || secondCard == province || secondCard == gardens || secondCard == great_hall) {
                    numCards += 2;
                } else {
                    numActions += 2;
                }
            }
        }

        if(preActions + numActions != postActions) {
            wrongActions++;
        }
        if(preCoins + numCoins != postCoins) {
            wrongCoins++;
        }
        if(preCards + numCards != postCards) {
            wrongCards ++;
        }
    }

    printf("In 10000 iterations:\n");
    printf("%d iterations had an inappropriate change in actions.\n", wrongActions);
    printf("%d iterations had an inappropriate change in coins.\n", wrongCoins);
    printf("%d iterations had an inappropriate number of card draws for the current player.\n", wrongCards);
    printf("End random testing of tribute card.\n\n");
    return 0;
}