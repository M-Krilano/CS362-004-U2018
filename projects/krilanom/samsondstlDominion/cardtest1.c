#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#include <stdlib.h>

/*
*Testing Smithy Card
*	handsize is increased by drawing three cards
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
	int seed = 10;
	int numPlayers = 2;
	int currentPlayer = 0;
	struct gameState originalState, testState;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state
	initializeGame(numPlayers, k, seed, &originalState);

	printf("\nTESTING: Smithy Card\n");

	//copy game state
	memcpy(&testState, &originalState, sizeof(struct gameState));

	cardEffect(smithy, choice1, choice2, choice3, &testState, handpos, &bonus);
	newCards = 3;

	/****************************************Test 1****************************************/
	assertTest(testState.handCount[currentPlayer] == originalState.handCount[currentPlayer] + newCards - discarded);
	printf("Expected to increase handcount and gain three cards");
	/****************************************Test 2****************************************/
	assertTest(testState.deckCount[currentPlayer] == originalState.deckCount[currentPlayer] - newCards + shuffledCards);
	printf("Expted to increase players deck count by three cards");
	/****************************************Test 3****************************************/
	assertTest(testState.playedCardCount == originalState.playedCardCount + discarded);
	printf("Expected to increase number of cards in discarded deck");

	return 0;
}
