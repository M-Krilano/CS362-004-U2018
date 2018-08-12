// randomhelpers.c
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "dominion_helpers.h"
#include "random_test_helpers.h"
#include "rngs.h"

/*
* Outputs a random integer based on 
*/
int randomNum(int lower, int upper) {
	return (rand() % (upper - lower + 1)) + lower;
}


// Assigns random gameState
void randomGameState(struct gameState *state) {
	int i;
	int numPlayers = randomNum(2, MAX_PLAYERS);
	int whoseTurn = randomNum(0, numPlayers);  // range 0 - numPlayers

	for (i = 0; i < sizeof(struct gameState); i++) {
		((char*)state)[i] = floor(Random() * 256);
	}

	// Assigns a somewhat "sane" gamestate
	state->deckCount[whoseTurn] = randomNum(MINCARDS, MAX_DECK);
	state->discardCount[whoseTurn] = randomNum(0, MAX_DECK - state->deckCount[whoseTurn]);
	state->handCount[whoseTurn] = randomNum(0, MAX_DECK - state->deckCount[whoseTurn] - state->discardCount[whoseTurn]);
	state->playedCardCount = 0; 
	state->numPlayers = numPlayers;
	state->whoseTurn = whoseTurn;

	// Assigns random cards to deck, discard pile, and hand
	for (i = 0; i < state->deckCount[whoseTurn]; i++)
		state->deck[whoseTurn][i] = randomNum(0, 26);
	for (i = 0; i < state->discardCount[whoseTurn]; i++)
		state->discard[whoseTurn][i] = randomNum(0, 26);
	for (i = 0; i < state->handCount[whoseTurn]; i++)
		state->hand[whoseTurn][i] = randomNum(0, 26);
}
