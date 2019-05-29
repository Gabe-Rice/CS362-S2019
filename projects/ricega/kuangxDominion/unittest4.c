#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

//make custom assertion so program won't die, use function, file and line macros for output of where error occurs
#define stringify(x) #x   //convert argument to string
#define ASSERT_TRUE(x) if (!(x)) { printf("ASSERT_TRUE FAILED: (%s), FUNCTION: %s, FILE: %s, LINE: %d.\n", stringify(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }

#define FUNCTION "minionFunc()"

int main()
{
	int i; 
	int choice1 = -1;
	int choice2 = -1;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int thatPlayer = 1;
	
	int numCoinsHand = 0;
	int numCoinsDeck = 0;
	int numEstateHand = 0;
	int numEstateDeck = 0;
	
	struct gameState testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	memset(&testState, 23, sizeof(struct gameState)); 
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &testState);
	
	printf("\n----------------- Unit Test 4: Testing Function: %s ----------------\n\n", FUNCTION);
	
	printf("-Testing game state at initialization, prior to function call-\n");
	
/*******************Test initial Game state*******************************/
	
	for (i = 0; i < testState.handCount[thisPlayer]; i++)
	{
		if (testState.hand[thisPlayer][i] == copper)
			numCoinsHand++;
		
		if (testState.hand[thisPlayer][i] == estate)
			numEstateHand++;
	}
	printf("\n\tCopper in hand: %d\n", numCoinsHand);
	printf("\testate in hand: %d\n", numEstateHand);
	
	for (i = 0; i < testState.deckCount[thisPlayer]; i++)
	{
		if (testState.deck[thisPlayer][i] == copper)
			numCoinsDeck++;
		
		if (testState.deck[thisPlayer][i] == estate)
			numEstateDeck++;
	}
	printf("\tCopper in deck: %d\n", numCoinsDeck);
	printf("\testate in deck: %d\n", numEstateDeck);
	
	printf("\tTotal copper: %d, Expected: 7\n", (numCoinsHand + numCoinsDeck));
	printf("\tTotal estate: %d, Expected: 3\n\n", (numEstateHand + numEstateDeck));
	ASSERT_TRUE((numCoinsHand + numCoinsDeck) == 7);
	ASSERT_TRUE((numEstateHand + numEstateDeck) == 3);

	
/*********************Test choice1 +2 coin**********************/
	printf("\n\n\t\t------Test +2 coin choice------\n");

	printf("\n\tCoins in hand: %d\n", testState.coins);
	
	choice1 = 1;
	
	
	minionFunc(&testState, 1, thisPlayer, choice1, choice2);
	
	printf("\n\tCoins in hand after call: %d, Expected 6\n", testState.coins);
	ASSERT_TRUE(testState.coins == 6);
	
/*****Test choice2 discard hand, draw 4, same for all players with 5+ cards*****/
	printf("\n\n---Test discard hand, draw 4, same for all other players with 5+ in hand choice---\n");
	
	choice1 = -1;
	
	//reset from previous func call
	initializeGame(numPlayers, k, seed, &testState);
	
	printf("\n\tCards in hand: %d\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	
	
	choice2 = 1;
	
	minionFunc(&testState, 1, thisPlayer, choice1, choice2);
	
	printf("\n\tCards in hand after call: %d, Expected: 4\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 4);

	//reset from previous func call
	initializeGame(numPlayers, k, seed, &testState);
	
	
	
	
	return 0;
}