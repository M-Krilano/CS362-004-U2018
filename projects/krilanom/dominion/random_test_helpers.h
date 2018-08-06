
#ifndef RANDOM_TEST_HELPERS_H
#define RANDOM_TEST_HELPERS_H

#include "dominion.h"

// Global Constants
#define NUMTESTS 100
#define MINCARDS 3


// Struct to hold number of inconsistencies between pre and post gameState

struct results {
	int result1;
	int result2;
	int result3;
	int result4;
	int result5;
};

// Function Prototypes
int randomNum(int low, int high);
void randomGameState(struct gameState *state);


#endif
