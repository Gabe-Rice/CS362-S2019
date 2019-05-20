#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include "rngs.h"

#define stringify(x) #x   //convert argument to string
#define ASSERT_TRUE(x) if (!(x)) { printf("ASSERT_TRUE FAILED: (%s), FUNCTION: %s, FILE: %s, LINE: %d.\n", stringify(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }

int main (int argc, char** argv) {
    printf("TESTING adventurer\n");

    srand(time(NULL));

    printf("RANDOM TESTS\n");

    for(int i = 0; i < 2000; i++){
		
		//two to 4 players
        int numplayers = rand() % (MAX_PLAYERS - 1) + 2;
		
        struct gameState G;
        int k[10] = {adventurer, gardens, embargo, village, steward, mine, cutpurse, sea_hag, tribute, smithy};

        initializeGame(numplayers, k, rand(), &G);

        int player = rand() % numplayers;
  
        struct gameState pre;
        memcpy(&pre, &G, sizeof(struct gameState));

        adventurerFunc(&G, player);
		ASSERT_TRUE(G.handCount[player] == pre.handCount[player] + 2);

        int cardDrawn1 = G.hand[player][G.handCount[player] - 1];
		//ASSERT_TRUE(cardDrawn1 == copper && cardDrawn1 == silver && cardDrawn1 == gold);
        if(cardDrawn1 != copper && cardDrawn1 != silver && cardDrawn1 != gold){
            printf("TEST FAILED: card is not coin");
        }

        int cardDrawn2 = G.hand[player][G.handCount[player] - 2];
		//ASSERT_TRUE(cardDrawn2 == copper && cardDrawn2 == silver && cardDrawn2 == gold);
        if(cardDrawn2 != copper && cardDrawn2 != silver && cardDrawn2 != gold){
            printf("TEST FAILED: card is not coin");
        }
    }

    printf ("ALL TESTS OK\n");
	
	return 0;
}