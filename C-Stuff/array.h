#pragma once

#include <stdint.h>

#define ARRAY_LENGTH(arr) (sizeof(arr) / sizeof(arr[0]))
#define STRING_LENGTH(str) (sizeof(str) - 1)
//#define STRING_LENGTH(str) (stringLength(str))

uint16_t stringLength(const uint8_t *str);