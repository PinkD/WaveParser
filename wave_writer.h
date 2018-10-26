#ifndef WAVEPARSER_WAVE_WRITER_H
#define WAVEPARSER_WAVE_WRITER_H

#include "wave_common.h"
#include <stdio.h>

/**
 * write wave file
 * @param path
 * @param wave
 * @return 0->OK, -1->Error
 */
int write_wave(char *path, Wave *wave);

void write_header(FILE *f, WaveHeader *header);

void write_data(FILE *f, WaveData *data);

/**
 * write PCM part to file
 * @param path
 * @param wave
 * @return 0->OK, -1->Error
 */
int write_PCM(char *path, Wave *wave);

#endif
