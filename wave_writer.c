#include "wave_writer.h"
#include "log.h"

int write_wave(char *path, Wave *wave) {
    FILE *f = fopen(path, "wb");
    if (!f) {
        log_e("Fail to write file");
        return -1;
    }
    log_v("Saving wav file...");
    write_header(f, wave->header);
    WaveData *data = wave->data;
    while (data) {
        write_data(f, data);
        data = data->next;
    }
    log_v("File saved");
}

void write_header(FILE *f, WaveHeader *header) {
    log_v("Saving wav header...");
    fwrite(header->riff.riff, 4, 1, f);
    fwrite(&header->riff.size, sizeof(uint32), 1, f);
    fwrite(header->riff.wave, 4, 1, f);

    if (header->fmt.size > 0x10) {
        log_w("NOTE: Extra data won't be saved");
    }

    fwrite(header->fmt.fmt, 4, 1, f);
    fwrite(&header->fmt.size, sizeof(uint32), 1, f);
    fwrite(&header->fmt.format, sizeof(uint16), 1, f);
    fwrite(&header->fmt.channel, sizeof(uint16), 1, f);
    fwrite(&header->fmt.sample_rate, sizeof(uint32), 1, f);
    fwrite(&header->fmt.byte_rate, sizeof(uint32), 1, f);
    fwrite(&header->fmt.block_align, sizeof(uint16), 1, f);
    fwrite(&header->fmt.bits_per_sample, sizeof(uint16), 1, f);
    log_v("Header saved");
}

void write_data(FILE *f, WaveData *data) {
    log_v("Saving wav data chunk...");
    fwrite(data->data_chunk_header, 4, 1, f);
    fwrite(&data->data_size, sizeof(uint32), 1, f);
    fwrite(data->data, data->data_size, 1, f);
    log_v("Chunk saved");
}
