#include <stdlib.h>
#include "huffman.h"

/**
 * create_parent - Creates a combined nested node from two extracted nodes
 *
 * @left: Left child nested node
 * @right: Right child nested node
 *
 * Return: Pointer to the new parent nested node, or NULL on failure
 */
static binary_tree_node_t *create_parent(binary_tree_node_t *left,
	binary_tree_node_t *right)
{
	symbol_t *sym_left, *sym_right, *sym_parent;
	binary_tree_node_t *parent;
	size_t combined_freq;

	sym_left = (symbol_t *)left->data;
	sym_right = (symbol_t *)right->data;
	combined_freq = sym_left->freq + sym_right->freq;

	sym_parent = symbol_create(-1, combined_freq);
	if (sym_parent == NULL)
		return (NULL);

	parent = binary_tree_node(NULL, sym_parent);
	if (parent == NULL)
	{
		free(sym_parent);
		return (NULL);
	}

	parent->left = left;
	parent->right = right;
	left->parent = parent;
	right->parent = parent;

	return (parent);
}

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

	if (priority_queue == NULL)
		return (0);

	left = (binary_tree_node_t *)heap_extract(priority_queue);
	if (left == NULL)
		return (0);

	right = (binary_tree_node_t *)heap_extract(priority_queue);
	if (right == NULL)
		return (0);

	parent = create_parent(left, right);
	if (parent == NULL)
		return (0);

	if (heap_insert(priority_queue, parent) == NULL)
	{
		free(parent->data);
		free(parent);
		return (0);
	}

	return (1);
}
