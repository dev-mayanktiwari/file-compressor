#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <stdint.h>

struct HuffmanNode
{
    unsigned char data;
    unsigned int freq;
    struct HuffmanNode *left;
    struct HuffmanNode *right;
};

int compress_file(const char *filename);
int decompress_file(const char *filename);

#endif