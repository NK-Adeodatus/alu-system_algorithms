#include <stdlib.h>
#include "heap.h"

/**
 * tree_delete - Recursively frees all nodes in a binary tree
 *
 * @node: Pointer to the root node of the tree/subtree
 * @free_data: Function to free node data, or NULL to skip freeing data
 */
static void tree_delete(binary_tree_node_t *node, void (*free_data)(void *))
{
	if (node == NULL)
		return;

	tree_delete(node->left, free_data);
	tree_delete(node->right, free_data);

	if (free_data != NULL)
		free_data(node->data);

	free(node);
}

/**
 * heap_delete - Deallocates a heap
 *
 * @heap: Pointer to the heap to delete
 * @free_data: Function to free node data, or NULL to skip freeing data
 */
void heap_delete(heap_t *heap, void (*free_data)(void *))
{
	if (heap == NULL)
		return;

	tree_delete(heap->root, free_data);
	free(heap);
}
