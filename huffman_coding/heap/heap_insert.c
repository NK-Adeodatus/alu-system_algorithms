#include <stdlib.h>
#include "heap.h"

/**
 * get_insert_parent - Finds the parent node for the next insertion point
 *
 * @root: Root of the heap
 * @size: Current size of the heap
 *
 * Return: Pointer to the parent node where the new node should be inserted
 *
 * Description: Uses the binary representation of (size + 1) to navigate
 * the tree. For a heap of size n, the new node goes at position (n + 1).
 * Reading the bits of (n + 1) from MSB-1 down to bit 1 gives the path
 * (0 = left, 1 = right) from root to the new node's parent.
 */
static binary_tree_node_t *get_insert_parent(binary_tree_node_t *root,
	size_t size)
{
	size_t path;
	size_t levels;
	binary_tree_node_t *node;

	path = size + 1;
	levels = 0;
	while (path > 1)
	{
		path >>= 1;
		levels++;
	}

	path = size + 1;
	node = root;
	while (levels > 1)
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
 * sift_up - Restores min-heap property by bubbling a node up
 *
 * @heap: Pointer to the heap
 * @node: Node to sift up
 *
 * Return: Pointer to the node after sifting (its final position)
 */
static binary_tree_node_t *sift_up(heap_t *heap, binary_tree_node_t *node)
{
	void *tmp;

	while (node->parent &&
		heap->data_cmp(node->data, node->parent->data) < 0)
	{
		tmp = node->data;
		node->data = node->parent->data;
		node->parent->data = tmp;
		node = node->parent;
	}
	return (node);
}

/**
 * heap_insert - Inserts a value in a Min Binary Heap
 *
 * @heap: Pointer to the heap
 * @data: Pointer to the data to store in the new node
 *
 * Return: Pointer to the created node, or NULL if it fails
 */
binary_tree_node_t *heap_insert(heap_t *heap, void *data)
{
	binary_tree_node_t *parent;
	binary_tree_node_t *node;

	if (heap == NULL || data == NULL)
		return (NULL);

	if (heap->root == NULL)
	{
		heap->root = binary_tree_node(NULL, data);
		if (heap->root == NULL)
			return (NULL);
		heap->size++;
		return (heap->root);
	}

	parent = get_insert_parent(heap->root, heap->size);

	node = binary_tree_node(parent, data);
	if (node == NULL)
		return (NULL);

	if (parent->left == NULL)
		parent->left = node;
	else
		parent->right = node;

	heap->size++;

	sift_up(heap, node);

	return (node);
}
