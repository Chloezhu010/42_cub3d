/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:55:21 by auzou             #+#    #+#             */
/*   Updated: 2025/05/03 17:58:00 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"
/* free the map when error or exit */
void	free_map(t_game *game)
{
	int	i;

	if (game->map.grid != NULL)
	{
		i = 0;
		while (i < 11)
		{
			if (game->map.grid[i] != NULL)
				free(game->map.grid[i]);
			i++;
		}
		free(game->map.grid);
		game->map.grid = NULL;
	}
}

/* cleanup textures */
void	cleanup_resource(t_map *map, t_texture *texture)
{
	int	i;

	if (texture)
	{
		if (texture->north_path)
			free(texture->north_path);
		if (texture->south_path)
			free(texture->south_path);
		if (texture->west_path)
			free(texture->west_path);
		if (texture->east_path)
			free(texture->east_path);
		free(texture);
	}
	if (map && map->grid)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i])
				free(map->grid[i]);
			i++;
		}
		free(map->grid);
	}
	if (map)
		free(map);
}

/* handle program exit */
void	cleanup(t_game *game)
{
	if (!game)
		return ;
	free_map(game);
	if (game->mlx)
	{
		if (game->win)
		{
			mlx_destroy_window(game->mlx, game->win);
			game->win = NULL;
		}
		mlx_destroy_display(game->mlx);
		free(game->mlx);
		game->mlx = NULL;
	}
}