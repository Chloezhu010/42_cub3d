/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auzou <auzou@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:07:35 by auzou             #+#    #+#             */
/*   Updated: 2025/05/06 17:48:31 by auzou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/cub3D.h"

/* cal distance using delta x, delta y */
float	distance(float x, float y)
{
	return (sqrt(x * x + y * y));
}

float	fixed_dist(t_dist_data *data, t_game *game)
{
	float	delta_x;
	float	delta_y;
	float	angle;
	float	fix_dist;

	delta_x = data->end_x - data->start_x;
	delta_y = data->end_y - data->start_y;
	angle = atan2(delta_y, delta_x) - game->player.angle;
	fix_dist = distance(delta_x, delta_y) * cos(angle);
	if (fix_dist < 0.1f)
		fix_dist = 0.1f;
	return (fix_dist);
}

/* detect whether the ray touches the wall */
bool touch(float px, float py, t_game *game)
{
    int x;
    int y;

    x = px / BLOCK;
    y = py / BLOCK;
    
    // 1. 检查坐标是否在地图数组范围内
    if (y < 0 || y >= game->map.height)
        return (true); // 将边界外区域视为实体
    
    // 2. 检查x坐标是否在当前行长度范围内
    if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
        return (true); // 将边界外区域视为实体
    
    // 3. 核心判断：检查当前位置
    if (game->map.grid[y][x] == '1') // 墙壁
        return (true);
        
    // 4. 处理非封闭区域外的空格（使用is_within_bounds来验证）
    if (game->map.grid[y][x] == ' ' && !is_within_bounds(game->map.grid, y, x, game->map.height))
        return (true); // 有效路径外的空格视为墙壁
        
    return (false); // 有效路径内的空格或者0、玩家位置都是可通过的
}

/* put pixel into the buffer, then display */
void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

/* helper function for draw_loop */
void	clear_image(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}
