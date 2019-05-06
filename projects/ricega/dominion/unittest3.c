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

#define FUNCTION "mineFunc()"

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
	
	printf("\n----------------- Unit Test 3: Testing Function: %s ----------------\n\n", FUNCTION);
	
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
	
/*********Set hand to have all coppers to verify consistency in number of coppers********/
printf("\n\n-Set all cards in hand to copper to test treasure upgrade-\n");

	int numCopper = 0;
	for (i = 0; i < 5; i++) 
	{ 
		testState.hand[thisPlayer][i] = copper; 
	}
	for (i = 0; i < testState.handCount[thisPlayer]; i++) 
	{ 
		if (testState.hand[thisPlayer][i] == copper) 
			numCopper++; 
	}
	printf("\n\tcoppers in hand: %d, Expected: 5\n", numCopper); 
	
	printf("\n-----Test return statements-----\n");
	
	int ret;
	
/***************Test if return is true (1) with correct input****************/
	ret = mineFunc(&testState, thisPlayer, 1, copper, silver);
	printf("\n\tResult of minFunc return with known good input (choice1 copper, choice2 silver): %d\n", ret);
	ASSERT_TRUE(ret == 1);
	
/***************Test if return is false (-1) with bad input******************/
	ret = mineFunc(&testState, thisPlayer, 1, silver, copper);
	printf("\n\tResult of minFunc return with known bad input (choice1 silver, choice2 copper): %d\n", ret);
	ASSERT_TRUE(ret == 1);


/****************Test if +3 treasure actually placed in hand******************/
printf("\n\n---Test if treasure was upgraded (+3)---\n");

	mineFunc(&testState, thisPlayer, 1, copper, silver);
	int numSilver = 0;
	numCopper = 0;
	for (i = 0; i < testState.handCount[thisPlayer]; i++)
	{
		if (testState.hand[thisPlayer][i] == silver)
			numSilver++;
		if (testState.hand[thisPlayer][i] == copper)
			numCopper++;
	}
	printf("\n\t+3 treasure added to hand: %d, Expected: 1\n", numSilver);
	ASSERT_TRUE(numSilver == 1);
	
/*****************Test if there is 1 less copper (trash)**********/
printf("\n\n---Test if copper count is correct, 1 should be trashed and 1 discarded---\n");

	printf("\n\t-1 copper (trash), total in hand: %d, Expected: 3\n", numCopper);
	ASSERT_TRUE(numCopper == 3);
	
	
	printf("\n\tDeck count after function call: %d, Expected: 5\n", testState.deckCount[thisPlayer]);
	ASSERT_TRUE(testState.deckCount[thisPlayer] == 5);
	printf("\thand count after function call: %d, Expeceted 4 (after discard)\n", testState.handCount[thisPlayer]);
	ASSERT_TRUE(testState.handCount[thisPlayer] == 4);
	
	
	return 0;
}