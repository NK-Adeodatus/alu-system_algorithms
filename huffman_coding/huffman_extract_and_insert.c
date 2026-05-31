#include <stdlib.h>
#include "huffman.h"

/**
 * huffman_extract_and_insert - Extracts two nodes from the priority queue
 * and inserts a new combined node
 *
 * @priority_queue: Pointer to the priority queue
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_extract_and_insert(heap_t *priority_queue)
{
	binary_tree_node_t *left, *right, *parent;
	symbol_t *sym_left, *sym_right, *sym_parent;
	size_t combined_freq;

	if (priority_queue == NULL)
		return (0);

	left = (binary_tree_node_t *)heap_extract(priority_queue);
	if (left == NULL)
		return (0);

	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (right == NULL)
		return (0);

	sym_left = (symbol_t *)left->data;
	sym_right = (symbol_t *)right->data;
	combined_freq = sym_left->freq + sym_right->freq;

	sym_parent = symbol_create(-1, combined_freq);
	if (sym_parent == NULL)
		return (0);

	parent = binary_tree_node(NULL, sym_parent);
	if (parent == NULL)
	{
		free(sym_parent);
		return (0);
	}

	parent->left = left;
	parent->right = right;
	left->parent = parent;
	right->parent = parent;

	if (heap_insert(priority_queue, parent) == NULL)
	{
		free(sym_parent);
		free(parent);
		return (0);
	}

	return (1);
}
