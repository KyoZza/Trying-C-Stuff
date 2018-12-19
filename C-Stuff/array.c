#include "array.h"



uint16_t stringLength(const uint8_t *str) {
	uint16_t length = 0;

	while (*str) {
		length++;
		*str++;
	}

	return length;
}