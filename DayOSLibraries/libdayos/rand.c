#include <stdlib.h>

#define A 1103515245
#define C 12345
#define M 0xFFFFFE

// Using the Linear Conguential Generator
static unsigned int x;

int rand()
{
	x = (A * x + C) % M;
	return x;
}

void srand(unsigned int seed)
{
	x = seed;
}
