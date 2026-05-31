#include <stdlib.h>
#include "heap.h"

/**
 * get_last_node - Finds the last node in the heap (rightmost of last level)
 *
 * @root: Root of the heap
 * @size: Current size of the heap
 *
 * Return: Pointer to the last node
 *
 * Description: Uses the binary representation of size to navigate
 * the path from root to the last node (0 = left, 1 = right).
 */
static binary_tree_node_t *get_last_node(binary_tree_node_t *root,
	size_t size)
{
	size_t levels;
	size_t path;
	binary_tree_node_t *node;

	path = size;
	levels = 0;
	while (path > 1)
	{
		path >>= 1;
		levels++;
	}

	path = size;
	node = root;
	while (levels > 0)
	{
		if (path & (1 << (levels - 1)))
			node = node->right;
		else
			node = node->left;
		levels--;
	}
	return (node);
}

/**
 * sift_down - Restores min-heap property by pushing a node down
 *
 * @heap: Pointer to the heap
 * @node: Node to sift down
 */
static void sift_down(heap_t *heap, binary_tree_node_t *node)
{
	binary_tree_node_t *smallest;
	void *tmp;

	while (node->left != NULL)
	{
		smallest = node->left;
		if (node->right &&
			heap->data_cmp(node->right->data, node->left->data) < 0)
			smallest = node->right;

		if (heap->data_cmp(node->data, smallest->data) <= 0)
			break;

		tmp = node->data;
		node->data = smallest->data;
		smallest->data = tmp;
		node = smallest;
	}
}

/**
 * heap_extract - Extracts the root value of a Min Binary Heap
 *
 * @heap: Pointer to the heap
 *
 * Return: Pointer to the data stored in the root node, or NULL on failure
 */
void *heap_extract(heap_t *heap)
{
	void *extracted;
	binary_tree_node_t *last;

	if (heap == NULL || heap->root == NULL)
		return (NULL);

	extracted = heap->root->data;

	if (heap->size == 1)
	{
		free(heap->root);
		heap->root = NULL;
		heap->size = 0;
		return (extracted);
	}

	last = get_last_node(heap->root, heap->size);

	heap->root->data = last->data;

	if (last->parent->right == last)
		last->parent->right = NULL;
	else
		last->parent->left = NULL;

	free(last);
	heap->size--;

	sift_down(heap, heap->root);

	return (extracted);
}
