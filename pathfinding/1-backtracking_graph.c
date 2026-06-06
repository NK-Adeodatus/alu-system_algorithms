#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

/**
 * bt_graph_recurse - Recursive helper for graph backtracking search
 *
 * @current: current vertex being visited
 * @target: target vertex to reach
 * @visited: boolean array indexed by vertex index
 * @path: queue to build the path into
 *
 * Return: 1 if path found, 0 otherwise
 */
static int bt_graph_recurse(vertex_t const *current,
		vertex_t const *target, char *visited, queue_t *path)
{
	edge_t *edge;
	char *label;

	if (visited[current->index])
		return (0);

	printf("Checking %s\n", current->content);
	visited[current->index] = 1;

	if (strcmp(current->content, target->content) == 0)
	{
		label = strdup(current->content);
		if (!label)
			return (0);
		queue_push_front(path, label);
		return (1);
	}

	for (edge = current->edges; edge; edge = edge->next)
	{
		if (bt_graph_recurse(edge->dest, target, visited, path))
		{
			label = strdup(current->content);
			if (!label)
				return (0);
			queue_push_front(path, label);
			return (1);
		}
	}

	return (0);
}

/**
 * backtracking_graph - Finds a path in a graph using backtracking
 *
 * @graph: pointer to the graph to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: queue of char * vertex names from start to target, or NULL
 */
queue_t *backtracking_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	char *visited;
	queue_t *path;

	visited = calloc(graph->nb_vertices, sizeof(*visited));
	if (!visited)
		return (NULL);

	path = queue_create();
	if (!path)
	{
		free(visited);
		return (NULL);
	}

	if (!bt_graph_recurse(start, target, visited, path))
	{
		free(path);
		path = NULL;
	}

	free(visited);
	return (path);
}
