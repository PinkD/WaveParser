#include <stdio.h>
#include <stdlib.h>
#include "common_util.h"

char *int_to_str(int value) {
    static char int_str[12];
    sprintf(int_str, "%d", value);
    return int_str;
}

char *float_to_str(float value) {
    static char float_str[6];
    sprintf(float_str, "%3.2f", value);
    return float_str;
}

byte read_byte(FILE *f) {
    byte tmp;
    if (fread(&tmp, 1, 1, f) != 1) {//just in case
        fprintf(stderr, "EOF\n");
        exit(-1);
    }
    return tmp;
}

void write_byte(FILE *f, byte in) {
    fputc(in, f);
}

void printBits(uint32 num) {
    int counter = 0;
    for (int bit = 0; bit < (sizeof(int) * 8); bit++) {
        printf("%i", (num & 0x80000000) >> 31);
        counter++;
        if (counter == 8) {
            counter -= 8;
            printf(" ");
        }
        num = num << 1;
    }
    printf("\n");
}
