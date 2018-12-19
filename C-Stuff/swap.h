#pragma once

#include <stdio.h>
#include <stdint.h>
#include <time.h>

#define MULTIPLIER_MS 1000
#define MULTIPLIER_uS 1000000

// Fastest Swap
void swap(int8_t *a, int8_t *b);

void swapBitOperator(int8_t *a, int8_t *b);
void swapAddSub(int8_t *a, int8_t *b);
void swapTempVar(int8_t *a, int8_t *b);

void printNumbers(int8_t a, int8_t b);