#include <stdlib.h>
#include "graphs.h"

/**
 * struct queue_node_s - Node in a BFS queue
 *
 * @v: Pointer to the vertex
 * @depth: Depth of the vertex from the start
 * @next: Pointer to the next node in the queue
 */
typedef struct queue_node_s
{
	const vertex_t		*v;
	size_t			depth;
	struct queue_node_s	*next;
} queue_node_t;

/**
 * enqueue - Adds a vertex to the tail of the queue
 *
 * @head: Pointer to the head of the queue
 * @tail: Pointer to the tail of the queue
 * @v: Vertex to enqueue
 * @depth: Depth of the vertex
 *
 * Return: 1 on success, 0 on failure
 */
static int enqueue(queue_node_t **head, queue_node_t **tail,
		const vertex_t *v, size_t depth)
{
	queue_node_t *node;

	node = malloc(sizeof(queue_node_t));
	if (!node)
		return (0);
	node->v = v;
	node->depth = depth;
	node->next = NULL;
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	return (1);
}

/**
 * breadth_first_traverse - Traverses a graph using breadth-first algorithm
 *
 * @graph: Pointer to the graph to traverse
 * @action: Function to call for each visited vertex
 *
 * Return: The biggest vertex depth reached, or 0 on failure
 */
size_t breadth_first_traverse(const graph_t *graph,
		void (*action)(const vertex_t *v, size_t depth))
{
	queue_node_t *head, *tail, *tmp;
	char *visited;
	size_t max_depth;
	edge_t *edge;

	if (!graph || !action || !graph->vertices)
		return (0);
	visited = calloc(graph->nb_vertices, sizeof(char));
	if (!visited)
		return (0);
	head = tail = NULL;
	max_depth = 0;
	if (!enqueue(&head, &tail, graph->vertices, 0))
	{
		free(visited);
		return (0);
	}
	visited[graph->vertices->index] = 1;
	while (head)
	{
		tmp = head;
		head = head->next;
		if (!head)
			tail = NULL;
		action(tmp->v, tmp->depth);
		if (tmp->depth > max_depth)
			max_depth = tmp->depth;
		edge = tmp->v->edges;
		while (edge)
		{
			if (!visited[edge->dest->index])
			{
				visited[edge->dest->index] = 1;
				enqueue(&head, &tail, edge->dest,
					tmp->depth + 1);
			}
			edge = edge->next;
		}
		free(tmp);
	}
	free(visited);
	return (max_depth);
}
