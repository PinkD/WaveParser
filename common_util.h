#ifndef WAVEPARSER_COMMON_UTIL_H
#define WAVEPARSER_COMMON_UTIL_H

#include "base_def.h"

/**
 * int to str
 * !!!WARNING!!! this function can not be used in synchronization place
 * @param value int
 * @return str
 */
char *int_to_str(int value);

/**
 * float to str
 * !!!WARNING!!! this function can not be used in synchronization place
 * @param value float
 * @return str, format is `%3.2f`
 */
char *float_to_str(float value);

/**
 * write a single byte to file
 * @param f file
 * @param in byte to write
 */
void write_byte(FILE *f, byte in);

void printBits(uint32 num);


#endif
