#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"

/*
*Testing Village Card
*	receive one card and one action
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
	int numActions = 0;

	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 1000;
	int numPlayers = 2;
	int thisPlayer = 0;
	struct gameState originalState, testState;
	int k[10] = { adventurer, embargo, village, minion, mine, cutpurse,
		sea_hag, tribute, smithy, council_room };

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &originalState);

	printf("\nTESTING: Village Card\n");

	//copy game state
	memcpy(&testState, &originalState, sizeof(struct gameState));

	cardEffect(village, choice1, choice2, choice3, &testState, handpos, &bonus);
	newCards = 1;
	numActions = 1;

	/****************************************Test 1****************************************/
	assertTest(testState.handCount[thisPlayer] == originalState.handCount[thisPlayer] + newCards - discarded);
	printf("Expected to increase hand count by 1 card\n");
	/****************************************Test 1****************************************/
	assertTest(testState.deckCount[thisPlayer] == originalState.deckCount[thisPlayer] - newCards + shuffledCards);
	printf("Expected to decrease deck count by one card\n");
	/****************************************Test 1****************************************/
	assertTest(testState.whoseTurn == originalState.whoseTurn);
	printf("Expected to be same player's turn\n");
	/****************************************Test 1****************************************/
	assertTest(testState.numActions == originalState.numActions + numActions);
	printf("Expected to increase number of actions by one\n");

	/****************************************Test 1****************************************/
	assertTest(testState.playedCardCount == originalState.playedCardCount + discarded);
	printf("Expected to increase number of discarded cards by one\n");
	/****************************************Test 1****************************************/

	return 0;
}