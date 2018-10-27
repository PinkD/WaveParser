#ifndef WAVEPARSER_WAVE_COMMON_H
#define WAVEPARSER_WAVE_COMMON_H

#include "base_def.h"

typedef struct {
    byte riff[4];
    uint32 size;
    byte wave[4];
} RiffHeader;

typedef struct {
    byte fmt[4];
    uint32 size;
    uint16 format;
    uint16 channel;
    uint32 sample_rate;
    uint32 byte_rate;
    uint16 block_align;
    uint16 bits_per_sample;
} FmtHeader;

typedef struct {
    RiffHeader riff;
    FmtHeader fmt;
} WaveHeader;


typedef struct _WaveData {
    byte data_chunk_header[4];
    uint32 data_size;
    byte *data;
    struct _WaveData *next;
} WaveData;


typedef struct {
    WaveHeader *header;
    WaveData *data;
} Wave;

void free_wave(Wave *wave);

void free_wave_header(WaveHeader *header);

void free_wave_data(WaveData *data);

#endif
