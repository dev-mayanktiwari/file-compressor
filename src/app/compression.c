#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BitWriter
{
    unsigned char byte;
    int position;
} BitWriter;

void init_bit_writer(BitWriter *writer)
{
    writer->byte = 0;
    writer->position = 0;
}

void write_bit(FILE *output, BitWriter *writer, int bit)
{
    writer->byte = (writer->byte << 1) | (bit & 1);
    writer->position++;

    if (writer->position == 8)
    {
        fwrite(&writer->byte, 1, 1, output);
        writer->byte = 0;
        writer->position = 0;
    }
}


