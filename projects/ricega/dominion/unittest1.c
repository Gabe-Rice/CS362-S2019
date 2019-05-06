
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

#define FUNCTION "adventurerFunc()"
		
	
	
int main()
{
	int numCoinsHand = 0;
	int numCoinsDeck = 0;
	int numEstateHand = 0;
	int numEstateDeck = 0;

    int i; 
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
	
	struct gameState testState;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	memset(&testState, 23, sizeof(struct gameState)); 
	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &testState);

	printf("\n----------------- Unit Test 1: Testing Function: %s ----------------\n\n", FUNCTION);

	
	printf("-Testing game state at initialization, prior to function call-\n");

//*********** Test initialization of game****************

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
	
	
//******** Test state of game with initial settings before and after call to adventurer() **********
	
	printf("-Testing state of deck and hand before and after function call-\n");
	
	printf("\n\tDeck count before function call: %d, Expected: 5\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 5);
	printf("\thand count before function call: %d, Expected: 5\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	printf("\tdiscard before function call: %d, Expeceted: 0\n", testState.discardCount[thisPlayer]);
	ASSERT_TRUE(testState.discardCount[thisPlayer] == 0);
	
	adventurerFunc(&testState, thisPlayer);
	
	printf("\n\tDeck count after function call: %d, Expected: 3\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 3);
	printf("\thand count after function call: %d, Expected: 7\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 7);
	printf("\tdiscard after function call: %d, Expected: 0\n", testState.discardCount[thisPlayer]);
	ASSERT_TRUE(testState.discardCount[thisPlayer] == 0);
	
	
//************* Test state of game after manipulating inputs: 1 coin in player's hand, no coins in deck *******
	
	printf("\n-Testing state of deck and hand by manipulating inputs: 1 coin in hand-\n");
	
	initializeGame(numPlayers, k, seed, &testState);
	
	for (i = 0; i < 5; i++)
	{
		testState.deck[thisPlayer][i] = estate;
	}
	testState.hand[thisPlayer][0] = estate;
	testState.hand[thisPlayer][1] = estate;
	testState.hand[thisPlayer][2] = estate;
	testState.hand[thisPlayer][3] = estate;
	testState.hand[thisPlayer][4] = copper;
	
	printf("\n\tDeck count before function call: %d, Expected: 5\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 5);
	printf("\thand count before function call: %d, Expected: 5\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	printf("\tdiscard before function call: %d, Expeceted: 0\n", testState.discardCount[thisPlayer]);
	ASSERT_TRUE(testState.discardCount[thisPlayer] == 0);
	
	adventurerFunc(&testState, thisPlayer);
	
	printf("\n\tDeck count after function call: %d, Expected: 0\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 0);
	printf("\thand count after function call: %d, Expeceted 5\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	printf("\tdiscard after function call: %d, Expected 5\n", testState.discardCount[thisPlayer]);
	ASSERT_TRUE(testState.discardCount[thisPlayer] == 5);
	
	
//************* Test state of game after manipulating inputs: 1 coin at bottom of deck *******
	
	printf("\n-Testing state of deck and hand by manipulating inputs: 1 coin at bottom of deck-\n");
	
	initializeGame(numPlayers, k, seed, &testState);
	
	for (i = 0; i < 5; i++)
	{
		testState.hand[thisPlayer][i] = estate;
	}
	testState.deck[thisPlayer][0] = estate;
	testState.deck[thisPlayer][1] = estate;
	testState.deck[thisPlayer][2] = estate;
	testState.deck[thisPlayer][3] = estate;
	testState.deck[thisPlayer][4] = copper;
	
	printf("\n\tDeck count before function call: %d, Expected: 5\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 5);
	printf("\thand count before function call: %d, Expected: 5\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 5);
	printf("\tdiscard before function call: %d, Expeceted: 0\n", testState.discardCount[thisPlayer]);
	ASSERT_TRUE(testState.discardCount[thisPlayer] == 0);
	
	adventurerFunc(&testState, thisPlayer);
	
	printf("\n\tDeck count after function call: %d, Expected: 0\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 0);
	printf("\thand count after function call: %d, Expeceted 6\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 6);
	printf("\tdiscard after function call: %d, Expected 4\n", testState.discardCount[thisPlayer]);
	ASSERT_TRUE(testState.discardCount[thisPlayer] == 4);
	
	printf("\n-If no asserts were triggered, the test completed with no errors found-\n");
	
	
	
	//int x = 1;
	//int y = 5;
	
	//ASSERT_TRUE(x == y);
	
	return 0;
}