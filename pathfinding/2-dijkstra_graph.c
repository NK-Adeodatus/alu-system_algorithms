#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "pathfinding.h"

#define INF ((size_t)-1)

/**
 * build_path - Reconstructs path queue from prev array
 *
 * @verts: array of graph vertices in index order
 * @prev: array of predecessor indices (-1 if none)
 * @target_idx: index of the target vertex
 *
 * Return: queue of strdup'd vertex names, or NULL on failure
 */
static queue_t *build_path(vertex_t **verts, int *prev, size_t target_idx)
{
	queue_t *path;
	char *label;
	int cur;

	path = queue_create();
	if (!path)
		return (NULL);
	for (cur = (int)target_idx; cur != -1; cur = prev[cur])
	{
		label = strdup(verts[cur]->content);
		if (!label)
		{
			free(path);
			return (NULL);
		}
		queue_push_front(path, label);
	}
	return (path);
}

/**
 * min_unvisited - Returns index of unvisited vertex with smallest distance
 *
 * @dist: distance array
 * @visited: visited flags array
 * @n: number of vertices
 *
 * Return: index of minimum, or n if all visited or all INF
 */
static size_t min_unvisited(size_t *dist, char *visited, size_t n)
{
	size_t i, best;

	best = n;
	for (i = 0; i < n; i++)
	{
		if (visited[i] || dist[i] == INF)
			continue;
		if (best == n || dist[i] < dist[best])
			best = i;
	}
	return (best);
}

/**
 * init_arrays - Allocates and initialises Dijkstra working arrays
 *
 * @graph: pointer to the graph
 * @verts: output array of vertex pointers by index
 * @dist: output distance array (all INF)
 * @prev: output predecessor array (all -1)
 * @visited: output visited flags array (all 0)
 *
 * Return: 0 on success, -1 on allocation failure
 */
static int init_arrays(graph_t *graph, vertex_t ***verts,
		size_t **dist, int **prev, char **visited)
{
	size_t n, i;
	vertex_t *v;

	n = graph->nb_vertices;
	*verts = malloc(n * sizeof(**verts));
	*dist = malloc(n * sizeof(**dist));
	*prev = malloc(n * sizeof(**prev));
	*visited = calloc(n, sizeof(**visited));
	if (!*verts || !*dist || !*prev || !*visited)
	{
		free(*verts); free(*dist); free(*prev); free(*visited);
		return (-1);
	}
	for (v = graph->vertices, i = 0; v; v = v->next, i++)
	{
		(*verts)[i] = v;
		(*dist)[i] = INF;
		(*prev)[i] = -1;
	}
	return (0);
}

/**
 * dijkstra_graph - Finds shortest path in a graph using Dijkstra's algorithm
 *
 * @graph: pointer to the graph to search
 * @start: pointer to the starting vertex
 * @target: pointer to the target vertex
 *
 * Return: queue of char * vertex names from start to target, or NULL
 */
queue_t *dijkstra_graph(graph_t *graph, vertex_t const *start,
		vertex_t const *target)
{
	size_t n, u, alt;
	size_t *dist;
	int *prev;
	char *visited;
	vertex_t **verts;
	edge_t *e;
	queue_t *path;

	if (init_arrays(graph, &verts, &dist, &prev, &visited) == -1)
		return (NULL);
	n = graph->nb_vertices;
	dist[start->index] = 0;
	while ((u = min_unvisited(dist, visited, n)) < n)
	{
		printf("Checking %s, distance from %s is %lu\n",
			verts[u]->content, start->content, dist[u]);
		visited[u] = 1;
		if (verts[u] == target)
			break;
		for (e = verts[u]->edges; e; e = e->next)
		{
			if (visited[e->dest->index])
				continue;
			alt = dist[u] + e->weight;
			if (alt < dist[e->dest->index])
			{
				dist[e->dest->index] = alt;
				prev[e->dest->index] = (int)u;
			}
		}
	}
	path = visited[target->index] ?
		build_path(verts, prev, target->index) : NULL;
	free(dist); free(prev); free(visited); free(verts);
	return (path);
}
