#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

/*
*Testing supplyCount()
*	How many of given card are left in supply
*/
//this is the amount of a specific type of card given a specific number

int main() {
	struct gameState testState;
	int actual;
	int expected;

	// initialize supply piles to 1
	for (int i = 0; i < 25; i++) {
		testState.supplyCount[i] = 1;
	}

	printf("TESTING: isGameOver()\n");
	/****************************************Test 1****************************************/
	printf("-TEST 1-\n");
	expected = 1;
	actual = supplyCount(adventurer, &testState);
	if (actual == expected)
	{
		printf("PASSED: returned 1 because adventurer card pile was set to 1\n");
	}
	else
	{
		printf("FAILED: did not return 1, even thoough adventurer card pile was set to 1\n");
	}

	/****************************************Test 2****************************************/
	printf("-TEST 2-\n");
	// initialize supply piles to 5
	for (int i = 0; i < 25; i++) {
		testState.supplyCount[i] = 5;
	}
	testState.supplyCount[sea_hag] - 5;
	expected = 0;
	actual = supplyCount(sea_hag, &testState);
	if (actual == expected)
	{
		printf("PASSED: returned 0 because sea_hag card pile was set to 0\n");
	}
	else
	{
		printf("FAILED: did not return 0, even thoough sea_hag card pile was set to 0\n");
	}
	/****************************************Test 3****************************************/
	printf("-TEST 3-\n");
	for (int i = 0; i < 25; i++) {
		testState.supplyCount[i] = -1;
	}
	expected = -1;
	actual = supplyCount(ambassador, &testState);
	if (actual == expected)
	{
		printf("PASSED: returned -1 because ambassador card pile was set to -1\n");
	}
	else
	{
		printf("FAILED: did not return -1, even thoough ambassador card pile was set to -1\n");
	}
	/****************************************Test 4****************************************/
	printf("-TEST 4-\n");
	for (int i = 0; i < 25; i++) {
		testState.supplyCount[i] = -10;
	}
	testState.supplyCount[minion] + 110;
	expected = 100;
	actual = supplyCount(minion, &testState);
	if (actual == expected)
	{
		printf("PASSED: returned 100 because minion card pile was set to 100\n");
	}
	else
	{
		printf("FAILED: did not return 100, even thoough minion card pile was set to 100\n");
	}

	return 0;
}