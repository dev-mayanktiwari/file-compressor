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


void flush_bits(FILE* output, BitWriter* writer)
{
    if (writer->position > 0)
    {
        writer->byte <<= (8 - writer->position);
        fwrite(&writer->byte, 1, 1, output);
    }
}

int compress_file(const char* filename) {
    FILE *input = fopen(filename, "rb");
    if (!input) {
        printf("Error: Could not open file %s\n", filename);
        return 1;
    }

    char* output_filename = malloc(strlen(filename) + 5);
    sprintf(output_filename, "%s.huf", filename);
    
    FILE *output = fopen(output_filename, "wb");
    if (!output) {
        printf("Error: Could not create file %s\n", output_filename);
        fclose(input);
        free(output_filename);
        return 1;
    }

    fseek(input, 0, SEEK_END);
    size_t file_size = ftell(input);
    fseek(input, 0, SEEK_SET);

    unsigned char* buffer = malloc(file_size);
    if (!buffer) {
        printf("Error: Could not allocate memory for file buffer\n");
        fclose(input);
        fclose(output);
        free(output_filename);
        return 1;
    }

    int unique_chars;
    CharFreq* frequency_table = count_frequencies(buffer, file_size, &unique_chars);
    if (!frequency_table) {
        printf("Error: Could not count character frequencies\n");
        fclose(input);
        fclose(output);
        free(output_filename);
        free(buffer);
        return 1;
    }


    
}
