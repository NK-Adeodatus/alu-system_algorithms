#include <stdlib.h>
#include <stdio.h>
#include "pathfinding.h"

/**
 * bt_recurse - Recursive helper for backtracking path search
 *
 * @map: 2D array map (read-only)
 * @visited: 2D array tracking visited cells
 * @rows: number of rows in map
 * @cols: number of columns in map
 * @x: current X coordinate (column)
 * @y: current Y coordinate (row)
 * @target: pointer to target coordinates
 * @path: queue to build the path into
 *
 * Return: 1 if path found, 0 otherwise
 */
static int bt_recurse(char **map, char **visited, int rows, int cols,
		int x, int y, point_t const *target, queue_t *path)
{
	point_t *pt;

	if (x < 0 || x >= cols || y < 0 || y >= rows)
		return (0);
	if (map[y][x] == '1' || visited[y][x])
		return (0);

	printf("Checking coordinates [%d, %d]\n", x, y);
	visited[y][x] = 1;

	if (x == target->x && y == target->y)
	{
		pt = malloc(sizeof(*pt));
		if (!pt)
			return (0);
		pt->x = x;
		pt->y = y;
		queue_push_front(path, pt);
		return (1);
	}

	if (bt_recurse(map, visited, rows, cols, x + 1, y, target, path) ||
	    bt_recurse(map, visited, rows, cols, x, y + 1, target, path) ||
	    bt_recurse(map, visited, rows, cols, x - 1, y, target, path) ||
	    bt_recurse(map, visited, rows, cols, x, y - 1, target, path))
	{
		pt = malloc(sizeof(*pt));
		if (!pt)
			return (0);
		pt->x = x;
		pt->y = y;
		queue_push_front(path, pt);
		return (1);
	}

	return (0);
}

/**
 * backtracking_array - Finds a path in a 2D array using backtracking
 *
 * @map: pointer to a read-only 2D array
 * @rows: number of rows in the map
 * @cols: number of columns in the map
 * @start: pointer to starting coordinates
 * @target: pointer to target coordinates
 *
 * Return: queue of point_t from start to target, or NULL on failure
 */
queue_t *backtracking_array(char **map, int rows, int cols,
		point_t const *start, point_t const *target)
{
	char **visited;
	queue_t *path;
	int i;

	visited = calloc(rows, sizeof(*visited));
	if (!visited)
		return (NULL);
	for (i = 0; i < rows; i++)
	{
		visited[i] = calloc(cols, sizeof(**visited));
		if (!visited[i])
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			return (NULL);
		}
	}

	path = queue_create();
	if (!path)
	{
		for (i = 0; i < rows; i++)
			free(visited[i]);
		free(visited);
		return (NULL);
	}

	if (!bt_recurse(map, visited, rows, cols,
			start->x, start->y, target, path))
	{
		for (i = 0; i < rows; i++)
			free(visited[i]);
		free(visited);
		free(path);
		return (NULL);
	}

	for (i = 0; i < rows; i++)
		free(visited[i]);
	free(visited);
	return (path);
}
