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

#define FUNCTION "village"

int main()
{
	int i; 
	int choice1 = -1, choice2 = -1, choice3 = -1;
	int handPos = 0;
	int bonus = 0;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	int nextPlayer = thisPlayer + 1;
	
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
	
	printf("\n----------------- Card Test 4: %s ----------------\n\n", FUNCTION);
	
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
	
/***************Verify number of actions prior to function call***********************/
	printf("\n-Verify number of current actions prior to function call-\n");
	int currNumActs;
	currNumActs = testState.numActions;
	printf("\n\tNumber of actions: %d\n", currNumActs);
	
	
/*********************Test before and after function***********************/

	printf("\n-Testing state of deck and hand before and after function call-\n");
	
	printf("\n\tDeck count before function call: %d, Expected: 5\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 5);
	printf("\thand count before function call: %d, Expected: 5\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	printf("\tdiscard is not kept track of in smithy, the numbers will reveal it's functionality\n", testState.discardCount[thisPlayer]);
	
	cardEffect(village, choice1, choice2, choice3, &testState, handPos, &bonus);
	
	printf("\n\tDeck count after function call: %d, Expected: 4\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 4);
	printf("\thand count after function call: %d, Expected: 5 (after discard() is called)\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	
	
/***************Verify number of actions after function call***********************/
	printf("\n-Verify number of current actions after function call-\n");
	int plusNumActs;
	plusNumActs = testState.numActions;
	printf("\n\tNumber of actions: %d, Expected: %d\n", plusNumActs, currNumActs + 2);
	ASSERT_TRUE(testState.numActions == currNumActs + 2);
	
	
	
	
	return 0;
}