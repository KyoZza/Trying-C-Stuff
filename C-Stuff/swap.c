#include "swap.h"

// Fastest Swap
void swap(int8_t *a, int8_t *b) {
	int8_t temp = *a;
	*a = *b;
	*b = temp;
}


void swapBitOperator(int8_t *a, int8_t *b) {
	for (unsigned i = 0xFFFFFFF; i--;);

	clock_t tStart = clock();

	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;

	for (unsigned i = 0xFFFFFFF; i--;);
	clock_t tEnd = clock() - tStart;

	printf("Time taken: %Lfms\n", (long double)(tEnd - tStart) / CLOCKS_PER_SEC * MULTIPLIER_MS);
}

void swapAddSub(int8_t *a, int8_t *b) {
	for (unsigned i = 0xFFFFFFF; i--;);

	clock_t tStart = clock();

	*a = *a + *b;
	*b = *a - *b;
	*a = *a - *b;

	for (unsigned i = 0xFFFFFFF; i--;);
	clock_t tEnd = clock() - tStart;

	printf("Time taken: %Lfms\n", (long double)(tEnd - tStart) / CLOCKS_PER_SEC * MULTIPLIER_MS);
}

void swapTempVar(int8_t *a, int8_t *b) {
	for (unsigned i = 0xFFFFFFF; i--;);

	clock_t tStart = clock();

	int8_t temp = *a;
	*a = *b;
	*b = temp;

	for (unsigned i = 0xFFFFFFF; i--;);
	clock_t tEnd = clock() - tStart;

	printf("Time taken: %Lfms\n", (long double)(tEnd - tStart) / CLOCKS_PER_SEC * MULTIPLIER_MS);
}

void printNumbers(int8_t a, int8_t b) {
	printf("a: %d\nb: %d\n\n", a, b);
}