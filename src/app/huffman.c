#include "huffman.h"
#include <stdio.h>
#include <string.h>

// Create a new Huffman tree node
HuffmanNode *create_node(unsigned char character, unsigned frequency)
{
    HuffmanNode *node = (HuffmanNode *)malloc(sizeof(HuffmanNode));
    if (node == NULL)
    {
        return NULL;
    }

    node->data = character;
    node->freq = frequency;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Free the Huffman tree
void free_huffman_tree(HuffmanNode *root)
{
    if (root == NULL)
        return;
    free_huffman_tree(root->left);
    free_huffman_tree(root->right);
    free(root);
}

// Count frequency of each character in the input data
CharFreq *count_frequencies(const unsigned char *data, size_t size, int *unique_chars)
{
    unsigned int frequencies[256] = {0};

    for (size_t i = 0; i < size; i++)
    {
        frequencies[data[i]]++;
    }

    *unique_chars = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] > 0)
        {
            (*unique_chars)++;
        }
    }

    CharFreq *freq_table = (CharFreq *)malloc(*unique_chars * sizeof(CharFreq));
    if (freq_table == NULL)
    {
        return NULL;
    }

    int j = 0;
    for (int i = 0; i < 256; i++)
    {
        if (frequencies[i] > 0)
        {
            freq_table[j].character = (unsigned char)i;
            freq_table[j].frequency = frequencies[i];
            j++;
        }
    }

    return freq_table;
}

// Build Huffman tree from frequency table
HuffmanNode *build_huffman_tree(CharFreq *freq_table, int size)
{
    if (size == 0)
        return NULL;

    HuffmanNode **nodes = (HuffmanNode **)malloc(size * sizeof(HuffmanNode *));
    if (nodes == NULL)
        return NULL;

    for (int i = 0; i < size; i++)
    {
        nodes[i] = create_node(freq_table[i].character, freq_table[i].frequency);
    }

    int nodes_left = size;
    while (nodes_left > 1)
    {
        HuffmanNode *new_node = create_node(0, nodes[0]->freq + nodes[1]->freq);
        new_node->left = nodes[0];
        new_node->right = nodes[1];

        nodes_left--;
        for (int i = 0; i < nodes_left - 1; i++)
        {
            nodes[i] = nodes[i + 2];
        }
        nodes[nodes_left - 1] = new_node;

        for (int i = nodes_left - 1; i > 0; i--)
        {
            if (nodes[i]->freq < nodes[i - 1]->freq)
            {
                HuffmanNode *temp = nodes[i];
                nodes[i] = nodes[i - 1];
                nodes[i - 1] = temp;
            }
        }
    }

    HuffmanNode *root = nodes[0];
    free(nodes);
    return root;
}

void generate_huffman_codes(HuffmanNode *root, HuffmanCode *codes, char *code, int depth)
{
    if (root == NULL)
        return;

    if (root->left == NULL && root->right == NULL)
    {
        code[depth] = '\0';
        codes[root->data].character = root->data;
        codes[root->data].code = strdup(code);
        return;
    }

    code[depth] = '0';
    generate_huffman_codes(root->left, codes, code, depth + 1);

    code[depth] = '1';
    generate_huffman_codes(root->right, codes, code, depth + 1);
}