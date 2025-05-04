/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: czhu <czhu@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:55:21 by auzou             #+#    #+#             */
/*   Updated: 2025/05/04 14:11:41 by czhu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"
/* free the map when error or exit */
void	free_map(t_map *map)
{
	int	i;

	if (map->grid != NULL)
	{
		i = 0;
		while (i < map->height)
		{
			if (map->grid[i] != NULL)
            {
                free(map->grid[i]);
                map->grid[i] = NULL;
            }
			i++;
		}
		free(map->grid);
		map->grid = NULL;
	}
}

/* free texture paths */
void    free_texture_path(t_game *game)
{
    if (game->textures.north_path)
        free(game->textures.north_path);
    if (game->textures.south_path)
        free(game->textures.south_path);
    if (game->textures.west_path)
        free(game->textures.west_path);
    if (game->textures.east_path)
        free(game->textures.east_path);
}

/* destroy all texture img */
void    free_texture_img(t_game *game)
{
    if (game->mlx)
    {
        if (game->textures.north_img.img)
            mlx_destroy_image(game->mlx, game->textures.north_img.img);
        if (game->textures.south_img.img)
            mlx_destroy_image(game->mlx, game->textures.south_img.img);
        if (game->textures.west_img.img)
            mlx_destroy_image(game->mlx, game->textures.west_img.img);
        if (game->textures.east_img.img)
            mlx_destroy_image(game->mlx, game->textures.east_img.img);
    }
    if (game->img)
        mlx_destroy_image(game->mlx, game->img);
}

/* handle program exit
    - free map
    - free texture paths
    - destroy all loaded texture img
    - destory main img
    - cleanup MLX resource
    - free the game struct
*/
void	cleanup(t_game *game)
{
	if (!game)
		return ;
	free_map(&game->map);
    free_texture_path(game);
    free_texture_img(game);
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
    free(game);
}
