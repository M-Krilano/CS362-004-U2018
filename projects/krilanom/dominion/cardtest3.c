#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

/*
*Testing Council Room Card
*	each other player draws a card. Player draws 4 cards and gets one buy
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

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState originalState, testState;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state
	initializeGame(numPlayers, k, seed, &originalState);
	printf("\nTESTING: Council Room Card\n");

	//copy game state
	memcpy(&testState, &originalState, sizeof(struct gameState));

	cardEffect(council_room, choice1, choice2, choice3, &testState, handpos, &bonus);
	newCards = 4;

	/****************************************Test 1****************************************/
	assertTest(testState.handCount[thisPlayer] == originalState.handCount[thisPlayer] + newCards - discarded);
	printf("Receives 4 cards");
	/****************************************Test 1****************************************/
	assertTest(testState.deckCount[thisPlayer] == originalState.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("Deck has 4 less Cards");
	

	return 0;
}

