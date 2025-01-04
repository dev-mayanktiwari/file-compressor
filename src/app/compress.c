#include "huffman.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    unsigned char byte;
    int position;
} BitWriter;

void init_bit_writer(BitWriter* writer) {
    writer->byte = 0;
    writer->position = 0;
}

void write_bit(FILE* output, BitWriter* writer, int bit) {
    writer->byte = (writer->byte << 1) | (bit & 1);
    writer->position++;
    
    if (writer->position == 8) {
        fwrite(&writer->byte, 1, 1, output);
        writer->byte = 0;
        writer->position = 0;
    }
}

void flush_bits(FILE* output, BitWriter* writer) {
    if (writer->position > 0) {
        writer->byte <<= (8 - writer->position);
        fwrite(&writer->byte, 1, 1, output);
    }
}

int compress_file(const char* filename) {
    printf("Compressing %s\n", filename);
    
    // Initialize all pointers to NULL
    FILE* input = NULL;
    FILE* output = NULL;
    unsigned char* buffer = NULL;
    CharFreq* freq_table = NULL;
    char* output_filename = NULL;
    HuffmanNode* root = NULL;
    
    // Initialize codes array
    HuffmanCode codes[256] = {0};
    for (int i = 0; i < 256; i++) {
        codes[i].code = NULL;
    }

    // Open input file
    input = fopen(filename, "rb");
    if (!input) {
        printf("Error: Cannot open input file\n");
        return 1;
    }

    // Get file size
    fseek(input, 0, SEEK_END);
    size_t file_size = ftell(input);
    fseek(input, 0, SEEK_SET);
    
    if (file_size == 0) {
        printf("Error: File is empty\n");
        fclose(input);
        return 1;
    }

    // Create output filename
    output_filename = malloc(strlen(filename) + 5);
    if (!output_filename) {
        printf("Error: Memory allocation failed for filename\n");
        fclose(input);
        return 1;
    }
    sprintf(output_filename, "%s.huf", filename);
    
    // Open output file
    output = fopen(output_filename, "wb");
    if (!output) {
        printf("Error: Cannot create output file\n");
        free(output_filename);
        fclose(input);
        return 1;
    }

    // Allocate buffer for file content
    buffer = malloc(file_size);
    if (!buffer) {
        printf("Error: Memory allocation failed for buffer\n");
        free(output_filename);
        fclose(input);
        fclose(output);
        return 1;
    }
    
    // Read file content
    size_t bytes_read = fread(buffer, 1, file_size, input);
    if (bytes_read != file_size) {
        printf("Error: Failed to read entire file\n");
        free(buffer);
        free(output_filename);
        fclose(input);
        fclose(output);
        return 1;
    }

    // Get frequency table
    int unique_chars;
    freq_table = count_frequencies(buffer, file_size, &unique_chars);
    if (!freq_table || unique_chars == 0) {
        printf("Error: Failed to create frequency table\n");
        free(buffer);
        free(output_filename);
        fclose(input);
        fclose(output);
        return 1;
    }

    // Build Huffman tree
    root = build_huffman_tree(freq_table, unique_chars);
    if (!root) {
        printf("Error: Failed to build Huffman tree\n");
        free(freq_table);
        free(buffer);
        free(output_filename);
        fclose(input);
        fclose(output);
        return 1;
    }

    // Generate Huffman codes
    char temp_code[256] = {0};
    generate_huffman_codes(root, codes, temp_code, 0);

    // Write header
    fwrite(&file_size, sizeof(file_size), 1, output);
    fwrite(&unique_chars, 1, 1, output);
    fwrite(freq_table, sizeof(CharFreq), unique_chars, output);

    // Write compressed data
    BitWriter writer;
    init_bit_writer(&writer);

    for (size_t i = 0; i < file_size; i++) {
        if (codes[buffer[i]].code != NULL) {
            for (int j = 0; codes[buffer[i]].code[j]; j++) {
                write_bit(output, &writer, codes[buffer[i]].code[j] - '0');
            }
        }
    }

    flush_bits(output, &writer);

    // Clean up
    for (int i = 0; i < 256; i++) {
        if (codes[i].code != NULL) {
            free(codes[i].code);
        }
    }
    
    if (root) free_huffman_tree(root);
    if (freq_table) free(freq_table);
    if (buffer) free(buffer);
    if (output_filename) free(output_filename);
    if (input) fclose(input);
    if (output) fclose(output);

    printf("File compressed successfully!\n");
    return 0;
}