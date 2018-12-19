#include "convert.h"

void intToString(int32_t value, uint8_t *str) {
	uint8_t convert[11];

	if (!value) {
		convert[0] = '0';
		convert[1] = '\0';
		strcpy(str, convert);
		
		return;
	}

	int32_t devider = 10;
	uint8_t i = 0;
	for ( ; value; i++, devider *= 10) {
		uint32_t r = value % devider;
		uint8_t ch = r * 10 / devider + ASCII_0;
		value -= r;

		convert[i] = ch;
		printf("%i.char: %c\n", i, ch);
	}
	convert[i] = '\0';
	strrev(convert);
	strcpy(str, convert);
}