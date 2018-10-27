#ifndef WAVEPARSER_READER_H
#define WAVEPARSER_READER_H

#include <stdio.h>
#include "wave_common.h"

/**
 * read wave file
 * @param path file path
 * @return Wave
 */
Wave *read_wave(char *path);

/**
 * read wave file header
 * @param f file
 * @return WaveHeader
 */
WaveHeader *read_wave_header(FILE *f);

/**
 * read data block, data are samples only when `data_chunk_header` is 'data`
 * @param f file ptr
 * @return WaveData
 */
WaveData *read_wave_data(FILE *f);

#endif