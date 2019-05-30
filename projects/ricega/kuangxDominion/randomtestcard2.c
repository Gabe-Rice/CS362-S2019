#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <time.h>
#include "rngs.h"

#define stringify(x) #x   //convert argument to string
#define ASSERT_TRUE(x) if (!(x)) { printf("ASSERT_TRUE FAILED: (%s), FUNCTION: %s, FILE: %s, LINE: %d.\n", stringify(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }

int testMine(struct gameState *post, int player, int handPos, int choice1, int choice2)
{
	struct gameState pre;
	memcpy (&pre, post, sizeof(struct gameState));
	
	int ret = mineFunc(post, player, handPos, choice1, choice2);
	
	if (ret != -1)
	{
		ASSERT_TRUE(ret != -1);
		exit(1);
	}
	
}



int main () {

  int i, j, n, r, p, deckCount, discardCount, handCount;
  
  srand(time(NULL));

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing mine.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);
  
	int C1;

  for (n = 0; n < 10000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
	
	//randomize choice1
	int cointTestArr[3] = { 5,6,7 };
	int randIdx = rand() % 3;
	int ch1 = cointTestArr[randIdx];
	G.hand[p][C1] = ch1;
	
	
	//randomize choice2
	enum CARD C2 = rand() % 27 + 1;
	//printf("%d\n", C2);
	
	G.playedCardCount = 0;
    r = testMine(&G, p, 1, C1, C2);
	
  }

  printf ("ALL TESTS OK\n");
  
  return 0;
  
}