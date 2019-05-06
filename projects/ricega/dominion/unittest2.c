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

#define FUNCTION "smithy()"

int main()
{
	int i; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	
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
	
	printf("\n----------------- Unit Test 2: Testing Function: %s ----------------\n\n", FUNCTION);
	
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
	
	
/*********************Test before and after function***********************/
//smithy just draws 3 cards and discards:

	printf("-Testing state of deck and hand before and after function call-\n");
	
	printf("\n\tDeck count before function call: %d, Expected: 5\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 5);
	printf("\thand count before function call: %d, Expected: 5\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	printf("\tdiscard is not kept track of in smithy, the numbers will reveal it's functionality\n", testState.discardCount[thisPlayer]);
	
	smithyFunc(&testState, thisPlayer, 1);
	
	printf("\n\tDeck count after function call: %d, Expected: 2\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 2);
	printf("\thand count after function call: %d, Expected: 7 (after discard() is called)\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 7);
	
	
	
	
	return 0;
}