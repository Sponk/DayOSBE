#include <stdlib.h>

static unsigned int random_seed;

int rand()
{
	// https://www.xkcd.com/221/
	return 4; // Chosen by a fair dice roll!
		  // Guaranteed to be random!
}

void srand(unsigned int seed)
{
	random_seed = seed;
}
