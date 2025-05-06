/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:00:03 by auzou             #+#    #+#             */
/*   Updated: 2025/05/06 17:03:27 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* check if the player pos is within bounds */
int	is_within_bounds(char **grid, int row, int col, int height)
{
	int	first_non_space;
	int	row_len;

	if (!grid)
		return (0);
	if (row < 0 || row >= height || !grid[row])
		return (0);
	first_non_space = 0;
	row_len = ft_strlen(grid[row]);
	while (first_non_space < row_len && is_space(grid[row][first_non_space]))
		first_non_space++;
	if (col < first_non_space || col < 0 || col >= row_len)
		return (0);
	return (1);
}

/* flood fill to check if surrounded by wall */
int	flood_fill(t_map *map, bool **visited, int x, int y)
{
	if (!is_within_bounds(map->grid, y, x, map->height))
		return (0);
	if (visited[y][x] || map->grid[y][x] == '1')
		return (1);
	if (!ft_strchr("0NSEW ", map->grid[y][x]))
		return (0);
	visited[y][x] = true;
	return (flood_fill(map, visited, x + 1, y)
		&& flood_fill(map, visited, x - 1, y)
		&& flood_fill(map, visited, x, y + 1)
		&& flood_fill(map, visited, x, y - 1));
}

/* free the visited grid */
void	free_visited_grid(bool **visited, int height)
{
	int	i;

	if (!visited)
		return ;
	i = 0;
	while (i < height)
	{
		free(visited[i]);
		i++;
	}
	free(visited);
}

/* init visited grid for flood fill */
bool	**create_visited_grid(int width, int height)
{
	bool	**visited;
	int		i;

	visited = (bool **)ft_calloc(height, sizeof(bool *));
	if (!visited)
		return (NULL);
	i = 0;
	while (i < height)
	{
		visited[i] = (bool *)ft_calloc(width, sizeof(bool));
		if (!visited[i])
		{
			free_visited_grid(visited, i);
			return (NULL);
		}
		i++;
	}
	return (visited);
}

/* check if map is closed */
int	is_map_closed(t_map *map)
{
	bool	**visited;
	int		result;

	visited = create_visited_grid(map->width, map->height);
	if (!visited)
		return (0);
	result = flood_fill(map, visited, map->player_x, map->player_y);
	free_visited_grid(visited, map->height);
	return (result);
}
