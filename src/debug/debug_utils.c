/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 17:58:07 by auzou             #+#    #+#             */
/*   Updated: 2025/05/05 17:47:29 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

void	print_texture(t_texture *texture)
{
	printf("=== texture info ===\n");
	printf("north texture: %s\n", texture->north_path);
	printf("south texture: %s\n", texture->south_path);
	printf("west texture: %s\n", texture->west_path);
	printf("east texture: %s\n", texture->east_path);
	printf("floor color: %X\n", texture->floor_color);
	printf("ceiling color: %X\n", texture->ceiling_color);
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

	printf("=== map info ===\n");
	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			printf("%c", map->grid[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("map height: %d\n", map->height);
	printf("map width: %d\n", map->width);
}

void	print_player(t_player *player)
{
	printf("=== player info ===\n");
	printf("player pos x: %f\n", player->pos_x);
	printf("player pos y: %f\n", player->pos_y);
	printf("player angle: %f * PI\n", player->angle / PI);
}
