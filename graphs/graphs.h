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

/* Function prototypes */
graph_t		*graph_create(void);
vertex_t	*graph_add_vertex(graph_t *graph, const char *str);

#endif /* GRAPHS_H */
