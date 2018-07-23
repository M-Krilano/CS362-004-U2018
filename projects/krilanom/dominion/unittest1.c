#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

/*
*Testing numHandCards()
*	returns how many cards current player has in hand
*/

int main() {
	struct gameState testState;
	int maxHandCount = 5;
	int numPlayers = 2;
	int player1 = 0;
	int player2 = 1;
	int actual;
	int expected;
	
	// init both players hands to 0
	testState.handCount[player1] = 0;
	testState.handCount[player2] = 0;

	// start with player 1
	testState.whoseTurn = player1;

	printf("TESTING: numHandCards()\n");
	/****************************************Test 1****************************************/
	printf("-TEST 1-\n");
	expected = 0;
	actual = numHandCards(&testState);
	if (actual == expected)
	{
		printf("PASSED: returned 0 because cards in player 1's hand is 0\n");
	}
	else
	{
		printf("FAILED: did not return 0 even though cards in player 1's hand is 0\n");
	}

	/****************************************Test 2****************************************/
	printf("-TEST 2-\n");
	// switch to player 2;
	testState.whoseTurn + 1;
	expected = 0;
	actual = numHandCards(&testState);
	if (actual == expected)
	{
		printf("PASSED: returned 0 because cards in player 2's hand is 0\n");
	}
	else
	{
		printf("FAILED: did not return 0 even though cards in player 2's hand is 0\n");
	}

	/****************************************Test 3****************************************/
	printf("-TEST 3-\n");
	// switch to player 1;
	testState.whoseTurn - 1;
	expected = 5;
	for (int x = 0; x < maxHandCount; x++) {
		testState.handCount[player1]++;
	}
	actual = numHandCards(&testState);
	if (actual == expected)
	{
		printf("PASSED: return 5 because cards in player 1's hand is 5\n");
	}
	else
	{
		printf("FAILED: did not return 5 even though cards in player 1's hand is 5\n");
	}

	/****************************************Test 4****************************************/
	printf("-TEST 4-\n");
	// switch to player 2;
	testState.whoseTurn + 1;
	expected = 5;
	for (int x = 0; x < maxHandCount; x++) {
		testState.handCount[player2]++;
	}
	actual = numHandCards(&testState);
	if (actual == expected)
	{
		printf("PASSED: return 5 because cards in player 2's hand is 5\n");
	}
	else
	{
		printf("FAILED: did not return 5 even though cards in player 2's hand is 5\n");
	}
	
	/****************************************Test 5****************************************/
	printf("-TEST 5-\n");
	// switch to player 1;
	testState.whoseTurn - 1;
	expected = 3;
	testState.handCount[player1] - 2;
	actual = numHandCards(&testState);
	if (actual == expected)
	{
		printf("PASSED: returned 3 because cards in player 1's hand is 3\n");
	}
	else
	{
		printf("FAILED: did not return 3 even though cards in player 1's hand is 3\n");
	}

	/****************************************Test 6****************************************/
	printf("-TEST 6-\n");
	// switch to player 2;
	testState.whoseTurn + 1;
	expected = 3;
	testState.handCount[player2] - 2;
	actual = numHandCards(&testState);
	if (actual == expected)
	{
		printf("PASSED: returned 3 because cards in player 2's hand is 3\n");
	}
	else
	{
		printf("FAILED: did not return 3 even though cards in player 2's hand is 3\n");
	}
	return 0;
}