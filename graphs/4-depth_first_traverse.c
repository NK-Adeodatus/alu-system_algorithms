#include <stdlib.h>
#include "graphs.h"

/**
 * dfs - Recursive depth-first traversal helper
 *
 * @v: Pointer to the current vertex
 * @depth: Current depth from the starting vertex
 * @visited: Array tracking visited vertex indices
 * @action: Function to call on each visited vertex
 * @max_depth: Pointer to the maximum depth reached
 */
static void dfs(const vertex_t *v, size_t depth, char *visited,
		void (*action)(const vertex_t *, size_t), size_t *max_depth)
{
	edge_t *edge;

	if (visited[v->index])
		return;
	visited[v->index] = 1;
	action(v, depth);
	if (depth > *max_depth)
		*max_depth = depth;
	edge = v->edges;
	while (edge)
	{
		dfs(edge->dest, depth + 1, visited, action, max_depth);
		edge = edge->next;
	}
}

/**
 * depth_first_traverse - Traverses a graph using depth-first algorithm
 *
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest vertex depth reached, or 0 on failure
 */
size_t depth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	char *visited;
	size_t max_depth;

	if (!graph || !action || !graph->vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
		return (0);
	max_depth = 0;
	dfs(graph->vertices, 0, visited, action, &max_depth);
	free(visited);
	return (max_depth);
}
