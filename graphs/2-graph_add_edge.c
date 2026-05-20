#include <stdlib.h>
#include <string.h>
#include "graphs.h"

/**
 * find_vertex - Finds a vertex in the graph by its string content
 *
 * @graph: Pointer to the graph to search
 * @str: String to search for
 *
 * Return: Pointer to the matching vertex, or NULL if not found
 */
static vertex_t *find_vertex(graph_t *graph, const char *str)
{
	vertex_t *current;

	current = graph->vertices;
	while (current)
	{
		if (strcmp(current->content, str) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

/**
 * create_edge - Creates and appends an edge from src to dest
 *
 * @src: Pointer to the source vertex
 * @dest: Pointer to the destination vertex
 *
 * Return: Pointer to the new edge, or NULL on failure
 */
static edge_t *create_edge(vertex_t *src, vertex_t *dest)
{
	edge_t *new_edge, *current;

	new_edge = malloc(sizeof(edge_t));
	if (!new_edge)
		return (NULL);
	new_edge->dest = dest;
	new_edge->next = NULL;
	if (!src->edges)
	{
		src->edges = new_edge;
	}
	else
	{
		current = src->edges;
		while (current->next)
			current = current->next;
		current->next = new_edge;
	}
	src->nb_edges++;
	return (new_edge);
}

/**
 * graph_add_edge - Adds an edge between two vertices in a graph
 *
 * @graph: Pointer to the graph to add the edge to
 * @src: String identifying the source vertex
 * @dest: String identifying the destination vertex
 * @type: Type of edge (UNIDIRECTIONAL or BIDIRECTIONAL)
 *
 * Return: 1 on success, 0 on failure
 */
int graph_add_edge(graph_t *graph, const char *src,
		const char *dest, edge_type_t type)
{
	vertex_t *v_src, *v_dest;
	edge_t *edge1;

	if (!graph || !src || !dest)
		return (0);
	v_src = find_vertex(graph, src);
	v_dest = find_vertex(graph, dest);
	if (!v_src || !v_dest)
		return (0);
	edge1 = create_edge(v_src, v_dest);
	if (!edge1)
		return (0);
	if (type == BIDIRECTIONAL)
	{
		if (!create_edge(v_dest, v_src))
		{
			v_src->edges = NULL;
			free(edge1);
			v_src->nb_edges--;
			return (0);
		}
	}
	return (1);
}
