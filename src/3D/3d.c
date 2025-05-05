/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:48:23 by czhu              #+#    #+#             */
/*   Updated: 2025/05/05 18:08:48 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

int	draw_loop(t_game *game)
{
	t_player	*player;
	float		ray_x;
	float		ray_y;
	float		start_x;
	int			i;

	player = &game->player;
	ray_x = player->pos_x;
	ray_y = player->pos_y;
	move_player(player, game);
	clear_image(game);
	start_x = player->angle + PI / 6;
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x -= (PI / 3 / WIDTH);
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}

t_wall_side	get_wall_side(float ray_x, float ray_y, float dx, float dy)
{
	int		map_x;
	int		map_y;
	float	prev_x;
	float	prev_y;
	int		prev_map_x;

	map_x = ray_x / BLOCK;
	map_y = ray_y / BLOCK;
	prev_x = ray_x - dx;
	prev_y = ray_y - dy;
	prev_map_x = prev_x / BLOCK;
	if (prev_map_x < map_x)
		return (WALL_WEST);
	else if (prev_map_x > map_x)
		return (WALL_EAST);
	if ((prev_y / BLOCK) < map_y)
		return (WALL_NORTH);
	else if ((prev_y / BLOCK) > map_y)
		return (WALL_SOUTH);
	return (WALL_NORTH);
}
