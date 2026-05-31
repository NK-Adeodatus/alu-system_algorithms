#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "huffman.h"

/**
 * tree_free - Recursively frees all nodes of the Huffman tree
 *
 * @node: Pointer to the root node of the tree/subtree
 */
static void tree_free(binary_tree_node_t *node)
{
	if (node == NULL)
		return;

	tree_free(node->left);
	tree_free(node->right);

	free(node->data);
	free(node);
}

/**
 * traverse - Recursively traverses the Huffman tree and prints codes
 *
 * @node: Current node
 * @code: Buffer holding the current code string
 * @depth: Current depth (length of code so far)
 *
 * Return: 1 on success, 0 on failure
 */
static int traverse(binary_tree_node_t *node, char *code, size_t depth)
{
	symbol_t *symbol;

	if (node == NULL)
		return (1);

	if (node->left == NULL && node->right == NULL)
	{
		symbol = (symbol_t *)node->data;
		code[depth] = '\0';
		printf("%c: %s\n", symbol->data, code);
		return (1);
	}

	code[depth] = '0';
	if (!traverse(node->left, code, depth + 1))
		return (0);

	code[depth] = '1';
	if (!traverse(node->right, code, depth + 1))
		return (0);

	return (1);
}

/**
 * huffman_codes - Builds Huffman tree and prints codes for each symbol
 *
 * @data: Array of characters
 * @freq: Array of associated frequencies
 * @size: Size of both arrays
 *
 * Return: 1 on success, 0 on failure
 */
int huffman_codes(char *data, size_t *freq, size_t size)
{
	binary_tree_node_t *root;
	char code[4096];
	int result;

	if (data == NULL || freq == NULL || size == 0)
		return (0);

	root = huffman_tree(data, freq, size);
	if (root == NULL)
		return (0);

	result = traverse(root, code, 0);

	tree_free(root);

	return (result);
}
