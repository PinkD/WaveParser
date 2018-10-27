#include "wave_reader.h"
#include "log.h"

#include <malloc.h>

Wave *read_wave(char *path) {
    FILE *f = fopen(path, "rb");
    if (!f) {
        return NULL;
    }
    WaveHeader *header = read_wave_header(f);
    WaveData *waveData = read_wave_data(f);
    Wave *wave = malloc(sizeof(Wave));
    wave->header = header;
    wave->data = waveData;

    while (waveData) {
        WaveData *d = waveData;
        waveData = read_wave_data(f);
        d->next = waveData;
    }
    return wave;
}

WaveHeader *read_wave_header(FILE *f) {
    WaveHeader *header = malloc(sizeof(WaveHeader));
    fread(header->riff.riff, 4, 1, f);
    fread(&header->riff.size, sizeof(uint32), 1, f);
    fread(header->riff.wave, 4, 1, f);

    fread(header->fmt.fmt, 4, 1, f);

    fread(&header->fmt.size, sizeof(uint32), 1, f);
    fread(&header->fmt.format, sizeof(uint16), 1, f);
    fread(&header->fmt.channel, sizeof(uint16), 1, f);
    fread(&header->fmt.sample_rate, sizeof(uint32), 1, f);
    fread(&header->fmt.byte_rate, sizeof(uint32), 1, f);
    fread(&header->fmt.block_align, sizeof(uint16), 1, f);
    fread(&header->fmt.bits_per_sample, sizeof(uint16), 1, f);
    if (header->fmt.size > 0x10) {
        size_t size = header->fmt.size - 0x10;
        char discard[size];
        char buff[5];
        fread(discard, size, 1, f);
        log_w("detect extra data in fmt header:");
        for (int i = 0; i < size; i++) {
            sprintf(buff, "0x%02x", discard[i]);
            log_w(buff);
        }
        log_w("end of extra data");
    }
    return header;
}

WaveData *read_wave_data(FILE *f) {
    WaveData *waveData = malloc(sizeof(WaveData));
    size_t result = fread(waveData->data_chunk_header, 4, 1, f);
    if (!result) {
        free(waveData);
        return NULL;
    }
    fread(&waveData->data_size, sizeof(uint32), 1, f);
    byte *data = malloc(waveData->data_size);
    fread(data, waveData->data_size, 1, f);
    waveData->data = data;
    return waveData;
}
