#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

/*
*Testing Adventurer Card
*	Reveal cards from your deck until you reveal 2 Treasure cards. Put those Treasure cards into your hand and discard the other revealed cards.
*/

void assertTest(int passedTest)
{
	if (passedTest)
	{
		printf("PASSED: ");
	}
	else
	{
		printf("FAILED: ");
	}

}

int main() {
	int newCards = 0;
	int discarded = 1;
	int shuffledCards = 0;
	int handCount;
	int deckcount;
	int newDeckCount;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState originalState, testState;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &originalState);
	printf("\nTESTING: Adventurer Card\n");

	//copy game state
	printf("--------------------Test Case Copper, Copper, Gold ------------");
	memcpy(&testState, &originalState, sizeof(struct gameState));

	deckcount = testState.deckCount[thisPlayer];


	int newDeck1[] = {copper, copper, copper};
	newDeckCount = 3;

	for (int i = 0; i < newDeckCount; i++) {
		testState.deck[thisPlayer][--deckcount] = newDeck1[i];
	}

	cardEffect(adventurer, choice1, choice2, choice3, &testState, handpos, &bonus);
	newCards = 2;
	handCount = testState.handCount[thisPlayer];

	/****************************************Test 1****************************************/
	assertTest(testState.handCount[thisPlayer] == originalState.handCount[thisPlayer] + newCards - discarded);
	printf("Expected to increase handcount by two cards\n");

	/****************************************Test 2****************************************/
	assertTest(testState.hand[thisPlayer][--handCount] == copper);
	printf("Expected to recieve the first treasure card, which is Copper\n");

	/****************************************Test 3****************************************/
	assertTest(testState.hand[thisPlayer][--handCount] == copper);
	printf("Expected to recieve the second treasure card, which is Copper\n");

	/****************************************Test 4****************************************/
	assertTest(testState.deckCount[thisPlayer] == originalState.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("Expected to reduce the deck by two cards\n");

	return 0;
}
