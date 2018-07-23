#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

/*
Testing isGameOver()
*	determines if game is over depending on if province card pile is empty or
*	at least three card piles are empty
*/

int main() {
	struct gameState testState;
	int actual;
	int expected;

	// initialize supply piles to 1
	for (int i = 0; i < 25; i++)
		testState.supplyCount[i] = 1;

	printf("TESTING: isGameOver()\n");
	/****************************************Test 1****************************************/
	printf("-TEST 1-\n");
	testState.supplyCount[province] = 0;
	expected = 1;
	actual = isGameOver(&testState);
	if (actual == expected)
	{
		printf("PASSED: returned 1 because province card pile is empty\n");
	}
	else
	{
		printf("FAILED: did not return 1 even thoough province card pile is empty\n");
	}

	/****************************************Test 2****************************************/
	printf("-TEST 2-\n");
	actual = isGameOver(&testState);
	expected = 0;
	if (actual == expected)
	{
		printf("PASSED: returned 0 because no card piles are empty including the province card pile\n");
	}
	else
	{
		printf("FAILED: did not retrun 0 even though no card piles are empty including the province card pile\n");
	}

	/****************************************Test 3****************************************/
	printf("-TEST 3-\n");
	testState.supplyCount[province] = 1;
	testState.supplyCount[minion] = 0;
	testState.supplyCount[duchy] = 0;
	testState.supplyCount[council_room] = 0;
	actual = isGameOver(&testState);
	expected = 1;
	if (actual == expected)
	{
		printf("PASSED: returned 1 because there's 3 empty piles and stack of province cards is not empty\n");
	}
	else
	{
		printf("FAILED: did not return 1 even though there's 3 empty pilies and stack of province cards is not empty\n");
	}

	return 0;
}