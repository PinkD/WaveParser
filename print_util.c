#include <stdio.h>
#include "print_util.h"
#include "log.h"

const int BUFFER_SIZE = 1024;

void print_header(WaveHeader *header) {
    char buff[BUFFER_SIZE];
    sprintf(buff,
            "\n{\n"
                    "\triff: {\n"
                    "\t\triff: \"%c%c%c%c\",\n"
                    "\t\tsize: %d,\n"
                    "\t\twave: \"%c%c%c%c\",\n"
                    "\t},\n"
                    "\tfmt: {\n"
                    "\t\tfmt: \"%c%c%c%c\",\n"
                    "\t\tsize: %d,\n"
                    "\t\tformat: %d,\n"
                    "\t\tchannel: %d,\n"
                    "\t\tsample_rate: %d,\n"
                    "\t\tbyte_rate: %d,\n"
                    "\t\tblock_align: %d,\n"
                    "\t\tbits_per_sample: %d,\n"
                    "\t},\n"
                    "}",
            header->riff.riff[0], header->riff.riff[1], header->riff.riff[2], header->riff.riff[3],
            header->riff.size,
            header->riff.wave[0], header->riff.wave[1], header->riff.wave[2], header->riff.wave[3],
            header->fmt.fmt[0], header->fmt.fmt[1], header->fmt.fmt[2], header->fmt.fmt[3],
            header->fmt.size,
            header->fmt.format,
            header->fmt.channel,
            header->fmt.sample_rate,
            header->fmt.byte_rate,
            header->fmt.block_align,
            header->fmt.bits_per_sample
    );
    log_d(buff);
}

void print_data(WaveData *data) {
    char buff[BUFFER_SIZE];
    sprintf(buff, "\n{\n"
                    "\theader: \"%c%c%c%c\"\n"
                    "\tsize: %d\n"
                    "\tdata:%p\n"
                    "}",
            data->data_chunk_header[0], data->data_chunk_header[1], data->data_chunk_header[2], data->data_chunk_header[3],
            data->data_size,
            &data->data);
    log_d(buff);
}
