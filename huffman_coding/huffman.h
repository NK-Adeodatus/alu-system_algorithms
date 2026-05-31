#ifndef HUFFMAN_H
#define HUFFMAN_H

#include "heap/heap.h"

typedef struct symbol_s
{
    char data;
    size_t freq;
} symbol_t;

symbol_t *symbol_create(char data, size_t freq);

/* huffman_priority_queue.c */
heap_t *huffman_priority_queue(char *data, size_t *freq, size_t size);

/* huffman_extract_and_insert.c */
int huffman_extract_and_insert(heap_t *priority_queue);

/* huffman_tree.c */
binary_tree_node_t *huffman_tree(char *data, size_t *freq, size_t size);

/* huffman_codes.c */
int huffman_codes(char *data, size_t *freq, size_t size);

#endif /* HUFFMAN_H */
