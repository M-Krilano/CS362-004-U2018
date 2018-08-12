#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include "random_test_helpers.h"

/*
* Random Test Suite: Village card
* Card Detail:
*	- Use village card
*	- Add one card from deck to hand
*   - Add two actions
*	- No changes to state of other player
*   - No changes in the number of cards in the supply piles
* Test Conditions:
*	- Create a gameState struct with random values called pre
*   - Call cardEffect with a copy of pre called post 
*	- Compare the structs and report differences
* Tests:
*   - Current players deck has 1 less card
*   - Current players hand has is unchanged
*   - Current player played 1 card
*   - Opponent's deck unchanged
*   - 2 more actions
*/


// Function Prototype
void testCardVillage(struct gameState *pre, struct results *r);

int main() {
	srand(time(NULL));

	printf("Test Suite: Village Card - running %d random tests\n", NUMTESTS);
	printf("Testing Initiating.\n");
	struct results r = { 0 };
	int i;
	for (i = 0; i < NUMTESTS; i++) {
		struct gameState state;
		randomGameState(&state);
		testCardVillage(&state, &r);
	}
	printf("Testing Completed.\n\n");

	if (r.result1 + r.result2 + r.result3 + r.result4 + r.result5 > 0) {
		printf("\nTest Suite FAILED (at least one test failed\n");
	}
	else {
		printf("\nTest Suite PASSED\n");
	}
	printf("\n---------- Results: Error Rates ----------\n");
	printf("Played card count: %.2f%%\n", r.result1 * 1.0 / NUMTESTS * 100);
	printf("Player hand count: %.2f%%\n", r.result2 * 1.0 / NUMTESTS * 100);
	printf("Deck count: %.2f%%\n", r.result3 * 1.0 / NUMTESTS * 100);
	printf("Opponent card counts: %.2f%%\n", r.result4 * 1.0 / NUMTESTS * 100);
	printf("Number Actions: %.2f%%\n", r.result5 * 1.0 / NUMTESTS * 100);
	return 0;
}

/*
* Function: testCardVillage
* Pass in a pointer to a gameState struct with random values and a pointer to
* an results struct
*/
void testCardVillage(struct gameState *pre, struct results *r) {
	// cardEffect variables
	int handPos;					// range 0 - state->handCount[playerNumber]
	int choice1, choice2, choice3;  // range 0 - 26 (CARD values)
	int bonus;						// 0 - MAX_DECK

				// test variables
	int playerNumber = pre->whoseTurn;
	struct gameState post;
	int i;

	handPos = randomNum(0, pre->handCount[playerNumber]);
	pre->hand[playerNumber][handPos] = village;

	memcpy(&post, pre, sizeof(struct gameState));

	bonus = randomNum(0, MAX_DECK);
	choice1 = randomNum(0, 26);
	choice2 = randomNum(0, 26);
	choice3 = randomNum(0, 26);

	// Call cardEffect w/ post gameState
	cardEffect(village, choice1, choice2, choice3, &post, handPos, &bonus);

	// Compare pre to post gameState, increment results struct
	// Post played hand expected to be 1 more than pre
	if (pre->playedCardCount + 1 != post.playedCardCount) {
		r->result1++;
	}

	// Post hand count expected to equal pre hand count
	if (pre->handCount[playerNumber] != post.handCount[playerNumber]) {
		r->result2++;
	}

	// Post deck expected to be 1 less than pre
	if (pre->deckCount[playerNumber] - 1 != post.deckCount[playerNumber]) {
		r->result3++;
	}

	// Opponent cards counts unchanged
	for (i = 0; i < pre->numPlayers; i++) {
		if (i == playerNumber) {
			continue;
		}
		else {
			if (pre->deckCount[i] != post.deckCount[i] || pre->handCount[i] != post.handCount[i] || pre->discardCount[i] != post.discardCount[i]) {
				r->result4++;
			}
		}
	}

	// Expected to be one more action
	if (pre->numActions + 2 != post.numActions) {
		r->result5++;
	}
}
