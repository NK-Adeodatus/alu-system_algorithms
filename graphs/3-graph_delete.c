#include <stdlib.h>
#include "graphs.h"

/**
 * free_edges - Frees all edges in a vertex's edge list
 *
 * @edges: Pointer to the head of the edge linked list
 */
static void free_edges(edge_t *edges)
{
	edge_t *current, *next;

	current = edges;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

/**
 * graph_delete - Completely deletes a graph
 *
 * @graph: Pointer to the graph to delete
 */
void graph_delete(graph_t *graph)
{
	vertex_t *current, *next;

	if (!graph)
		return;
	current = graph->vertices;
	while (current)
	{
		next = current->next;
		free_edges(current->edges);
		free(current->content);
		free(current);
		current = next;
	}
	free(graph);
}
