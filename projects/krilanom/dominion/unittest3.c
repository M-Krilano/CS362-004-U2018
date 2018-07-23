#include "dominion.h"
#include "dominion_helpers.h"
#include <stdio.h>
#include "rngs.h"

/*
*Testing updateCoins()
*	updates the amount of coins based off the amount of treasure cards in players hand
*/

int main() {
	struct gameState testState;
	int maxHand = 5;			// maximum cards per hand is 5
	int numPlayers = 2;
	int currentPlayer = 0; // player1 = 0 and player2 = 1
	int seed = 10;
	int bonus = 0;
	int k[] = { sea_hag, feast, embargo, village, minion, great_hall, steward,
		adventurer, council_room, smithy };
	
	int actual;
	int expected, expected1, expected2, expected3, expected4;

	// initialize game with 2 players and a randomSeed of 10
	initializeGame(numPlayers, k, seed, &testState);

	printf("TESTING: updateCoins()\n");
	/****************************************Test 1****************************************/
	printf("-TEST 1-\n");

	// start out with 10 cards (3 estates and 7 coppers) but only 5 cards per had
	expected1 = 2, expected2 = 3, expected3 = 4, expected4 = 5;
	updateCoins(currentPlayer, &testState, bonus);
	actual = testState.coins;
	
	if (actual == expected1 || actual == expected2 || actual == expected3 || actual == expected4) {
		printf("PASS: Initial coin amount could be 2, 3, 4, or 5\n");
	}
	else {
		printf("FAIL: Initial coin amount is not 2, 3, 4, or 5\n");
	}
	
	
	/****************************************Test 2****************************************/
	printf("-TEST 2-\n");

	// Updated Player1
	for (int i = 0; i < maxHand; i++) {
		testState.hand[currentPlayer][i] = gold;
	}

	expected = 15;
	updateCoins(currentPlayer, &testState, bonus);
	actual = testState.coins;
	if (actual == expected) {
		printf("PASS: New coin amount is 15\n");
	}
	else {
		printf("FAIL: New coin amount is not 15\n");
	}
	/****************************************Test 3****************************************/
	printf("-TEST 3-\n");

	// Updated Player1
	for (int i = 0; i < maxHand; i++) {
		testState.hand[currentPlayer][i] = silver;
	}
	bonus + 1;
	
	expected = 11;									// silver = 2, bonus = 1; (2*5)+1 = 11 
	updateCoins(currentPlayer, &testState, bonus);
	actual = testState.coins;
	if (actual == expected) {
		printf("PASS: New coin amount is 11\n");
	}
	else {
		printf("FAIL: New coin amount is not 11\n");
	}
	return 0;
}