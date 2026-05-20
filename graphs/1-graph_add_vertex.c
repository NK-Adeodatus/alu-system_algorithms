#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * graph_add_vertex - Adds a vertex to an existing graph
 *
 * @graph: Pointer to the graph to add the vertex to
 * @str: String to store in the new vertex
 *
 * Return: Pointer to the created vertex, or NULL on failure
 */
vertex_t *graph_add_vertex(graph_t *graph, const char *str)
{
	vertex_t *current, *new_vertex;
	char *content;

	if (!graph || !str)
		return (NULL);

	current = graph->vertices;
	while (current)
	{
		if (strcmp(current->content, str) == 0)
			return (NULL);
		current = current->next;
	}

	new_vertex = malloc(sizeof(vertex_t));
	if (!new_vertex)
		return (NULL);

	content = strdup(str);
	if (!content)
	{
		free(new_vertex);
		return (NULL);
	}

	new_vertex->content = content;
	new_vertex->nb_edges = 0;
	new_vertex->edges = NULL;
	new_vertex->next = NULL;

	if (!graph->vertices)
	{
		new_vertex->index = 0;
		graph->vertices = new_vertex;
	}
	else
	{
		current = graph->vertices;
		while (current->next)
			current = current->next;
		new_vertex->index = current->index + 1;
		current->next = new_vertex;
	}

	graph->nb_vertices++;

	return (new_vertex);
}
