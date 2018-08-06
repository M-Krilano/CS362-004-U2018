#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "dominion_helpers.h"
#include "rngs.h"
#include "random_test_helpers.h"

/*
* Random Test Suite: Adventurer Card
* Card Detail:
*	- Use adventure card
*	- Go through deck, one card at a time (revealing them) until you find two 
*	  treasure cards
*	- Once you find two treasure cards, add those two treasure cards to hand
*	- Discard the revealed/non-treasure cards into discard pile
* Test Conditions: 
*	- Create a gameState struct with random values called pre
*   - Call cardEffect with a copy of pre called post
*   - Compare the structs and report differences
* Tests:
*   - Current player's deck has x fewer cards - no visibility into this metric
*   - Current player's hand has 2 more treasure cards
*   - Current player's hand has 1 more card
*   - Played card has 1 more card
*   - Current player's deck + discard has 2 fewer cards
*   - Opponent's card counts unchanged
*/

// Function Prototype
void testCardAdventurer(struct gameState *pre, struct results *r);

int main() {
	srand(time(NULL));

	printf("Test Suite: Adventurer Card - running %d random tests\n", NUMTESTS);
	printf("Testing Initiating.\n");
	struct results r = { 0 };
	int i;
	for (i = 0; i < NUMTESTS; i++) {
		struct gameState state;
		randomGameState(&state);
		testCardAdventurer(&state, &r);
	}
	printf("Testing Completed.\n\n");

	if (r.result1 + r.result2 + r.result3 + r.result4 + r.result5 > 0) {
		printf("\nTest Suite FAILED (at least one test failed\n");
	}
	else {
		printf("\nTest Suite PASSED\n");
	}
	printf("\n---------- Results: Error Rates ----------\n");
	printf("Treasure card counts: %.2f%%\n", r.result1 * 1.0 / NUMTESTS * 100);
	printf("Player hand count: %.2f%%\n", r.result2 * 1.0 / NUMTESTS * 100);
	printf("Total discards+deck count: %.2f%%\n", r.result3 * 1.0 / NUMTESTS * 100);
	printf("Opponent card counts: %.2f%%\n", r.result4 * 1.0 / NUMTESTS * 100);
	printf("Played card counts: %.2f%%\n", r.result5 * 1.0 / NUMTESTS * 100);
	return 0;
}

/*
* Function: testCardAdeventurer 
*	- Pass in pointer to gameState struct w/ random values and a pointer to
*	  results struct
*/
void testCardAdventurer(struct gameState *pre, struct results *r) {
	// cardEffect variables
	int handPos;					// range 0 - state->handCount[playerNumber]
	int choice1, choice2, choice3;  // range 0 - 26 (CARD values)
	int bonus;						// 0 - MAX_DECK

	// test variables
	int playerNumber = pre->whoseTurn;
	struct gameState post;
	int i;
	int pre_t = 0;					// number of treasure cards in hand (pre gameState)
	int post_t = 0;					// number of treasure cards in hand (post gameState)

	handPos = randomNum(0, pre->handCount[playerNumber]);
	pre->hand[playerNumber][handPos] = adventurer;

	memcpy(&post, pre, sizeof(struct gameState));

	bonus = randomNum(0, MAX_DECK);
	choice1 = randomNum(0, 26);
	choice2 = randomNum(0, 26);
	choice3 = randomNum(0, 26);

	// Call cardEffect w/ post gameState
	cardEffect(adventurer, choice1, choice2, choice3, &post, handPos, &bonus);

	// Compare pre to post gameState, increment results struct
	// Post Hand expected to contain 2 more treasure cards
	for (i = 0; i < pre->handCount[playerNumber]; i++) {
		int cardPre = pre->hand[playerNumber][i];
		if (cardPre == copper || cardPre == gold || cardPre == silver) {
			pre_t++;
		}
	}
	for (i = 0; i < post.handCount[playerNumber]; i++) {
		int cardPost = post.hand[playerNumber][i];
		if (cardPost == copper || cardPost == gold || cardPost == silver) {
			post_t++;
		}
	}
	if (pre_t + 2 != post_t) {
		r->result1++;
	}

	// Hand count expected to have 1 more card
	if (pre->handCount[playerNumber] + 1 != post.handCount[playerNumber])
		r->result2++;

	// Post deck + discard pile expected to be 2 less than pre
	if (pre->deckCount[playerNumber] + pre->discardCount[playerNumber] != post.deckCount[playerNumber] + post.discardCount[playerNumber] + 2) {
		r->result3++;
	}

	// Opponent-card's counts unchanged
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

	// Post playedCardCount expected to be 1 more than pre
	if (pre->playedCardCount + 1 != post.playedCardCount) {
		r->result5++;
	}
}
