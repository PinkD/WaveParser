#ifndef WAVEPARSER_LIBRARY_H
#define WAVEPARSER_LIBRARY_H

#include <stdio.h>
#include "wave_common.h"

Wave *read_wave(char *path);

/**
 * read wave file header
 * @param f file
 * @return WaveHeader
 */
WaveHeader *read_header(FILE *f);

WaveData *read_data(FILE *f);

#endif