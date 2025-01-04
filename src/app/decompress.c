// src/app/decompress.c
#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to handle bit reading
typedef struct
{
    unsigned char byte;
    int position;
} BitReader;

// Initialize bit reader
void init_bit_reader(BitReader *reader)
{
    reader->byte = 0;
    reader->position = 8; // Force new byte read
}

// Read a single bit from file
int read_bit(FILE *input, BitReader *reader)
{
    // If we've used all bits in current byte, read next byte
    if (reader->position == 8)
    {
        if (fread(&reader->byte, 1, 1, input) != 1)
        {
            return -1; // EOF or error
        }
        reader->position = 0;
    }

    // Get current bit and advance position
    int bit = (reader->byte >> (7 - reader->position)) & 1;
    reader->position++;
    return bit;
}

int decompress_file(const char *filename)
{
    // Check if file has .huf extension
    if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".huf") != 0)
    {
        printf("Error: Input file must have .huf extension\n");
        return 1;
    }

    FILE *input = fopen(filename, "rb");
    if (!input)
    {
        printf("Error: Cannot open input file\n");
        return 1;
    }

    // Create output filename (remove .huf extension)
    char *output_filename = malloc(strlen(filename) - 3);
    strncpy(output_filename, filename, strlen(filename) - 4);
    output_filename[strlen(filename) - 4] = '\0';

    FILE *output = fopen(output_filename, "wb");
    if (!output)
    {
        printf("Error: Cannot create output file\n");
        free(output_filename);
        fclose(input);
        return 1;
    }

    // Read header
    // 1. Original file size
    size_t original_size;
    fread(&original_size, sizeof(size_t), 1, input);

    // 2. Number of unique characters
    unsigned char unique_chars;
    fread(&unique_chars, 1, 1, input);

    // 3. Read frequency table
    CharFreq *freq_table = malloc(unique_chars * sizeof(CharFreq));
    fread(freq_table, sizeof(CharFreq), unique_chars, input);

    // Rebuild Huffman tree
    HuffmanNode *root = build_huffman_tree(freq_table, unique_chars);
    if (!root)
    {
        printf("Error: Failed to rebuild Huffman tree\n");
        free(freq_table);
        free(output_filename);
        fclose(input);
        fclose(output);
        return 1;
    }

    // Read compressed data bit by bit and decode
    BitReader reader;
    init_bit_reader(&reader);
    size_t bytes_written = 0;
    HuffmanNode *current = root;

    while (bytes_written < original_size)
    {
        int bit = read_bit(input, &reader);
        if (bit == -1)
        {
            printf("Error: Unexpected end of file\n");
            break;
        }

        // Traverse tree according to bit
        current = (bit == 0) ? current->left : current->right;

        // If we reach a leaf node, we have a character
        if (current->left == NULL && current->right == NULL)
        {
            fwrite(&current->data, 1, 1, output);
            bytes_written++;
            current = root; // Start over from root
        }
    }

    // Clean up
    free_huffman_tree(root);
    free(freq_table);
    free(output_filename);
    fclose(input);
    fclose(output);

    printf("File decompressed successfully!\n");
    return 0;
}