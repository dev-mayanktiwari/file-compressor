#include <stdio.h>
#include <string.h>
#include "huffman.h"

void print_usage()
{
    printf("Usage:\n");
    printf("For compression: ./huffman comp <input_file> \n");
    printf("For decompression: ./huffman decomp <input_file>\n");
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        print_usage();
        return 1;
    }

    char *command = argv[1];
    char *filename = argv[2];

    if (strcmp(command, "comp") == 0)
    {
        printf("Compressing %s\n", filename);

        // TODO: Implement the compress_file function
        return compress_file(filename);
    }
    else if (strcmp(command, "decomp") == 0)
    {
        printf("Decompressing %s\n", filename);

        // TODO: Implement the decompress_file function
        return decompress_file(filename);
    }
    else
    {
        printf("Invalid command\n");
        print_usage();
        return 1;
    }
}