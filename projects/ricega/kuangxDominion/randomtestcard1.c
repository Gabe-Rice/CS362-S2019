#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "rngs.h"

#define stringify(x) #x   //convert argument to string
#define ASSERT_TRUE(x) if (!(x)) { printf("ASSERT_TRUE FAILED: (%s), FUNCTION: %s, FILE: %s, LINE: %d.\n", stringify(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); }

int testSmithy(int p, struct gameState *post) {
	
  struct gameState pre;
  memcpy (&pre, post, sizeof(struct gameState));
  
  int handPos = 1;
  int numInHand = pre.handCount[p];
  //printf("%d\n\t", numInHand);
  smithyEffect(p, post, handPos);
  //printf("%d\n", post->handCount[p]);
  
  if (post->handCount[p] != numInHand + 2 && post->handCount[p] != numInHand)
  {
	  ASSERT_TRUE(post->handCount[p] == numInHand + 2);
	  //exit(1);
  }
  
  
}

int main () {

  int i, n, r, p, deckCount, discardCount, handCount;

  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

  struct gameState G;

  printf ("Testing smithy.\n");

  printf ("RANDOM TESTS.\n");

  SelectStream(2);
  PutSeed(3);

  for (n = 0; n < 2000; n++) {
    for (i = 0; i < sizeof(struct gameState); i++) {
      ((char*)&G)[i] = floor(Random() * 256);
    }
    p = floor(Random() * 2);
    G.deckCount[p] = floor(Random() * MAX_DECK);
    G.discardCount[p] = floor(Random() * MAX_DECK);
    G.handCount[p] = floor(Random() * MAX_HAND);
	G.playedCardCount = 0;
    r = testSmithy(p, &G);
	//printf("%d\n", r);
	//ASSERT_TRUE(r = 2000);
  }

  printf ("ALL TESTS OK\n");
  
  return 0;
  
}