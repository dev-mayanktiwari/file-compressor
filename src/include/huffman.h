#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>
#include <stdlib.h>

typedef struct
{
    unsigned char character;
    unsigned int frequency;
} CharFreq;
typedef struct HuffmanNode
{
    unsigned char data;
    unsigned int freq;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
} HuffmanNode;

typedef struct
{
    unsigned char character;
    char *code;
} HuffmanCode;

// FILE COMPRESSION & DECOMPRESSION
int compress_file(const char *filename);
int decompress_file(const char *filename);

// HUFFMAN TREE
HuffmanNode *create_node(unsigned char character, unsigned int frequency);
void free_huffman_tree(HuffmanNode *root);

// COMPRESSION HELPER FUNCTIONS
CharFreq *count_frequencies(const unsigned char *data, size_t size, int *unique_chars);
HuffmanNode *build_huffman_tree(CharFreq *frequency_table, int size);
void generate_huffman_codes(HuffmanNode *root, HuffmanCode *codes, char *code, int depth);

#endif