#ifndef GRAPHS_H
#define GRAPHS_H

#include <stddef.h>

typedef enum edge_type_e
{
	UNIDIRECTIONAL = 0,
	BIDIRECTIONAL
} edge_type_t;

typedef struct vertex_s vertex_t;

typedef struct edge_s
{
	vertex_t	*dest;
	struct edge_s	*next;
} edge_t;

struct vertex_s
{
	size_t		index;
	char		*content;
	size_t		nb_edges;
	edge_t		*edges;
	struct vertex_s	*next;
};

typedef struct graph_s
{
	size_t		nb_vertices;
	vertex_t	*vertices;
} graph_t;

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

/* Function prototypes */
graph_t		*graph_create(void);
vertex_t	*graph_add_vertex(graph_t *graph, const char *str);
int		graph_add_edge(graph_t *graph, const char *src,
			const char *dest, edge_type_t type);
void		graph_delete(graph_t *graph);
size_t		depth_first_traverse(const graph_t *graph,
			void (*action)(const vertex_t *v, size_t depth));
size_t		breadth_first_traverse(const graph_t *graph,
			void (*action)(const vertex_t *v, size_t depth));

#endif /* GRAPHS_H */
