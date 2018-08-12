#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include "random_test_helpers.h"

/*
* Random Test Suite: Smithy Card
* Card Detail:
*	- Use smithy card
*	- Add three cards from current players deck to their hand
*   - No changes to state of other player(s)
*	- No changes in number of cards in supply piles
* Test Conditions: 
*	- Create a gameState struct with random values called pre
*   - Call cardEffect with a copy of pre called post
*   - Compare the structs and report differences
* Tests:
*   - Current player deck has 3 less cards
*   - Current player hand has 2 more cards
*   - Current player played 1 card
*   - Opponent's deck unchanged
*/



// Function Prototype
void testCardSmithy(struct gameState *pre, struct results *r);

int main() {
	srand(time(NULL));
	printf("Test Suite: Smithy Card - running %d random tests\n", NUMTESTS);
	printf("Testing Initiating.\n");
	struct results r = { 0 };
	int i;
	for (i = 0; i < NUMTESTS; i++) {
		struct gameState state;
		printf("before gameState\n");
		randomGameState(&state);
		printf("after gameState\n"); 
		testCardSmithy(&state, &r);
		printf("after testcardsmithy\n");
	}
	printf("Testing Completed.\n\n");

	if (r.result1 + r.result2 + r.result3 + r.result4 + r.result5 > 0) {
		printf("\nTest Suite FAILED (at least one test failed\n");
	}
	else {
		printf("\nTest Suite PASSED\n");
	}

	printf("\n---------- Results: Error Rates ----------\n");
	printf("Player played card count: %.2f%%\n", r.result1 * 1.0 / NUMTESTS * 100);
	printf("Player hand count: %.2f%%\n", r.result2 * 1.0 / NUMTESTS * 100);
	printf("Deck count: %.2f%%\n", r.result3 * 1.0 / NUMTESTS * 100);
	printf("opponent card counts: %.2f%%\n", r.result4 * 1.0 / NUMTESTS * 100);
	
	return 0;
}

/*
* Function: testCardSmithy
* pass in a pointer to a gameState struct with random values and a pointer to
* an results struct
*/
void testCardSmithy(struct gameState *pre, struct results *r) {
	// cardEffect variables
	int handPos;						// range 0 - state->handCount[playerNumber]
	int choice1, choice2, choice3;		// range 0 - 26 (CARD values)
	int bonus;							// 0 - MAX_DECK

	// test variables
	int playerNumber = pre->whoseTurn;
	struct gameState post;
	int i;

	handPos = randomNum(0, pre->handCount[playerNumber]);
	pre->hand[playerNumber][handPos] = smithy;

	memcpy(&post, pre, sizeof(struct gameState));

	bonus = randomNum(0, MAX_DECK);
	choice1 = randomNum(0, 26);
	choice2 = randomNum(0, 26);
	choice3 = randomNum(0, 26);
	printf("before cardeffect\n");
	// Call cardEffect w/ post gameState
	cardEffect(smithy, choice1, choice2, choice3, &post, handPos, &bonus);

	// Compare pre to post gameState, increment results struct
	// Post played hand expected to be 1 more than pre
	if (pre->playedCardCount + 1 != post.playedCardCount)
		r->result1++;

	// HandCount expected to have only 2 more cards
	if (pre->handCount[playerNumber] + 2 != post.handCount[playerNumber])
		r->result2++;

	// Post deck expected to be 3 less than pre
	if (pre->deckCount[playerNumber] - 3 != post.deckCount[playerNumber])
		r->result3++;
	printf("before last for loop\n");
	// Opponent cards counts unchanged
	for (i = 0; i < pre->numPlayers; i++) {
		if (i == playerNumber)
			continue;
		else {
			if (pre->deckCount[i] != post.deckCount[i] || pre->handCount[i] != post.handCount[i] || pre->discardCount[i] != post.discardCount[i]) {
				r->result4++;
			}
		}
	}
}
