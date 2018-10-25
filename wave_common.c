#include <malloc.h>
#include "wave_common.h"

void free_wave(Wave *wave) {
    free_header(wave->header);
    WaveData *data = wave->data;
    while (data) {
        WaveData *d = data;
        data = data->next;
        free_data(d);
    }
}

void free_header(WaveHeader *header){
    free(header);
}

void free_data(WaveData *data) {
    free(data->data);
    free(data);
}
