#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap/heap.h"

typedef struct symbol_s
{
    char data;
    size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);

#endif /* HUFFMAN_H */
