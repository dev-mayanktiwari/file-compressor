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


